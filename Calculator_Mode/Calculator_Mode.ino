/* Successful Orders Of Operation. Getting to clear for new prob correctly
*/

//parNum[10];    //  Parentheses Number Array
//parSym[10];      //  Parentheses Symbols Array

void Calculator()
{
  cursorTrack++;
  delay(5);
  Mode = 1;
  SimpleCheck();
  if(symbols[menuPos] == 61)    //  Equal sign means to start solving
  {
    PEMDAS();
    menuPos = 0;
    Answer = calcNum[menuPos];
    calcNum[menuPos] = 0;
  }
//  else if(specFunc[menuPos] == 40)  
//  {
//    if(calcNum[menuPos] > 0 || calcNum[menuPos] < 0)
//    {
//      symbols[menuPos] = 42;      // 2(2) = 2 * 2
//      menuPos++;
//    }
//    openPar[menuPos] = menuPos;
//    Parentheses();
//  }
}

void SimpleCheck()
{
}

void PEMDAS()
{
  while(turn < 17)  // This determines the number of rounds to do
  {
    turn++;    // This is the round of operation to perform. Round 1-5 is mult and div for now
    for(int m = 0; m <= menuPos; m++)    // the last menuPos will always be "=" or ) 
    { 
      if(turn <= 5)
      {
        if(symbols[m] == 94)
        {
          Solver(symbols[m], calcNum[m], calcNum[m + 1], m);
        }
      }
      else if(turn > 5 && turn <= 10)
      {
        if(symbols[m] == 42 || symbols[m] == 47)
        {
          if(symbols[m-1] == 45)
          {
            symbols[m-1] = 43;
            calcNum[m] *= -1;
          }
          Solver(symbols[m], calcNum[m], calcNum[m + 1], m);  // Filling parameters 
        }
      }
      else if(turn > 10 && turn <= 15 )
      {
        if(symbols[m] == 43 || symbols[m] == 45)
        {
          if(symbols[m] == 45)
          {
            symbols[m] = 43;
            calcNum[m+1] = calcNum[m+1] * -1;
          }
          Solver(symbols[m], calcNum[m], calcNum[m + 1], m);
        }
      }
      else if(turn == 16)
      {
        if(symbols[m] == 61)
        {
          Solver(symbols[m], calcNum[m], calcNum[m + 1], m);
        }
      }
    }    
  }
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(calcNum[0]);
  turn = 0;
  cursorTrack = 0;
  delay(1);
  lcd.setCursor(0,0);
  menuPos = 0;
  for(int j = 0; j < sizeof(symbols)/ sizeof(byte); j++)  // Need to get rid of any equal signs whereever they are -- This clears every slot
  {
    symbols[j] = 0;
    specFunc[j] = 0;    // Also get rid of any special functions
  }
}

void Solver(byte symbol, float A, float B, byte m)
{
  switch(symbol)
  {
    case 42:      //    Multiplication
    {
      A = A * B;
      calcNum[m] = A; 
      Sort(m);
      break;
    }
    case 43:      //    Addition
    {
      A = A + B;
      calcNum[m] = A;
      Sort(m);
      break;
    }
    case 45:      //    Subtraction
    {
      A = A - B;
      calcNum[m] = A;
      Sort(m);
      break;
    }
    case 47:      //    Division
    {
      A = A / B;
      calcNum[m] = A;
      Sort(m);
      break;
    }
//    case 61:      //    Equal Sign
//    {
//      Answer = A;
//      lcd.setCursor(14,1);
//      lcd.print(A);
//      break; 
//    }
    case 94:    //    Exponents
    {
      A = pow(A, B);
      calcNum[m] = A;
      Sort(m);
      break;
    }
  }
}



void Parentheses()
{
  if(specFunc[menuPos] == 41)
  {
    for(byte q = menuPos; q > -1; q--)
    {
      if(specFunc[q] == 40)
      {
        insidePEMDAS(q);
//        Serial.println(q);
        if(operation[q-1] == 1)
        {
          calcNum[q] = sin(calcNum[q]);
        }
        else if(operation[q] == 2)
        {
          calcNum[q] = cos(calcNum[q]);
        }
        else if(operation[q] == 3)
        {
          calcNum[q] = tan(calcNum[q]);
        }
        else if(operation[q] == 4)
        {
          calcNum[q] = sqrt(calcNum[q]);
        }
        q = -1;
      }
    }
  }
}

void insidePEMDAS(byte n)
{
  while(turn < 16)  // This determines the number of rounds to do
  {
    turn++;    // This is the round of operation to perform. Round 1-5 is mult and div for now
    for(n; n <= menuPos; n++)    // the last menuPos will always be "=" or ) 
    { 
      if(turn <= 5)
      {
        if(symbols[n] == 94)
        {
          Solver(symbols[n], calcNum[n], calcNum[n + 1], n);
        }
      }
      else if(turn > 5 && turn <= 10)
      {
        if(symbols[n] == 42 || symbols[n] == 47)
        {
          Solver(symbols[n], calcNum[n], calcNum[n + 1], n);  // Filling parameters 
        }
      }
      else if(turn > 10 && turn <= 15 )
      {
        if(symbols[n] == 43 || symbols[n] == 45)
        {
          if(symbols[n] == 45)
          {
            symbols[n] = 43;
            calcNum[n+1] = calcNum[n+1] * -1;
          }
          Solver(symbols[n], calcNum[n], calcNum[n + 1], n);
        }
      }
    }    
  }
}

void Sort(byte s) 
{
  for(s += 1; s <= menuPos; s++)
  {
    if(symbols[s] == 61) 
    {
      for(byte g = menuPos; g < sizeof(calcNum)/ sizeof(int); g++)
      {
        calcNum[s+1] = 0;
        symbols[s] = symbols[s+1];
        symbols[s+1] = 0;
      }
    }
    calcNum[s] = calcNum[s + 1];
    symbols[s - 1] = symbols[s]; 
  } 
}

void Delete()
{
  if(symbols[menuPos] > 0)
  {
    symbols[menuPos = 0];
    menuPos--;
    cursorTrack--;
    lcd.setCursor(0, cursorTrack);
    lcd.print(symbols[menuPos + 1]);
  }
  else
  {
    
    
  }
}
