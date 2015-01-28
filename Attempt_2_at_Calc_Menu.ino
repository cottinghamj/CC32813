// A Cost-effective Alternative to Expensive Computers and Mobile Devices
// by Jarian Cottingham
// 17 March 2013

// Note to self >>> The problem we are now having is we need a working key pad for the symbol and also we need to make the software according to the analog values. 
//This is all to do with Calculator Mode. The avgValue function keeps adding numbers to the previous number until a symbol interrupts. This algorithm needs to be set up. Also prototype the 
// 5 symbol keypad.

//Might get rid of numbers beside menu options. Might just have to directly pick instead of numbers

#include <LiquidCrystal.h> 
#include <avr/pgmspace.h>

// IMPORTANT: Both of these are getValue() variables. Very important for the functionality of the program 
int avgValue = 0;
int value[5];     // Can change this number to affect the accuracy of clicks

byte ArrowPadPin = 0;
byte NumberPadPin = 1;
byte SymbolPadPin = 2;
byte cursorTrack = 0;

byte ControlPadPin = 4;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
/*
Mode 0 = Menu Navigation Mode
Mode 1 = Calculator Mode
Mode 2 = Quiz Mode
Mode 3 = App Mode
Mode 4 = Settings Navigation
Mode 5 = Chat Mode
Mode 6 = Set Time
Mode 7 = Set Password
Mode 8 = Timer Mode
Mode 9 = Quiz Pick Mode
Mode 10 = Download Quiz Mode
Mode 11 = Upload Quiz Mode
Mode 12 = Get Results Mode
Mode 13 = Make Quiz Mode
Mode 14 = Delete Quiz Mode 
Mode 15 = Math Functions Mode
Mode 16 = Temperature Mode
Mode 17 = Buzzer Mode
Mode 18 = Quiz Environment
Mode 19 = Morse Code Mode
Mode 20 = See Gotten Results Mode
Mode 21 = Button Tester Mode
Mode 22 = Flash Card Mode
Mode 23 = Data Receive Mode
Mode 24 = Data Send Mode
*/

prog_char menuOptions_0[] PROGMEM = "(0)Calculator";   
prog_char menuOptions_1[] PROGMEM = "(1)Quiz Mode";
prog_char menuOptions_2[] PROGMEM = "(2)Apps";
prog_char menuOptions_3[] PROGMEM = "(3)Settings";
prog_char menuOptions_4[] PROGMEM = "(4)Chat";

PROGMEM const char *menuOptions_table[] = 	   
{   
  menuOptions_0,
  menuOptions_1,
  menuOptions_2,
  menuOptions_3,
  menuOptions_4
};

byte menuOptionsSize = 5; // Might just change value for function directly. It is permanent.

prog_char settingOptions_0[] PROGMEM = "(1)Password Set";
prog_char settingOptions_1[] PROGMEM = "(2)Info";
prog_char settingOptions_2[] PROGMEM = "(3)Splash Screen";
prog_char settingOptions_3[] PROGMEM = "(4)Button Tester";
prog_char settingOptions_4[] PROGMEM = "(5)Main Menu";


PROGMEM const char *settingOptions_table[] = 
{
  settingOptions_0,
  settingOptions_1,
  settingOptions_2,
  settingOptions_3,
  settingOptions_4
};

byte settingOptionsSize = 5;  // Might just change value for function directly. It is permanent.

prog_char quizOptions_0[] PROGMEM = "(0)Pick A Quiz";
prog_char quizOptions_1[] PROGMEM = "(1)Download Quiz";
prog_char quizOptions_2[] PROGMEM = "(2)Upload Quiz";
prog_char quizOptions_3[] PROGMEM = "(3)See Results";
prog_char quizOptions_4[] PROGMEM = "(4)Make a Quiz";
prog_char quizOptions_5[] PROGMEM = "(5)Delete Quiz";
prog_char quizOptions_6[] PROGMEM = "(6)Main Menu";

PROGMEM const char *quizOptions_table[] = 
{
  quizOptions_0,
  quizOptions_1,
  quizOptions_2,
  quizOptions_3,
  quizOptions_4,
  quizOptions_5,
  quizOptions_6
};

byte quizOptionsSize = 7;  // // Might just change value for function directly. It is permanent.

