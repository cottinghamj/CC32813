byte Morsecode[5]; // 1 = short --- 2 = long
byte n;  //
byte t;   //

void MorseCode()
{
  Mode = 19;
  lcd.setCursor(16, 1);
  lcd.autoscroll();
  if(avgValue == 0)
    {
      delay(150); // adjust this number for the break between shorts or longs
      avgValue = analogRead(ArrowPadPin); // Is the button still being held down???
      if(avgValue == 0)    // It is, so it must be a long
      {
//        Serial.println("high");
        Morsecode[n] = 2;
        n++;
        if(n == 5)
        {
          t = 0;
          for(int j; j < 5; j++)
          {
//            Serial.println(Morsecode[j]);
            Morsecode[j] = 0;
          }
          n = 0;
        }
        while(avgValue == 0)
        {
          delay(1);
          avgValue = 0;
          value[5];     // Can change this number to affect the accuracy of clicks
          delay(5);
          for(int i = 0; i < 5; i++) // Can change this number to affect the accuracy of clicks
          {
            value[i] = analogRead(ArrowPadPin);
            delay(5);
            if(i != 0)
            {
              value[i] = value[i] + value[i - 1];
            } 
          }
          avgValue = value[4] / 5; // This is the value that will be used to determine button pushed 
              }
            }
      else // its not still being held, it must be a short
      {
        t = 0;
//        Serial.println("low");
        Morsecode[n] = 1;
        n++;
        if(n == 5)
        {
          for(int j; j < 5; j++)
          {
//            Serial.println(Morsecode[j]);
            Morsecode[j] = 0;
          }
          n = 0;
        }
      }
    }
    else if(avgValue > 0)
    {
//      Serial.println("hey");
      delay(1);
      t++;
      if(t == 8)
      {
        interpretMorse();
        for(int j = 0; j < 5; j++)
          {
 //           Serial.println(Morsecode[j]);
            Morsecode[j] = 0;
          }
          n = 0;
          t = 0;
      }
    }
}

void interpretMorse()
{
  byte m = 0;
    if(Morsecode[m] == 1)
    {
      if(Morsecode[m+1] == 0)
      {
          lcd.print("E");
      }
      else if(Morsecode[m+1] == 1)
      {
        if(Morsecode[m+2] == 0)
        {
            lcd.print("I");
        }
        else if(Morsecode[m+2] == 1)
        {
          if(Morsecode[m+3] == 0)
          {
              lcd.print("S");
          }
          else if(Morsecode[m+3] == 1)
          {
              if(Morsecode[m+4] == 0)
              {
                  lcd.print("H");
              }
              else if(Morsecode[m+4] == 1)
              {
                  lcd.print("5");
              }
              else if(Morsecode[m+4] == 2)
              {
                  lcd.print("4");
              }
          }
          else if(Morsecode[m+3] == 2)
          {
              if(Morsecode[m+4] == 0)
              {
                  lcd.print("V");
              }
              else if(Morsecode[m+4] == 1)
              {
                  // print nothing
              }
              else if(Morsecode[m+4] == 2)
              {
                  lcd.print("3");
              }
          }
        }
        else if(Morsecode[m+2] == 2)
        {
            if(Morsecode[m+3] == 0)
            {
                lcd.print("U");
            }
            else if(Morsecode[m+3] == 1)
            {
                lcd.print("F");
            }
            else if(Morsecode[m+3] == 2)
            {
                if(Morsecode[m+4])
                {
                    lcd.print("2");
                }
            }
        }
      }
      else if(Morsecode[m+1] == 2)
      {
          if(Morsecode[m+2] == 0)
          {
              lcd.print("A");
          }
          else if(Morsecode[m+2] == 1)
          {
              if(Morsecode[m+3] == 0)
              {
                  lcd.print("R");
              }
              else if(Morsecode[m+3] == 1)
              {
                  if(Morsecode[m+4] == 0)
                  {
                      lcd.print("L");
                  }
              }
          }
        else if(Morsecode[m+2] == 2)
        {
            if(Morsecode[m+3] == 0)
            {
                lcd.print("W");
            }
            else if(Morsecode[m+3] == 1)
            {
                if(Morsecode[m+4] == 0)
                {
                    lcd.print("P");
                }
            }
            else if(Morsecode[m+3] == 2)
            {
                if(Morsecode[m+4] == 0)
                {
                    lcd.print("J");
                }
                else if(Morsecode[m+4] == 2)
                {
                    lcd.print("1");
                }
            }
         }
        }
      }      
    else if(Morsecode[m] == 2)
    {
        if(Morsecode[m+1] == 0)
        {
            lcd.print("T");
        }
        else if(Morsecode[m+1] == 1)
        {
            if(Morsecode[m+2] == 0)
            {
                lcd.print("N");
            }
            else if(Morsecode[m+2] == 1)
            {
                if(Morsecode[m+3] == 0)
                {
                    lcd.print("D");
                }
                else if(Morsecode[m+3] == 1)
                {
                    if(Morsecode[m+4] == 0)
                    {
                        lcd.print("B");
                    }
                    else if(Morsecode[m+4] == 1)
                    {
                        lcd.print("6");
                    }
                    else if(Morsecode[m+4] == 2)
                    {
                        lcd.print("=");
                    }
                }
                else if(Morsecode[m+3] == 2)
                {
                    if(Morsecode[m+4] == 0)
                    {
                        lcd.print("X");
                    }
                    else if(Morsecode[m+4] == 1)
                    {
                        lcd.print("/");
                    }
                }
            }
            else if(Morsecode[m+2] == 2)
            {
                if(Morsecode[m+3] == 0)
                {
                    lcd.print("K");
                }
                else if(Morsecode[m+3] == 1)
                {
                    if(Morsecode[m+4] == 0)
                    {
                        lcd.print("C");
                    }
                }
                else if(Morsecode[m+3] == 2)
                {
                    if(Morsecode[m+4] == 0)
                    {
                        lcd.print("Y");
                    }
                }
            }
        }
        else if(Morsecode[m+1] == 2)
        {
            if(Morsecode[m+2] == 0)
            {
                lcd.print("M");
            } 
            else if(Morsecode[m+2] == 1)  
            {
                if(Morsecode[m+3] == 0)
                {
                     lcd.print("G"); 
                }
                else if(Morsecode[m+3] == 1)
                {
                    if(Morsecode[m+4] == 0)
                    {
                        lcd.print("Z");
                    }
                    if(Morsecode[m+4] == 1)
                    {
                        lcd.print("7");
                    }
                }
                else if(Morsecode[m+3] == 2)  
                {
                    if(Morsecode[m+4] == 0)
                    {
                        lcd.print("Q");
                    }
                }
            }
            else if(Morsecode[m+2] == 2) 
            {
                if(Morsecode[m+3] == 0)
                {
                    lcd.print("O");
                }
                if(Morsecode[m+3] == 1)
                {
                    if(Morsecode[m+4] == 1)
                    {
                        lcd.print("8");
                    }
                }
                if(Morsecode[m+3] == 2)
                {
                    if(Morsecode[m+4] == 1)
                    {
                        lcd.print("9");
                    }
                    if(Morsecode[m+3] == 2)
                    {
                        lcd.print("0");
                    }
                }
            }  
        }
    }
    for(byte me; me < 5; me++)
    {
      Morsecode[me] = 0;
    }
  }
