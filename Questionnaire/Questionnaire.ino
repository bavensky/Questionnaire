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
   *  CS -  pin 53
   * But i use deek-robot datalog shield connect to :
   *  MOSI - pin 11
   *  MISO - pin 12
   *  CLK - pin 13
   *  CS - pin 4 or 10  now i use pin 10
   
     RTC DS1307
   *  Vcc  -  +5v
   *  GND  -  Ground
   *  SDA  -  pin 20
   *  SCL  -  pin 21
   
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
  #define  BUSZER    35
  #define  DELAYTIME  1000
  
  
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
  RTC_DS1307 rtc;
  
  File allFile;
  
  byte push0[8] = {
                      B00000,
                      B11111,
                      B11111,
                      B11111,
                      B11111,
                      B11111,
                      B11011, };
  byte push1[8] = {
                      B01000,
                      B10000,
                      B00000,
                      B00000,
                      B00000,
                      B00000,
                      B11111, };
                      
  byte push2[8] = {
                      B11111,
                      B00001,
                      B00111,
                      B00001,
                      B00111,
                      B00001,
                      B11111, };
 byte push3[8] = {
                      B00000,
                      B00000,
                      B00000,
                      B00000,
                      B00000,
                      B00000,
                      B00000, };                      
 byte push4[8] = {
                      B00000,
                      B00000,
                      B00000,
                      B00110,
                      B01001,
                      B01001,
                      B01001, };  
 byte push5[8] = {
                      B00000,
                      B00000,
                      B00000,
                      B00000,
                      B00000,
                      B00000,
                      B00000, };                      

  int people= 0;
  int readbutton5=0, readbutton4=0, readbutton3=0, readbutton2=0, readbutton1=0;    
  
  void setup() 
  {
    Wire.begin();
    rtc.begin();
    //rtc.adjust(DateTime(__DATE__, __TIME__));  //  Adjust time now
    Serial.begin(9600);
    while (!Serial) {;}
    
    pinMode(BUTTON_5, INPUT);
    pinMode(BUTTON_4, INPUT);
    pinMode(BUTTON_3, INPUT);
    pinMode(BUTTON_2, INPUT);
    pinMode(BUTTON_1, INPUT);
    pinMode(BUSZER,  OUTPUT);
    
    pinMode(CS, OUTPUT);
    SD.begin(CS,MOSI,MISO,CLK);
    
    first_save();  
    
    lcd.begin(20, 4);  
    // createChar for LCD
    lcd.createChar(0, push0);
    lcd.createChar(1, push1);
    lcd.createChar(2, push2);
    lcd.createChar(3, push3);
    lcd.createChar(4, push4);
    lcd.createChar(5, push5);
    
  }
  
  void loop() 
  { 
    /******* Show LCD RealTime ********/
    lcd.home();
    lcd.print("  RMUTL Question ");
    lcd.setCursor(17, 0);
    lcd.write(byte(3));
    lcd.setCursor(18, 0);
    lcd.write(byte(4));
    lcd.setCursor(19, 0);
    lcd.write(byte(5));
    
    lcd.setCursor(0, 1);
    lcd.print("   Please Choice");
    lcd.setCursor(17, 1);
    lcd.write(byte(0));
    lcd.setCursor(18, 1);
    lcd.write(byte(1));
    lcd.setCursor(19, 1);
    lcd.write(byte(2));
    lcd.setCursor(0, 2);
    lcd.print("  5   4   3   2   1 ");
    
    showtime();
    /**********************************/
     
    verygood();
    good();
    medium();
    poor();
    verypoor();
  }
  
  void showtime()
  {
    DateTime now = rtc.now();  
    lcd.setCursor(0, 4);
    lcd.print("Time : ");
    lcd.setCursor(8, 4);
    lcd.print(now.hour());
    lcd.print(":");
    lcd.print(now.minute());
    lcd.print(":");
    lcd.print(now.second());
    lcd.print(" ");
  }
  void first_save()
  {
    allFile = SD.open(OUTPUT_FILE, FILE_WRITE);
    if (allFile) 
      {   
        allFile.print("Date");
        allFile.print(",");
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
  
  /*************** VERY GOOD **************/
  void verygood()
  {
    readbutton5 = digitalRead(BUTTON_5);
    Serial.println(readbutton5);
    if(readbutton5 == 0)
    {
      delay(200);
      digitalWrite(BUSZER, HIGH);
      people = people++;
      lcd.setCursor(18, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1);
      lcd.print("Choice: 5 (VeryGood)");
      lcd.setCursor(0, 2);
      lcd.print("ThankYou For Answers");
      digitalWrite(BUSZER, HIGH);
      delay(DELAYTIME);
      digitalWrite(BUSZER, LOW);
      lcd.clear();
      
      allFile = SD.open(OUTPUT_FILE, FILE_WRITE);
      if (allFile) 
      {   
        /******   DATE  ************/ 
        DateTime now = rtc.now();
        allFile.print(now.day());
        allFile.print("/");
        allFile.print(now.month());
        allFile.print("/");
        allFile.print(now.year());
        allFile.print(",");
        /******   TIME  ************/ 
        allFile.print(now.hour());
        allFile.print(":");
        allFile.print(now.minute());
        allFile.print(":");
        allFile.print(now.second());
        allFile.print(",");
        /******   Number  *********/ 
        allFile.print(people);
        allFile.print(",");
        /******   Answers  ********/ 
        allFile.print("1");      //5    
        allFile.print(",");      
        allFile.print("0");      //4
        allFile.print(",");
        allFile.print("0");      //3
        allFile.print(",");
        allFile.print("0");      //2
        allFile.print(",");
        allFile.println("0");    //1
        allFile.close();
      }
    }  
  }
  
  /***************** GOOD *****************/
  void good()
  {
    readbutton4 = digitalRead(BUTTON_4);
    Serial.println(readbutton5);
    if(readbutton4 == 0)
    {
      delay(200);
      people = people++;
      lcd.setCursor(18, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1);
      lcd.print("Choice: 4 (Good)    ");
      lcd.setCursor(0, 2);
      lcd.print("ThankYou For Answers");
      digitalWrite(BUSZER, HIGH);
      delay(DELAYTIME);
      digitalWrite(BUSZER, LOW);
      lcd.clear();
      
      allFile = SD.open(OUTPUT_FILE, FILE_WRITE);
      if (allFile) 
      { 
        /******   DATE  ************/ 
        DateTime now = rtc.now();
        allFile.print(now.day());
        allFile.print("/");
        allFile.print(now.month());
        allFile.print("/");
        allFile.print(now.year());
        allFile.print(",");        
        /******   TIME  ************/ 
        allFile.print(now.hour());
        allFile.print(":");
        allFile.print(now.minute());
        allFile.print(":");
        allFile.print(now.second());
        allFile.print(",");
        /******   Number  *********/ 
        allFile.print(people);
        allFile.print(",");
        /******   Answers  ********/ 
        allFile.print("0");      //5    
        allFile.print(",");      
        allFile.print("1");      //4
        allFile.print(",");
        allFile.print("0");      //3
        allFile.print(",");
        allFile.print("0");      //2
        allFile.print(",");
        allFile.println("0");    //1
        allFile.close();
      }
    }   
  }
  
  /**************** MEDIUM *****************/
  void medium()
  {
    readbutton3 = digitalRead(BUTTON_3);
    Serial.println(readbutton5);
    if(readbutton3 == 0)
    {
      delay(200);
      people = people++;
      lcd.setCursor(18, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1);
      lcd.print("Choice: 3 (Medium)  ");
      lcd.setCursor(0, 2);
      lcd.print("ThankYou For Answers");
      digitalWrite(BUSZER, HIGH);
      delay(DELAYTIME);
      digitalWrite(BUSZER, LOW);
      lcd.clear();
      
      allFile = SD.open(OUTPUT_FILE, FILE_WRITE);
      if (allFile) 
      {
        /******   DATE  ************/ 
        DateTime now = rtc.now();
        allFile.print(now.day());
        allFile.print("/");
        allFile.print(now.month());
        allFile.print("/");
        allFile.print(now.year());
        allFile.print(",");   
        /******   TIME  ************/ 
        allFile.print(now.hour());
        allFile.print(":");
        allFile.print(now.minute());
        allFile.print(":");
        allFile.print(now.second());
        allFile.print(",");
        /******   Number  *********/ 
        allFile.print(people);
        allFile.print(",");
        /******   Answers  ********/ 
        allFile.print("0");      //5    
        allFile.print(",");      
        allFile.print("0");      //4
        allFile.print(",");
        allFile.print("1");      //3
        allFile.print(",");
        allFile.print("0");      //2
        allFile.print(",");
        allFile.println("0");    //1
        allFile.close();
      }
    }       
  }
  
  /**************** POOR *****************/
  void poor()
  {
    readbutton2 = digitalRead(BUTTON_2);
    Serial.println(readbutton2);
    if(readbutton2 == 0)
    {
      delay(200);
      people = people++;
      lcd.setCursor(18, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1);
      lcd.print("Choice: 2 (Poor)    ");
      lcd.setCursor(0, 2);
      lcd.print("ThankYou For Answers");
      digitalWrite(BUSZER, HIGH);
      delay(DELAYTIME);
      digitalWrite(BUSZER, LOW);
      lcd.clear();
      
      allFile = SD.open(OUTPUT_FILE, FILE_WRITE);
      if (allFile) 
      {
        /******   DATE  ************/ 
        DateTime now = rtc.now();
        allFile.print(now.day());
        allFile.print("/");
        allFile.print(now.month());
        allFile.print("/");
        allFile.print(now.year());
        allFile.print(",");       
        /******   TIME  ************/ 
        allFile.print(now.hour());
        allFile.print(":");
        allFile.print(now.minute());
        allFile.print(":");
        allFile.print(now.second());
        allFile.print(",");
        /******   Number  *********/ 
        allFile.print(people);
        allFile.print(",");
        /******   Answers  ********/ 
        allFile.print("0");      //5    
        allFile.print(",");      
        allFile.print("0");      //4
        allFile.print(",");
        allFile.print("0");      //3
        allFile.print(",");
        allFile.print("1");      //2
        allFile.print(",");
        allFile.println("0");    //1
        allFile.close();
      }
    }       
  }
  
  /************** VERY POOR ***************/ 
  void verypoor()
  {
    readbutton1 = digitalRead(BUTTON_1);
    Serial.println(readbutton5);
    if(readbutton1 == 0)
    {
      delay(200);
      people = people++;
      lcd.setCursor(18, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1);
      lcd.print("Choice: 1 (VeryPoor)");
      lcd.setCursor(0, 2);
      lcd.print("ThankYou For Answers");
      digitalWrite(BUSZER, HIGH);
      delay(DELAYTIME);
      digitalWrite(BUSZER, LOW);
      lcd.clear();
      
      allFile = SD.open(OUTPUT_FILE, FILE_WRITE);
      if (allFile) 
      { 
        /******   DATE  ************/ 
        DateTime now = rtc.now();
        allFile.print(now.day());
        allFile.print("/");
        allFile.print(now.month());
        allFile.print("/");
        allFile.print(now.year());
        allFile.print(",");  
        /******   TIME  ************/ 
        allFile.print(now.hour());
        allFile.print(":");
        allFile.print(now.minute());
        allFile.print(":");
        allFile.print(now.second());
        allFile.print(",");
        /******   Number  *********/ 
        allFile.print(people);
        allFile.print(",");
        /******   Answers  ********/ 
        allFile.print("0");      //5    
        allFile.print(",");      
        allFile.print("0");      //4
        allFile.print(",");
        allFile.print("0");      //3
        allFile.print(",");
        allFile.print("0");      //2
        allFile.print(",");
        allFile.println("1");    //1
        allFile.close();
      }
    }       
  }

