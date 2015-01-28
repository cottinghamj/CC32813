// Make a mental math  practice app


byte Hour;
byte Minute;
byte Second;

void setTime()
{
	Mode = 6;// setTime Mode
	lcd.clear();
	if(menuPos == 0)
	{	
		lcd.clear();
		lcd.print("Hour: ");
		lcd.print(Hour);
		getValue();
	}
	else if(menuPos == 1)
	{
		lcd.clear();
		lcd.print("Minute");
		lcd.print(Minute);
		getValue();
	}
	else if(menuPos == 2)
	{
		lcd.clear();
		lcd.print("Second");
		lcd.print(Second);
		getValue();
	}
	else if(menuPos == 3)
	{
		MainMenu();
	}
}

//------------------------------------------------------------------------------------------------------------------------

void passwordSet()
{
	Mode = 7; // Password Set Mode
	if(menuPos == 0);
	{
		lcd.clear();
		lcd.print("Enter Old Pass");
		setCursor(0,1);
		getValue();

	}
	checkPass()	// You may want to put this in the checkPass()
	
	if(menuPos == 1)
	{
		lcd.clear();
		lcd.print("Enter New Pass");
		setCursor(0,1);
		getValue();
		PassPos++;		// Have input from controls got to string array e.g. Password[PassPos] = "h";
		String[] Password = ;// Set this up. Might also want to make this in createPass(). SHould be an array Need to store in flash
		
	}
}
void checkPass()
{
	byte a = 0;
	while(a < sizeof(Password)/ sizeof(String))
	{
		if(Password[a] == temp[a])
		{
			a++;
		}
		else if(Password[a] != temp[a])
		{
			lcd.clear();
			lcd.print("Incorrect Pass")
			delay(3000);
			passwordSet();
		}
		else if(a == sizeof(Password)/sizeof(String))
		{
			menuPos = 1;
		}
	}
}
// -----------------------------------------------------------------------------------------------------------------------------
//00:00:00

void Timer()
{
	byte hoursLeft, minutesLeft, secondsLeft;
	Mode = 8;
	lcd.clear();
	lcd.print("Set Timer:");
	setCursor(0,1);
	lcd.print(hoursLeft);	// in evalValue(), after enter lcd.SetCursor() ----- edit up and down in evalValue ---- might add support for numbers 
	lcd.print(":");
	lcd.print(minutesLeft); // in evalValue(), after enter lcd.SetCursor() ----- edit up and down in evalValue ---- ""
	lcd.print(":");
	lcd.print(secondsLeft); // in evalValue(), after enter lcd.SetCursor() ----- edit up and down in evalValue ---- ""
} 