prog_char quizSelect_0[] PROGMEM = "Calculus 5.1";
prog_char quizSelect_1[] PROGMEM = "Physics C 3";
prog_char quizSelect_2[] PROGMEM = "Statistics AP";

PROGMEM const char *quizSelect_table[] = 
{
  quizSelect_0,
  quizSelect_1,
  quizSelect_2,
};

byte quizSelectSize = 3;  // // Needs to be made changeable. This is a sample

prog_char appOptions_0[] PROGMEM = "Timer";
prog_char appOptions_1[] PROGMEM = "Morse Code";
prog_char appOptions_2[] PROGMEM = "Temperature";
prog_char appOptions_3[] PROGMEM = "Flash Cards";
prog_char appOptions_4[] PROGMEM = "Buzzer";
prog_char appOptions_5[] PROGMEM = "Laser Line";
prog_char appOptions_6[] PROGMEM = "Math Functions";

PROGMEM const char *appOptions_table[] = 
{
  appOptions_0,
  appOptions_1,
  appOptions_2,
  appOptions_3,
  appOptions_4,
  appOptions_5,
  appOptions_6
};

byte appOptionsSize = 6;

prog_char mathFunctions_0[] PROGMEM = "Pythagorean";
prog_char mathFunctions_1[] PROGMEM = "MidPoint Form";
prog_char mathFunctions_2[] PROGMEM = "Distance Form";

PROGMEM const char *mathFunctions_table[] = 
{
  mathFunctions_0,
  mathFunctions_1,
  mathFunctions_2
};

byte mathFunctionsSize = 3;

char buffer[30];

byte menuPos = 0;//constrain(menuPos, 0, 20);
byte Mode;
byte shift = 0;

float calcNum[10];
byte symbols[10]; // The highest number of symbol is the CalcNums - 1, The equal sign is the last
byte turn; 
float Answer;
byte operation[10]; // for sqroot, sin, cos, etc.
boolean on = false;
int seconds;
boolean Celsius = true;
int buzzerValue = 800;
byte specFunc[10];  // Special Function Array
byte openPar[10];       // This variable tells the menuPos where Parentheses opened
boolean nosymbol = true;

byte entryNumber = 20;
char quizEntry[20];
char calcQuizEntry[20];
char calcQuizAnswers[] = {68, 66, 65, 66, 68, 68, 65, 66, 65, 67, 66, 65, 65, 65, 65, 66, 66, 67, 68, 65};
char physicsQuizEntry[20];
char physicsQuizAnswers[] = {66, 66, 65, 66, 68, 68, 67, 66, 66, 67, 66, 65, 65, 66, 65, 66, 66, 67, 68, 65};
char statQuizEntry[20];
char statQuizAnswers[] = {65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65};
byte points;
char receiveQuizAnswer[20];

boolean pressed = false;
int M;
byte quiz;
byte MathFunc;

void setup()
{
  lcd.begin(16,2);
  //SplashScreen();
  MainMenu(); 
}

void loop()
{
  if(Mode == 17)      // Timer Mode (does not like the delay in the loop)
  {
    int val = analogRead(ArrowPadPin);
    if(val > 1020)
    {
      pinMode(6, OUTPUT);
      digitalWrite(6, HIGH);
      delayMicroseconds(buzzerValue);
      digitalWrite(6, LOW);
      delayMicroseconds(buzzerValue);
    }    // need to bypass the delay
    else if(val > 765 && val < 768)      // 
    {
      delay(250);
      val = analogRead(ArrowPadPin);
      if(val > 765 && val < 768)
      {
        menuPos = 0;
        Apps();
      }
    }
  }
  else if(Mode == 19)      // Morse Code Mode
  {
    MorseCode();
  }
  else if(Mode == 25) //     Laser Line Mode
  {
    LaserLine();
  }
  else
  {
//  Serial.println("In the loop!");
  delay(150);  // This is the speed of scrolling through menues --- Might make it adjustable by the user
  getValue();
  }
}

