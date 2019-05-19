/* Attendance Tracker
 *  Gene and Ruposri
 * 
 * SDA - Orange - A4
 * SCL - Brown - A5
 * 
 * 
 */
 /*
#include <SPI.h>
#include <Adafruit_PN532.h>
*/
#include <Wire.h> 


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

#define ROTARY_ANGLE_SENSOR A0
//#define ADC_REF 5
//#define GROVE_VCC 5//VCC of the grove interface is normally 5v
#define FULL_ANGLE 300//full value of the rotary angle is 300 degrees
/*
#define PN532_SCK  (2)
#define PN532_MOSI (3)
#define PN532_SS   (4)
#define PN532_MISO (5)
*/
int LIST_SIZE = 11;

char *myStrings[]={"Apple", "Pear", "Bread",
                    "Juice", "Chips","Soup","Oranges",
                    "Meat","Cheese","Cookies","Crackers"};

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
   
  pinMode(ROTARY_ANGLE_SENSOR, INPUT);
  //pinMode(BUTTON,INPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:
    int degrees;
    degrees = getDegree();
    
    int index = degrees/LIST_SIZE;

    int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
    
    int StudentListSize = map(sensor_value, 1000, 100, 1, LIST_SIZE);

    Serial.println(sensor_value);

    

    //Print index to screen
    lcd.clear(); //neaded to clear characters from screen
    lcd.setCursor(0,0);
    lcd.print(myStrings[StudentListSize-1]);
    lcd.setCursor(0, 1);
    lcd.print(myStrings[StudentListSize]);
    lcd.setCursor(0, 2);
    lcd.print(myStrings[StudentListSize+1]);
    lcd.setCursor(0, 3);
    lcd.print(myStrings[StudentListSize+2]);

    delay(100);
}

int getDegree()
{
  
  float voltage;
 //voltage = (float)sensor_value*ADC_REF/1023;
  float degrees = (voltage*FULL_ANGLE)/5;
  return degrees;
  lcd.clear();
}
