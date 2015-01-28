void Timer()
{
  Mode = 8;
  while(on == true)
  {
    getValue();
    lcd.clear();
    lcd.print("     Timer    ");
    lcd.setCursor(7,1);
    lcd.print(seconds);
    if(on == true)
    {
       delay(1000);
       seconds++; 
    }
  }
  if(on == false)
  {
    getValue();
  }
}