void getValue()
{
  for(byte t = 0; t < 3; t++)
  {
    int value[3];     // Can change this number to affect the accuracy of clicks
    for(int i = 0; i < 3; i++) // Can change this number to affect the accuracy of clicks
    {
      if(t == 0)
      {ControlPadPin = ArrowPadPin;}   //  Arrow Pad
      else if(t == 1)
      {ControlPadPin = NumberPadPin;}   //  NumberPad
      else if(t == 2)
      {ControlPadPin = SymbolPadPin;}   //  SymbolPad
      delay(50);                       // delay is placed here so switching pins does not mess with other pin values
      value[i] = analogRead(ControlPadPin);
      if(i != 0)
      {
        value[i] = value[i] + value[i - 1];
      } 
    }
    avgValue = value[2] / 3; // This is the value that will be used to determine button pushed 
    evalValue(avgValue);
  }
}
void evalValue(int avgValue)
{
  if(ControlPadPin == ArrowPadPin)
  {
      if(avgValue == 0)                      //             Up Button     ---------------------------------------------------------------------------------------
      {
        switch(Mode)
        {
          case 0:
          {
            if(menuPos == 0)
            {
              // do nothing
            }
            else if(menuPos > 0)
            {
              menuPos -= 1;          // Subtraction from menuPos pushes you left in the string array
            }
            MainMenu();
            break;
          }
          case 1:
          {
            break;
          }
          case 2:
          {
            if(menuPos == 0)
            {
              // do nothing
            }
            else if(menuPos > 0)
            {
              menuPos -= 1;          // Subtraction from menuPos pushes you left in the string array
            }
            QuizMode();
            break;
          }
          case 3:
          {
            if(menuPos == 0)
            {
              // do nothing
            }
            else if(menuPos > 0)
            {
              menuPos -= 1;          // Subtraction from menuPos pushes you left in the string array
            }
            Apps();
            break;
          }
          case 4:
          {
            if(menuPos == 0)
            {
              // do nothing
            }
            else if(menuPos > 0)
            {
              menuPos -= 1;          // Subtraction from menuPos pushes you left in the string array
            }
            Settings();
            break;
          }
          case 9:
          {
            if(menuPos == 0)
            {
              // do nothing
            }
            else if(menuPos > 0)
            {
              menuPos -= 1;          // Subtraction from menuPos pushes you left in the string array
            }
            quizPick();
            break;
          }
          case 12:
          {
            if(menuPos == 0)
            {
              // do nothing
            }
            else if(menuPos > 0)
            {
              menuPos -= 1;          // Subtraction from menuPos pushes you left in the string array
            }
            getResults();
            break;
          }
          case 18:
          {
            if(menuPos == 0)
            {
              // do nothing
            }
            else if(menuPos > 0)
            {
              menuPos -= 1;
            }
            quizEnvironment();
            break;
          }
          case 21:
          {
            lcd.clear();              
            lcd.print(analogRead(0));
            break;
          }
          case 22:
          {
            if(menuPos == 0)
            {
              // do nothing
            }
            else if(menuPos > 0)
            {
              menuPos -= 1;
            }
            FlashCards();
            break;
          }
          case 24:
          {
            shift = 1;
            dataSend();
            break;
          }
          default:
          {
            lcd.print("ERROR");
            break;
          }
        }
      }
      else if(avgValue > 509 && avgValue < 513)        //             Down Button     ---------------------------------------------------------------------------------------
      {
        switch(Mode)
        {
          case 0:
          {
            if(menuPos == menuOptionsSize)
            {
              // do nothing
            }
            else if(menuPos < menuOptionsSize)
            {
              menuPos += 1;       //   Adding to menuPos pushes you to the right in the string array
            }
            MainMenu();
            break;
          }
          case 1:
          {
            delay(300);
            if(analogRead(0) == avgValue)
            {
              menuPos = 0;
              MainMenu();
              break;
            }
          }
          case 2:
          {
            if(menuPos == quizOptionsSize)
            {
              // do nothing
            }
            else if(menuPos < quizOptionsSize)
            {
              menuPos += 1;       //   Adding to menuPos pushes you to the right in the string array
            }
            QuizMode();
            break;
          }
          case 3:
          {
            if(menuPos == appOptionsSize)
            {
              // do nothing
            }
            else if(menuPos < appOptionsSize)
            {
              menuPos += 1;       //   Adding to menuPos pushes you to the right in the string array
            }
            Apps();
            break;
          }
          case 4:
          {
            if(menuPos == settingOptionsSize)
            {
              // do nothing
            }
            else if(menuPos < settingOptionsSize)
            {
              menuPos += 1;       //   Adding to menuPos pushes you to the right in the string array
            }
            Settings();
            break;
          }
          case 9:
          {
            if(menuPos == quizSelectSize)
            {
              // do nothing
            }
            else if(menuPos < quizSelectSize)
            {
              menuPos += 1;       //   Adding to menuPos pushes you to the right in the string array
            }
            quizPick();
            break;
          }
          case 12:
          {
            if(menuPos == quizSelectSize)
            {
              // do nothing
            }
            else if(menuPos < quizSelectSize)
            {
              menuPos += 1;       //   Adding to menuPos pushes you to the right in the string array
            }
            getResults();
            break;
          }
          case 18:
          {
            if(menuPos == entryNumber)
            {
              // do nothing
            }
            else if(menuPos < entryNumber)
            {
              menuPos += 1;
            }
            quizEnvironment();
            break;
          }
          case 21:
          {
            lcd.clear();              
            lcd.print(analogRead(0));
            break;
          }
          case 22:
          {
            if(menuPos == entryNumber)
            {
              // do nothing
            }
            else if(menuPos < entryNumber)
            {
              menuPos += 1;
            }
            FlashCards();
            break;
          }
          default:
          {
            lcd.print("ERROR");
            break;
          }
        }
      }
      else if(avgValue > 1020)        //             Select Button    
      {
        switch(Mode)
        {
          case 0:
          {
            Select();
//            Serial.println("You might say I am also in case");
            break;
          }
          case 1:
          {
            shift = 1;
            delay(50);      // This delay is so that 0 is not recorded as an input
            break;
          }
          case 2:
          {
             Select();
             break; 
          }
          case 3:
          {
            Select();
            break;
          }
          case 4:
          {
            Select();
            break;
          }
          case 8:
          {
            Select();
            break;
          }
          case 9:
          {
            Select();
            break;
          }
          case 12:
          {
            Select();
            break;
          }
          case 15:
          {
            menuPos++;
            break;
          }
          case 16:
          {
            if(Celsius == false)
            {
              Celsius = true;
              Temperature();
              break;
            }
            else if(Celsius == true)
            {
              Celsius = false;
              Temperature();
              break;
            }
          }
          case 19:
          {
            pressed = true;
            MorseCode();
            break;
          }
          case 21:
          { 
            lcd.clear();             
            lcd.print(analogRead(0));
            break;
          }  
      }
    }
    else if(avgValue > 253 && avgValue < 256)  //    ------------------    right
    {
      switch(Mode)
      {
        case 21:
          {            
            lcd.print(analogRead(0));
            break;
          }
      }
    }
    else if(avgValue > 765 && avgValue < 768)  //  --------------------   left
    {
      switch(Mode)
      {
         case 1:
         {
            Delete();      //    the DELETE KEY
            break;
         }
         case 2:
         {
           menuPos = 0;
           MainMenu();
           break;
         }
         case 3:
         {
            menuPos = 0;
            MainMenu();
            break;
         }
         case 5:
         {
           menuPos = 0;
           MainMenu();
           break;
         }
         case 8:
         {
           menuPos = 0;
            MainMenu(); 
            break;
         }
         case 16:
         {
           menuPos = 0;
            MainMenu();
            break;
         }
         case 18:
         {
            menuPos = 0;
            for(byte s = 0; s < entryNumber; s++)
            {
              if(quiz == 1)
              {
                calcQuizEntry[s] = quizEntry[s];
              }
              else if(quiz == 2)
              {
                physicsQuizEntry[s] = quizEntry[s];
              }
              else if(quiz == 3)
              {
                statQuizEntry[s] = quizEntry[s];
              }
              quizEntry[s] = 32;    // makes it blank again
            }
            QuizMode();
            break;
         }
         case 19:
         {
           menuPos = 0;
           lcd.noAutoscroll();
           Apps();
           break;
         }
         case 20:
         {
           menuPos = 0;
           QuizMode();
           break;
         }
         case 21:
          {
            lcd.clear();            
            lcd.print(analogRead(0));
            break;
          }
         case 23:
         {
           menuPos = 0;
           Apps();
           break;
         }
         case 24:
         {
           menuPos = 0;
           Apps();
           break;
         }
      }
    }
    else
    {
      switch(Mode)
      {
        case 19:
        {
          pressed = false;
          break;
        }
      }
    }
  }
  else if(ControlPadPin == NumberPadPin)
  {
    if(avgValue > 1020)  //  0  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(shift == 0)
          {
            calcNum[menuPos] *= 10;
            calcNum[menuPos] += 0;
            lcd.print("0");
            Calculator();
            break;
          }
          else if(shift == 1)      //          ^  ------------------------------------------------
          {
            symbols[menuPos] = 94;    // 94 = ASCII "^"
            menuPos++;
            lcd.print("^");
            Calculator();
            break;
          }
        }
        case 5:
        {
          dataReceive();
          break;
        }
        case 15:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 0;
          lcd.print("0");
          mathFunctions();
          break;
        }
        case 18:
        {
          lcd.print("A");
          quizEntry[menuPos] = 65;
          quizEnvironment();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(1));
            break;
          }
      }
    }
    if(avgValue == 0)   //    1  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(shift == 0)
          {
            calcNum[menuPos] *= 10;
            calcNum[menuPos] += 1;
            lcd.print("1");
            Calculator();
            break;
          }
          else if(shift == 1)     //      e    ----------------------------------
          {
            shift = 0;
            lcd.print("e");
            calcNum[menuPos] = 2.71828;
            Calculator();
            break;
          }
        }
        case 5:
        {
          dataSend();
          break;
        }
        case 15:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 1;
          lcd.print("1");
          mathFunctions();
          break;
        }
        case 18:
        {
          lcd.print("B");
          quizEntry[menuPos] = 66;
          quizEnvironment();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(1));
            break;
          }
      }
    }
    if(avgValue > 958 && avgValue < 962)  // 2  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(shift == 0)
          {
            calcNum[menuPos] *= 10;
            calcNum[menuPos] += 2;
            lcd.print("2");
            Calculator();
            break;
          }
          else if(shift == 1)  //    pi --------------------------------
          {
            shift = 0;
            lcd.print("pi");
            calcNum[menuPos]  = 3.14;
            Calculator();
            break;
          }
        }
        case 15:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 2;
          lcd.print("2");
          mathFunctions();
          break;
        }
        case 18:
        {
          lcd.print("C");
          quizEntry[menuPos] = 67;
          quizEnvironment();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(1));
            break;
          }
      }
    }
    if(avgValue > 60 && avgValue < 64)  //  3  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(shift == 0)
          {
            calcNum[menuPos] *= 10;
            calcNum[menuPos] += 3;
            lcd.print("3");
            Calculator();
            break;
          }
          else if(shift == 1)    //    squareroot
          {
            shift = 0;
            lcd.print("RT");
            specFunc[menuPos]  = 40;    // do the inside if sqrt first "("
            operation[menuPos] = 4;    // Not ASCII but it represents the squareroot present
            menuPos++;
            Calculator();
            break;
          }
        }
        case 15:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 3;
          lcd.print("3");
          mathFunctions();
          break;
        }
        case 18:
        {
          lcd.print("D");
          quizEntry[menuPos] = 68;
          quizEnvironment();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(1));
            break;
          }
      }
    }
    if(avgValue > 895 && avgValue < 899)  //  4  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(shift == 0)
          {
            calcNum[menuPos] *= 10;
            calcNum[menuPos] += 4;
            lcd.print("4");
            Calculator();
            break;
          }
          else if(shift == 1)  //    ( --------------------------------
          {
            shift = 0;
            lcd.print("(");
            specFunc[menuPos]  = 40;
            Calculator();
            break;
          }
        }
        case 15:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 4;
          lcd.print("4");
          mathFunctions();
          break;
        }
        case 18:
        {
          lcd.print("D");
          delay(2000);
          quizEnvironment();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(1));
            break;
          }
      }
    }
    if(avgValue > 123 && avgValue < 127)  //  5  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(shift == 0)
          {
            calcNum[menuPos] *= 10;
            calcNum[menuPos] += 5;
            lcd.print("5");
            Calculator();
            break;
          }
          else if(shift == 1)  //    ) --------------------------------
          {
            shift = 0;
            lcd.print(")");
            specFunc[menuPos]  = 41;
            Calculator();
            break;
          }
        }
        case 15:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 5;
          lcd.print("5");
          mathFunctions();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(1));
            break;
          }
      }
    }
    if(avgValue > 832 && avgValue < 837)  //  6  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(shift == 0)
          {
            calcNum[menuPos] *= 10;
            calcNum[menuPos] += 6;
            lcd.print("6");
            Calculator();
            break;
          }
          else if(shift == 1)
          {
            shift = 0;
            lcd.print("sin(");
            specFunc[menuPos]  = 40;    // do the inside if sine first "("
            operation[menuPos] = 1;    // 1 is sine function 
            Calculator();
            break;
          }
        }
        case 15:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 6;
          lcd.print("6");
          mathFunctions();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(1));
            break;
          }
      }
    }
    if(avgValue > 186 && avgValue < 190)  //  7  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(shift == 0)
          {
            calcNum[menuPos] *= 10;
            calcNum[menuPos] += 7;
            lcd.print("7");
            Calculator();
            break;
          }
          else if(shift == 1)
          {
            shift = 0;
            lcd.print("cos(");
            specFunc[menuPos]  = 40;    // do the inside if cosine first "("
            operation[menuPos] = 2; // 2 is cosine function
            Calculator();
            break;
          }
        }    
        case 15:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 7;
          lcd.print("7");
          mathFunctions();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(1));
            break;
          }
      }
    }
    if(avgValue > 769 && avgValue < 774)  //  8  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(shift == 0)
          {
            calcNum[menuPos] *= 10;
            calcNum[menuPos] += 8;
            lcd.print("8");
            Calculator();
            break;
          }
          else if(shift == 1)
          {
            shift = 0;
            lcd.print("tan(");
            specFunc[menuPos]  = 40;    // do the inside if tangent first "("
            operation[menuPos] = 3; // 3 is tangent function
            Calculator();
            break;
          }
        }
        case 15:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 8;
          lcd.print("8");
          mathFunctions();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(1));
            break;
          }
      }
    }
    if(avgValue > 249 && avgValue < 252)  //  9  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 9;
          lcd.print("9");
          Calculator();
          break;
        }
        case 15:
        {
          calcNum[menuPos] *= 10;
          calcNum[menuPos] += 9;
          lcd.print("9");
          mathFunctions();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(1));
            break;
          }
      }
    }   
  } 
  else if(ControlPadPin == SymbolPadPin)  //    This is the symbol pad
  {
    if(avgValue > 1020)  //  +  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(nosymbol == true)      // If there is no symbols right before, then do this
          {
            nosymbol = false;
            symbols[menuPos] = 43;    // 43 = ASCII "+"
            menuPos++;
            lcd.print("+");
            Calculator();
            break;
          }
          else if(nosymbol == false)
          {
            // do nothing
            break;
          }
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(3));
            break;
          }
      }
    }
    else if(avgValue > 765 && avgValue < 769)  //  -  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(nosymbol == false)
          {
            nosymbol = true;
            symbols[menuPos] = 45;    // 45 = ASCII "-"
            menuPos++;
            lcd.print("-");
            Calculator();
            break;
          }
          else if(nosymbol == true)
          {
            // do nothings
            break;
          }
        }
        case 15:
        {
 //         mathFuncString += ",";
 //         lcd.print(",");
          Calculator();
          break;
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(3));
            break;
          }
      }
    }
    if(avgValue > 509 && avgValue < 513)  //  *  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(nosymbol == true)
          {
            nosymbol = false;
            symbols[menuPos] = 42;    // 42 = ASCII "*"
            menuPos++;
            lcd.print("*");
            Calculator();
            break;
          }
          else if(nosymbol == false)
          {
            // do nothing
            break;
          }
        }
        case 21:
          {
            lcd.clear();             
            lcd.print(analogRead(3));
            break;
          }
      }
    }
    if(avgValue > 250 && avgValue < 260)  //  /  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          if(nosymbol == true)
          {
            nosymbol = false;
            symbols[menuPos] = 47;    // 47 = ASCII "/"
            menuPos++;
            lcd.print("/");
            Calculator();
            break;
          }
          else if(nosymbol == false)
          {
            // do nothing
            break;
          }
        }
        case 21:
        {    
            lcd.clear();        
            lcd.print(analogRead(3));
            break;
        }
      }
    }
    if(avgValue == 0)  //  =  ---------------------------------------
    {
      switch(Mode)
      {
        case 0:
        {
          break;
        }
        case 1:
        {
          lcd.print("=");
          symbols[menuPos] = 61;    // 61 = ASCII "="
//          Serial.println("I am equal!!");
          Calculator();
          break;
        }
        case 21:
          {
            lcd.clear();            
            lcd.print(analogRead(3));
            break;
          }
      }
    }
  } 
}

