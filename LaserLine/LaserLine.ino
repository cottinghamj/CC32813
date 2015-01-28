#include <LiquidCrystal.h> 
int avgValue;
long int time;
int raceValue;
int runningValue;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  // This code will only run once, after each powerup or reset of the board
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  // This code will loops consecutively
  int val = analogRead(4);
  Serial.println(val);
  LaserLine();
  
}

void LaserLine()
{
  getValue();
  if(avgValue == 0)
  {
    lcd.clear();
    lcd.print("Wait");
    startCounter();
  }
  else if(avgValue > 1020)
  {
    lcd.clear();
    lcd.print("GO!");
    while(avgValue > 0)
    {
      time = time + 30; // compensating delay in getValue
      delay(1);
      lcd.setCursor(7, 1);
      lcd.print(time);
      getValue();
      runningValue = analogRead(4);
      if(runningValue < (raceValue - 100))
      {
        lcd.clear();
        lcd.print("Finished!");
        lcd.setCursor(7, 1);
        lcd.print(time);
        avgValue = 0;
      }
    }
  }
}

void getValue()
{
  for(byte i = 0; i < 3; i++)
  {
    avgValue = 0;
    int value[3];     // Can change this number to affect the accuracy of clicks
      value[i] = analogRead(0);
      delay(30);
      if(i != 0)
      {
        value[i] = value[i] + value[i - 1];
      } 
    avgValue = value[2] / 3; // This is the value that will be used to determine button pushed 
  }
}

void startCounter()
{
  int keepVal[25];
  for(int h = 0; h < 25; h++)
  {
    delay(100);
    keepVal[h] = analogRead(4);
    if(h != 0)
    {
      keepVal[h] = keepVal[h] + keepVal[h - 1];
    }
    if(h % 5 == 0)
    {
      lcd.print(".");
    }
  }
  raceValue = keepVal[24]/ 25;
  lcd.clear();
  lcd.print("Ready at:");
  lcd.setCursor(7, 1);
  lcd.print(raceValue);
}
