String Screen[] = {"    C","    CC","    CC3","    CC32","    CC328","    CC3281", "    CC32813"};
String Screen2[] = {">              <",">>            <<",">>>          <<<",">>>>        <<<<",">>>>>      <<<<<",">>>>>>    <<<<<<",">>>>>>>  <<<<<<<", ">>>>>>>><<<<<<<<"};

void SplashScreen()
{
  lcd.clear();
  lcd.print("    Welcome    ");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("      To       ");
  delay(1000);
  lcd.clear();
  for(int i = 0; i < 7; i++)
  {
     lcd.print(Screen[i]);
     delay(500);
     lcd.clear(); 
  }
  for(int i = 0; i < 6; i++)
  {
    delay(50);
    for(int j = 0; j < 8; j++)
    {
      lcd.clear();
      lcd.print(Screen[6]);
      lcd.setCursor(0, 1);
      lcd.print(Screen2[j]);
      delay(50); 
    }
  }
  delay(2000);
  if(Mode == 4)
  {
    Settings();
  }
  else
  {
    MainMenu();
  }
}
