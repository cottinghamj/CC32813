/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;
char quizzes[] = "2 Calculus, Physics C, English 3";
byte i = 0;
  byte a = 1;

void setup()
{
  Serial.begin(9600);
//  locateEEPROMslot();
  Serial.print("Checking");
      locateEEPROMslot();
      for(int j = 0; j < 30; j++)
        {
          delay(10);
          if(EEPROM.read(j) == 3)
          {
            Serial.println("popping out");
            j = a;
          }
          if(EEPROM.read(j) == 44)
          {
            Serial.println();
            j++;
            if(EEPROM.read(j) == 32)
            {
              j++;
            }
          }
        char hey = EEPROM.read(j);
        Serial.print(hey);
        }
      
}

void loop()
{

//  EEPROM.write(addr, quizzes[i]);
//    i++;

  addr = addr + 1;
      if(EEPROM.read(i) == 2)
      {
        Serial.println("bingo");
        for(int j = i + 1; j < a; j++)
        {
          delay(10);
          if(EEPROM.read(j) == 3)
          {
            Serial.println("popping out");
            j = a;
          }
          if(EEPROM.read(j) == 44)
          {
            Serial.println();
            j++;
            if(EEPROM.read(j) == 32)
            {
              j++;
            }
          }
        char hey = EEPROM.read(j);
        Serial.print(hey);
        }
      }
    addr = 0;
    Serial.println();
    delay(100);  
}

//  delay(500);

void locateEEPROMslot()
{
  while(EEPROM.read(a) > 0)
  {
    Serial.println(".");
    
    a++;
  }
  Serial.println(a);    // a is where you will start at 
}
