prog_char FlashCards_0[] PROGMEM = "Pythagorean";
prog_char FlashCards_1[] PROGMEM = "A^2 + B^2 = C^2";
prog_char FlashCards_2[] PROGMEM = "Ciao";
prog_char FlashCards_3[] PROGMEM = "Hi";
prog_char FlashCards_4[] PROGMEM = "Capisco";
prog_char FlashCards_5[] PROGMEM = "I Understand";

PROGMEM const char *FlashCards_table[] = 
{
  FlashCards_0,
  FlashCards_1,
  FlashCards_2,
  FlashCards_3,
  FlashCards_4,
  FlashCards_5
};

byte FlashCardsSize = 6;

void FlashCards()
{
  Mode = 22;
  lcd.clear();
  lcd.setCursor(0, 1);
  if(menuPos < 0)
  {
    menuPos = 0;
  }
  else if(menuPos == FlashCardsSize)
  {
    menuPos -= 1;
  }
  strcpy_P(buffer, (char*)pgm_read_word(&(FlashCards_table[menuPos])));
  lcd.print(buffer);
}
