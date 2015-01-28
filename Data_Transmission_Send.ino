//#include <EEPROM.h>
//
void dataSend()
{
  lcd.clear();
  lcd.print("in dataSend");
}

//char Answers[] = {1,
//                  2,
//                  3,
//                  4,
//                  3,
//                  2,
//                  1,
//                  2,
//                  4,
//                  1, 4, 2, 3, 4, 2, 3, 3, 2, 3, 4, 1, 2, 4, 2, 3, 1, 4, 2, 3, 1, 4, 2, 3, 1, 2};
//int Data;
//void setup()
//{
//  Serial.begin(9600);
//  pinMode(3, OUTPUT);
//  writeEEPROM(Answers);
//  readEEPROM(Answers);
//}
//
//void sendData(char Data)
//{
//      for(int i = 0; i < Data; i++)
//      {
//         digitalWrite(3, HIGH); 
//         delay(70); // 70 is the threshold. Any faster and it will risk reading incorrectly. MUST MATCH with Receiver!
//      }
//      digitalWrite(3, LOW);
////      delay(30);
//}
//
//void loop()
//{
//  char value = analogRead(0);
//  while(Serial.available() <= 0)
//  {
////     Serial.println(value);
//  }
//  while(Serial.available() > 0)
//  {
//     Data = Serial.read() - 64; 
//     delay(10);
//     Serial.println(Data);
//     sendData(Data);
//  }
//}
//
//void writeEEPROM(char something[])
//{
//  for(int k = 0; k < 35; k++)
//  {
//    EEPROM.write(k, something[k]);
//  }
//}
//
//void readEEPROM(char somethingElse[])
//{
//  for(int j = 0; j < 35; j++)
//  {
//    sendData(EEPROM.read(j));
//    delay(500);
//  }
//}