void Select()  //-------------------------------------------------------------------------  Select  -----------------------------------------------------
{
  if(Mode == 0)
  {
    switch(menuPos)    //----------------    Main Menu
    {
      case 0:
      {
        menuPos = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
//        lcd.autoscroll();
        Calculator();
        break;
      }
      case 1:
      {
        menuPos = 0;
        QuizMode();
        break;
      }
      case 2:
      {
        menuPos = 0;
        Apps(); 
        break;
      }
      case 3:
      {
        menuPos = 0;
        Settings();
         break;
      }
      case 4:
      {
        menuPos = 0;
        Chat();
        break;
      }
    }
  } 
  else if(Mode == 2)            //  ------------   App Mode
  {
    switch(menuPos)
    {
      case 0:
      {
        menuPos = 0;
        quizPick();
        break;
      }
      case 1:
      {
        menuPos = 0;
        DownloadQuiz();
        break;
      }
      case 2:
      {
        menuPos = 0;
        UploadQuiz();
        break;
      }
      case 3:
      {
        menuPos = 0;
        getResults();
        break;
      }
      case 4:
      {
        menuPos = 0;
//        makeQuiz();
        break;
      }
      case 5:
      {
        menuPos = 0;
//        deleteQuiz();
        break;
      }
      case 6:
      {
        menuPos = 0;
        MainMenu();
        break;
      }
      
    }
  }
  else if(Mode == 3)      //        ----------- Apps ----------------------------
  {
    switch(menuPos)
    {
      case 0:
      {
        menuPos = 0;
        Timer();
        break;
      }
      case 1:
      {
        menuPos = 0;
        lcd.clear();
        MorseCode();
        break;
      }
      case 2:
      {
        menuPos = 0;
        Temperature();
        break;
      }
      case 3:
      {
        menuPos = 0;
        FlashCards();
        break;
      }
      case 4:
      {
        menuPos = 0;
        Buzzer();
        break;
      }
      case 5:
      {
        menuPos = 0;
        entryLaserLine();
        break;
      }
      case 6:
      {
        menuPos = 0;
        mathFunctions();
        break; 
      }
    } 
  }
  else if(Mode == 4)
  {
    switch(menuPos)
    {
      case 1:
      {
        deviceInformation();
        break;
      }
      case 2:
      {
        SplashScreen();
        break;
      }
      case 3:
      {
        ButtonTester();
        break;
      }
      case 4:
      {
        menuPos = 0;
        MainMenu();
        break;
      }
    }
  }
  else if(Mode == 8)
  {
    if(on == true)
    {
      on = false;
      Timer();
    }
    else if(on == false)
    {
      on = true;
      Timer();
    }
  }
  else if(Mode == 9)    
  {
    switch(menuPos)
    {
      case 0:
      {
        menuPos = 0;
        quiz = 1;
        entryNumber = sizeof(calcQuizEntry)/ sizeof(char);
        for(byte s = 0; s < entryNumber; s++)
        {
           quizEntry[s] = calcQuizEntry[s];
        }
        quizEnvironment();
        break; 
      }
      case 1:
      {
        menuPos = 0;
        quiz = 2;
        entryNumber = sizeof(physicsQuizEntry)/ sizeof(char);
        for(byte s = 0; s < entryNumber; s++)
        {
           quizEntry[s] = physicsQuizEntry[s];
        }
        quizEnvironment();
        break; 
      }
      case 2:
      {
        menuPos = 0;
        quiz = 3;
        entryNumber = sizeof(statQuizEntry)/ sizeof(char);
        for(byte s = 0; s < entryNumber; s++)
        {
           quizEntry[s] = statQuizEntry[s];
        }
        quizEnvironment();
        break;
      }
    }
  }
  else if(Mode == 12)
  {
    switch(menuPos)
    {
      case 0:
      {
        quiz = 1;
        seeGottenResults();
        break;
      }
      case 1:
      {
        quiz = 2;
        seeGottenResults();
        break;
      }
      case 2:
      {
        quiz = 3;
        seeGottenResults();
        break;
      }
    }
  }
  else if(Mode == 15)
  {
    switch(menuPos)
    {
      case 0:
      {
        menuPos = 0;
        Pythagorean();
        break;
      }
/*      case 1:
      {
        menuPos = 0;
 //       MidpointFormula();
        break;
      }
      case 2:
      {
        menuPos = 0;
//        QuadraticFormula();
        break;
      } */
   }   
  }
}

