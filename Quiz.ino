// Pretty much done with the quiz function, might look into EEPROM saving and deleting

void DownloadQuiz()
{
  lcd.clear();
  lcd.print("Downloading");
  delay(3000);
  QuizMode();
}

void UploadQuiz()
{
  lcd.clear();
  lcd.print("Uploading");
  delay(3000);
  QuizMode();
}

void getResults()
{
  Mode = 12;
  lcd.clear();
  lcd.print("Choose A Quiz");
  lcd.setCursor(0, 1);
  if(menuPos < 0)
  {
    menuPos = 0;
  }
  else if(menuPos == entryNumber)    // Can't have more entries than answers
  {
    menuPos -= 1;
  } 
  strcpy_P(buffer, (char*)pgm_read_word(&(quizSelect_table[menuPos])));
  lcd.print(buffer); 
}

void seeGottenResults()
{
  Mode = 20;
  switch(quiz)
  {
    case 1:
    {
      for(byte a = 0; a < sizeof(calcQuizEntry)/ sizeof(char); a++)
      {
        if(calcQuizEntry[a] == calcQuizAnswers[a])
        {
          points++;
        }
        else if(calcQuizEntry[a] != calcQuizAnswers[a])
        {
          // do not count as another point
        }
      }
      lcd.clear();
      lcd.print("   You scored:   ");
      lcd.setCursor(0,1);
      lcd.print(points);
      lcd.print("/");
      lcd.print(sizeof(calcQuizEntry)/ sizeof(char));
      lcd.print("  =  ");
      float score = sizeof(calcQuizEntry)/ sizeof(char);
      score = points / score;
      score *= 100;
      lcd.print(score);
      lcd.print("%");
      points = 0;
      break;
    }
    case 2:
    {
      for(byte a = 0; a < sizeof(physicsQuizEntry)/ sizeof(char); a++)
      {
        if(physicsQuizEntry[a] == physicsQuizAnswers[a])
        {
          points++;
        }
        else if(physicsQuizEntry[a] != physicsQuizAnswers[a])
        {
          // do not count as another point
        }
      }
      float score = sizeof(physicsQuizEntry)/ sizeof(char);
      lcd.clear();
      lcd.print("   You scored:   ");
      lcd.setCursor(0,1);
      lcd.print(points);
      lcd.print("/");
      lcd.print(sizeof(physicsQuizEntry)/ sizeof(char));    // Want it to print out integer instead of decimal
      lcd.print("  =  ");
      score = points / score;
      score *= 100;
      lcd.print(score);
      lcd.print("%");
      points = 0;
      break;
    }
    case 3:
    {
      for(byte a = 0; a < sizeof(statQuizEntry)/ sizeof(char); a++)
      {
        if(statQuizEntry[a] == statQuizAnswers[a])
        {
          points++;
        }
        else if(statQuizEntry[a] != statQuizAnswers[a])
        {
          // do not count as another point
        }
      }
      float score = sizeof(statQuizEntry)/ sizeof(char);
      lcd.clear();
      lcd.print("   You scored:   ");
      lcd.setCursor(0,1);
      lcd.print(points);
      lcd.print("/");
      lcd.print(sizeof(statQuizEntry)/ sizeof(char));
      lcd.print("  =  ");
      score = points / score;
      score *= 100;
      lcd.print(score);
      lcd.print("%");
      points = 0;
      break;
    }
  }
}

void quizEnvironment()    
{
 // lcd.blink();
  Mode = 18;
  lcd.clear();
  if(menuPos < 0)
  {
    menuPos = 0;
  }
  else if(menuPos == entryNumber)
  {
    menuPos -= 1;
  }
  if(quizEntry[menuPos] == 0)
  {
    quizEntry[menuPos] = 32;    // Makes the output a blank space
    if(quizEntry[menuPos+1] == 0)
    {
      quizEntry[menuPos+1] = 32;    // Makes the output a blank space
    }
  }
  lcd.print(menuPos+1);
  lcd.print(".");
  lcd.setCursor(0,1);
  
  if((menuPos+1) == entryNumber)
  {
    
  }
  else if((menuPos+1) < entryNumber)
  {
    lcd.print((menuPos+2));
    lcd.print(".");
    lcd.print(quizEntry[menuPos+1]);
  }
  if(menuPos < 9)
  {
    lcd.setCursor(2,0);
  }
  else if(menuPos >= 9 && menuPos < 98)
  {
    lcd.setCursor(3,0);
  }
  lcd.print(quizEntry[menuPos]);
}
