void Temperature()
{
  Mode = 16;
  lcd.clear();                           
  lcd.print(" Temperature: ");
  lcd.setCursor(0, 1);
  int temp;
  temp = analogRead(3);
  temp /= 6.8181;
  lcd.print("      ");
  if(Celsius == true)
  {
    lcd.print(temp);
    lcd.print("C");
  }
  else if(Celsius == false)
  {
    temp *= 1.8;
    temp += 32;
    lcd.print(temp);
    lcd.print("F");
  }
}