void MainMenu()
{
//  lcd.noAutoscroll();
  
  Mode = 0;
  lcd.clear();
  lcd.print("Choose Program:");
  lcd.setCursor(0, 1);
  
  if(menuPos < 0)
  {
    menuPos = 0;
  }
  
  else if(menuPos == menuOptionsSize)
  {
    menuPos -= 1;
  }
  strcpy_P(buffer, (char*)pgm_read_word(&(menuOptions_table[menuPos])));
//  lcd.print(menuOptions[menuPos]);         The Old
  lcd.print(buffer);               //        The New - This will draw from program flash instead of SRAM

}

void Settings()
{
  Mode = 4;
  lcd.clear();
  lcd.print("Choose Option:");
  lcd.setCursor(0, 1);
  
  if(menuPos < 0)
  {
    menuPos = 0;
  }
  
  else if(menuPos == settingOptionsSize)
  {
    menuPos -= 1;
  }
  strcpy_P(buffer, (char*)pgm_read_word(&(settingOptions_table[menuPos])));
//  lcd.print(settingOptions[menuPos]);      The Old
  lcd.print(buffer);               //        The New - This will draw from program flash instead of SRAM

}

void QuizMode()
{
//  String quizOptions[] = {"(0)Pick A Quiz", "(1)Download Quiz", "(2)Upload Quiz", "(3)See Results", "(4)Make a Quiz", "(5)Delete Quiz", "(6)Main Menu"};
  Mode = 2;
  lcd.clear();
  lcd.print("Choose Option:");
  lcd.setCursor(0, 1);
  if(menuPos < 0)
  {
    menuPos = 0;
  }  
  else if(menuPos == quizOptionsSize)
  {
    menuPos -= 1;
  }
  strcpy_P(buffer, (char*)pgm_read_word(&(quizOptions_table[menuPos])));
  //lcd.print(quizOptions[menuPos]);        The Old
  lcd.print(buffer);               //       The New - This will draw from program flash instead of SRAM
}

