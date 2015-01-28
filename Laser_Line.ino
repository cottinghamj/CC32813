long int time;
int raceValue;
int runningValue;

void entryLaserLine()
{
  lcd.clear();
  delay(1500);
  Mode = 25;
}

void shortGet()
{
  for(int i = 0; i < 3; i++) // Can change this number to affect the accuracy of clicks
    {
      value[i] = analogRead(0);
      delay(30);
      if(i != 0)
      {
        value[i] = value[i] + value[i - 1];
      } 
    }
    avgValue = value[2] / 3; // This is the value that will be used to determine button pushed 
}

void LaserLine()
{
  Mode = 25;
  shortGet();
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
      time = time + 90; // compensating delay in getValue
      delay(1);
      lcd.setCursor(7, 1);
      lcd.print(time);
      shortGet();
      runningValue = analogRead(4);
      if(runningValue < (raceValue - 100))
      {
        lcd.clear();
        lcd.print("Finished!");
        lcd.setCursor(7, 1);
        lcd.print(time);
        avgValue = 0;
//        while(1)
//        {
//          delay(1);
//        }
      }
    }
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
