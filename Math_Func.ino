//prog_char FlashCards_0[] PROGMEM = "Pythagorean";
//prog_char FlashCards_1[] PROGMEM = "MidPoint Form";
//prog_char FlashCards_2[] PROGMEM = "Distance Form";

// Have a function definition page somewhere in the calc programming
// You need to make an app interface to use this

void Pythagorean()
{
  lcd.clear();
  MathFunc = 1;
  float A, B, C;
  A = calcNum[0];
  B = calcNum[1];
  C = calcNum[2];
  if(menuPos == 0)
  {
    lcd.print("A = ");
    lcd.print(A);
  }
  else if(menuPos == 1)
  {
    lcd.print("B = ");
    lcd.print(B);
  }
  else if(menuPos == 2)
  {
    lcd.print("C = ");
    lcd.print(C);
  }
  if(menuPos == 3)
  {
    if(A > 0 && B > 0 && C == 0)
    {
      A = A * A;
      B = B * B;
      A = A + B;
      C = sqrt(A);
      lcd.print(C);
    }
    else if(A > 0 && B == 0 && C > 0)
    {
      A = A * A;
      C = C * C;
      C = C - A;
      B = sqrt(C);
      lcd.print(B);
    }
    else if(A == 0 && B > 0 && C > 0)
    {
      B = B * B;
      C = C * C;
      C = C - B;
      A = sqrt(C);
      lcd.print(A);
    }
    else if(A > 0 && B > 0 && C > 0)
    {
      A = A * A;
      B = B * B;
      C = C * C;
      A = A + B;
      if(A == C)
      {
        lcd.print("correct");
      }
      else if(A != C)
      {
        lcd.print("incorrect");
      }
    }
  }
  calcNum[0] = 0;
  calcNum[1] = 0;
  calcNum[2] = 0;
}

//void QuadraticFormula(float A, float B, float C)
//{
//  float x;
//  x = -1 * B;
//  B = B * B;
//  B = B - (4*A*C);
//  B = sqrt(B);
//  C = (x + B)/ (2*A);
//  lcd.print(C);
//  lcd.print(", ");
//  C = (x - B)/ (2*A);
//  lcd.print(C);
//}
//
//void MidpointFormula(float xF, float yF, float xS, float yS)      // xF = First X, xS = Second X
//{
//  xF = xF + xS;
//  xF /= 2;
//  yF = yF + yS;
//  yF /= 2;
//  lcd.print("(");
//  lcd.print(xF);
//  lcd.print(",");
//  lcd.print(yF);
//  lcd.print(")");
//}
//
//int Factorial(int F)
//{
//  if(F <= 1)
//  {
//    return 1;
//  }
//  else
//  {
//    return F * Factorial(F - 1);
//  }
//}
