/* Attendance Tracker
 *  Gene and Ruposri
 * 
 * SDA - Orange - A4
 * SCL - Brown - A5
 * 
 * 
 */

#include <SPI.h>
#include <Adafruit_PN532.h>

#include <Wire.h> 


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

#define ROTARY_ANGLE_SENSOR A0
//#define ADC_REF 5
//#define GROVE_VCC 5//VCC of the grove interface is normally 5v
#define FULL_ANGLE 300//full value of the rotary angle is 300 degrees

#define PN532_SCK  (2)
#define PN532_MOSI (3)
#define PN532_SS   (4)
#define PN532_MISO (5)

int LIST_SIZE = 11;
int degrees;
int index;
int sensor_value; 
int StudentListSize;

char *classList[11][2]={
  {"Arlo", "Absent"},
  {"John", "Absent"},
  {"Sera", "Absent"},
  {"Remi", "Absent"},
  {"Blyke","Absent"},
  {"Isen", "Absent"},
  {"Cecille", "Absent"},
  {"Claire", "Absent"},
  {"Elaine", "Absent"},
  {"Meili", "Absent"},
  {"Ventus", "Absent"}
};

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
   
  pinMode(ROTARY_ANGLE_SENSOR, INPUT);
  //pinMode(BUTTON,INPUT);

  
}

void loop() {
    
    index = degrees/LIST_SIZE;
    sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
    StudentListSize = map(sensor_value, 680, 0, 1, LIST_SIZE);
    degrees = getDegree();
    Serial.println(sensor_value);

    

    //Print index to screen
    lcd.clear(); //neaded to clear characters from screen
    lcd.setCursor(0,0);
    lcd.print(classList[StudentListSize-1][0]);
    getSpacing(classList[StudentListSize-1][0],classList[StudentListSize-1][1]);
    lcd.print(classList[StudentListSize-1][1]);
    lcd.setCursor(0, 1);
    lcd.print(classList[StudentListSize][0]);
    getSpacing(classList[StudentListSize][0],classList[StudentListSize][1]);
    lcd.print(classList[StudentListSize][1]);
    lcd.setCursor(0, 2);
    lcd.print(classList[StudentListSize+1][0]);
    getSpacing(classList[StudentListSize+1][0],classList[StudentListSize+1][1]);
    lcd.print(classList[StudentListSize+1][1]);
    lcd.setCursor(0, 3);
    lcd.print(classList[StudentListSize+2][0]);
    getSpacing(classList[StudentListSize+2][0],classList[StudentListSize+2][1]);
    lcd.print(classList[StudentListSize+2][1]);

    delay(100);
}

void getSpacing(String studentName, String studentStatus){
    for (int i=0; i<(20-studentStatus.length()-studentName.length()); i++) {
      lcd.print(" ");
    }
}

int getDegree()
{
  
  float voltage;
 //voltage = (float)sensor_value*ADC_REF/1023;
  float degrees = (voltage*FULL_ANGLE)/5;
  return degrees;
  lcd.clear();
}