void quizPick()
{
  Mode = 9;
  lcd.clear();
  lcd.print("Choose A Quiz");
  lcd.setCursor(0, 1);
  if(menuPos < 0)
  {
    menuPos = 0;
  }
  else if(menuPos == quizSelectSize)    // This number needs to change based on the quizzes that come in
  {
    menuPos -= 1;
  } 
  strcpy_P(buffer, (char*)pgm_read_word(&(quizSelect_table[menuPos])));
  lcd.print(buffer);
}

void Apps()
{
  Mode = 3;
  lcd.clear();
  lcd.print("Choose An App");
  lcd.setCursor(0, 1);
  if(menuPos < 0)
  {
    menuPos = 0;
  }
  else if(menuPos == appOptionsSize)
  {
    menuPos -= 1;
  }
  strcpy_P(buffer, (char*)pgm_read_word(&(appOptions_table[menuPos])));
  lcd.print(buffer);   
}

void mathFunctions()
{
  Mode = 15;
  lcd.clear();
  lcd.print("Math Functions");
  lcd.setCursor(0, 1);
  if(menuPos < 0)
  {
    menuPos = 0;
  }
  else if(menuPos == mathFunctionsSize)
  {
    menuPos -= 1;
  }
  strcpy_P(buffer, (char*)pgm_read_word(&(mathFunctions_table[menuPos])));
  lcd.print(buffer);
  
  if(MathFunc == 1)
  {
    Pythagorean();
  }
}

void Chat()
{
  Mode = 5;
  lcd.clear();
  lcd.print("(0) Receive");
  lcd.setCursor(0, 1);
  lcd.print("(1) Send");
}
