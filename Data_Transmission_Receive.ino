byte count;
byte cycle;
byte transferArray[30];

void dataReceive()
{
  Mode = 23;
  lcd.clear();
  //  count = 0;
  lcd.clear();
  int value = analogRead(5);
  lcd.print(value);
//  delay(100);
  if(value >= 955)
  {
    lcd.clear();
//    lcd.print(count);
    cycle = 0;
    count++;
    delay(70); // 70 is the threshold. Any faster and it will read incorrectly. MUST MATCH with Sender!
  }
  if(value < 955)
  {
    lcd.clear();
//    lcd.print("in the other");
    cycle = cycle + 1;
    delay(50);
    if(cycle == 4)
    {
       readCycle(count); 
       delay(100);
       count = 0;
    }
  }
}

void readCycle(int count)
{
  switch(count)
  {
      case 1:
      {
        lcd.clear();
        lcd.print("A");
        break;
      }
      case 2:
      {
        lcd.clear();
        lcd.print("B");
        break;
      }
      case 3:
      {
        lcd.clear();
        lcd.print("C");
        break;
      }
      case 4:
      {
        lcd.clear();
        lcd.print("D");
        break;
      }
      case 5:
      {
        lcd.clear();
        lcd.print("E");
        break;
      }
      case 6:
      {
        lcd.clear();
        lcd.print("F");
        break;
      }
      case 7:
      {
        lcd.clear();
        lcd.print("G");
        break;
      }
      case 8:
      {
        lcd.clear();
        lcd.print("H");
        break;
      }
      case 9:
      {
        lcd.clear();
        lcd.print("I");
        break;
      }
      case 10:
      {
        lcd.clear();
        lcd.print("J");
        break;
      }
      case 11:
      {
        lcd.clear();
        lcd.print("K");
        break;
      }
      case 12:
      {
        lcd.clear();
        lcd.print("L");
        break;
      }
      case 13:
      {
        lcd.clear();
        lcd.print("M");
        break;
      }
      case 14:
      {
        lcd.clear();
        lcd.print("N");
        break;
      }
      case 15:
      {
        lcd.clear();
        lcd.print("O");
        break;
      }
      case 16:
      {
        lcd.clear();
        lcd.print("P");
        break;
      }
      case 17:
      {
        lcd.clear();
        lcd.print("Q");
        break;
      }
      case 18:
      {
        lcd.clear();
        lcd.print("R");
        break;
      }
      case 19:
      {
        lcd.clear();
        lcd.print("S");
        break;
      }
      case 20:
      {
        lcd.clear();
        lcd.print("T");
        break;
      }
      case 21:
      {
        lcd.clear();
        lcd.print("U");
        break;
      }
      case 22:
      {
        lcd.clear();
        lcd.print("V");
        break;
      }
      case 23:
      {
        lcd.clear();
        lcd.print("W");
        break;
      }
      case 24:
      {
        lcd.clear();
        lcd.print("X");
        break;
      }
      case 25:
      {
        lcd.clear();
        lcd.print("Y");
        break;
      }
      case 26:
      {
        lcd.clear();
        lcd.print("Z");
        break;
      }
  }
}
