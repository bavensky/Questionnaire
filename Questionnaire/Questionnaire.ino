  /*
  
    The LCD circuit:
   * LCD RS pin to digital pin 8
   * LCD Enable pin to digital pin 9
   * LCD D4 pin to digital pin 4
   * LCD D5 pin to digital pin 5
   * LCD D6 pin to digital pin 6
   * LCD D7 pin to digital pin 7
   * LCD R/W pin to ground
   
    SD card attached to SPI bus as follows:
   *Mega 
   *  MOSI - pin 50
   *  MISO - pin 51
   *  CLK - pin 52
   *  CS - 53
   * But i use deek-robot datalog shield connect to :
   *  MOSI - pin 11
   *  MISO - pin 12
   *  CLK - pin 13
   *  CS - pin 4 or 10  now i use pin 10
   
   */
  
  #include <LiquidCrystal.h>
  #include <SD.h>
  #include <Wire.h>
  #include "RTClib.h"
  
  #define  CS    10
  #define  MOSI  11
  #define  MISO  12
  #define  CLK   13

  #define  OUTPUT_FILE "Datalog.csv"
  #define  BUTTON_5  30 
  #define  BUTTON_4  31
  #define  BUTTON_3  32
  #define  BUTTON_2  33
  #define  BUTTON_1  34
  
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
  RTC_Millis rtc;
  
  File allFile;
  
  byte push[8] = {
  B11111,
  B01110,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  };

  int hour_1= 0, minute_1= 0, second_1= 0;
  int readbutton5=0, readbutton4=0, readbutton3=0, readbutton2=0, readbutton1=0;    
  
  void setup() 
  {
    rtc.begin(DateTime(__DATE__, __TIME__));
    Serial.begin(9600);
    
    pinMode(BUTTON_5, INPUT);
    pinMode(BUTTON_4, INPUT);
    pinMode(BUTTON_3, INPUT);
    pinMode(BUTTON_2, INPUT);
    pinMode(BUTTON_1, INPUT);
    
    pinMode(CS, OUTPUT);
    SD.begin(CS,MOSI,MISO,CLK);
    //first_save();  
    
    lcd.begin(20, 4);
    lcd.createChar(0, push);
  }
  
  void loop() 
  { 
    lcd.home();
    lcd.print("    Questionnaire   ");
    lcd.setCursor(0, 1);
    lcd.print("Please You Choice");
    lcd.setCursor(17, 1);
    lcd.write(byte(0));
    lcd.setCursor(0, 2);
    lcd.print("  5   4   3   2   1 ");

    
    showtime();
    
    verygood();
  }
  void showtime()
  {
    DateTime now = rtc.now();
    hour_1 = now.hour();
    minute_1 = now.minute();
    second_1 = now.second();
    
    lcd.setCursor(0, 4);
    lcd.print("Time : ");
    lcd.setCursor(8, 4);
    lcd.print(hour_1);
    lcd.print("/");
    lcd.print(minute_1);
    lcd.print("/");
    lcd.print(second_1);
    lcd.print(" ");
  }
  void first_save()
  {
    allFile = SD.open(OUTPUT_FILE, FILE_WRITE);
    if (allFile) 
      {   
        allFile.print("Time");
        allFile.print(",");
        allFile.print("Number");
        allFile.print(",");
        allFile.print("Very Good");
        allFile.print(",");
        allFile.print("Good");
        allFile.print(",");
        allFile.print("Medium");
        allFile.print(",");
        allFile.print("Poor");
        allFile.print(",");
        allFile.println("Very Poor");
        allFile.close();
      }
  }
  
  void verygood()
  {
    readbutton5 = digitalRead(BUTTON_5);
    Serial.println(readbutton5);
    if(readbutton5 == 0)
    {
      lcd.setCursor(0, 1);
      lcd.print("You Choice: VeryGood");
      lcd.setCursor(0, 2);
      lcd.print("ThankYou For Answers");
      delay(3000);
      lcd.clear();
    }
    
  }
  void good()
  {
    
  }
  void Medium()
  {
    
  }
  void poor()
  {
    
  }
  void verypoor()
  {
    
  }

