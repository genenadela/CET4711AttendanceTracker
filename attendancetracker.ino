#include <RTClib.h>



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

#define ROTARY_ANGLE_SENSOR A0
#define FULL_ANGLE 300//full value of the rotary angle is 300 degrees

#define PN532_SCK  (2)
#define PN532_MOSI (3)
#define PN532_SS   (4)
#define PN532_MISO (5)

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display
Adafruit_PN532 cardscan(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

RTC_DS1307 rtc;

int LIST_SIZE = 11;
int degrees;
int index;
int sensor_value; 
int StudentListSize;
String timeAttend;

char *classList[11][3]={
  {"Arlo", "Absent", "77157136640"},
  {"John", "Absent", "109117167640"},
  {"Sera", "Absent", "173104112640"},
  {"Remi", "Absent", "125174145640"},
  {"Blyke","Absent", "00000000000"},
  {"Isen", "Absent", "00000000000"},
  {"Cecille", "Absent", "00000000000"},
  {"Claire", "Absent", "00000000000"},
  {"Elaine", "Absent", "00000000000"},
  {"Meili", "Absent", "00000000000"},
  {"Ventus", "Absent", "00000000000"}
};

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  cardscan.begin();
  cardscan.SAMConfig();
  
  pinMode(ROTARY_ANGLE_SENSOR, INPUT);
  //pinMode(BUTTON,INPUT);

  
}

void loop() {

    uint8_t success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
    uint8_t uidLength; 
    String idString;
    DateTime now = rtc.now();
  
    //Serial.println(sensor_value);

    
  success=cardscan.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength,100);
  
  if (success) {
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    //idString=convertUIDString(uid);
    for (int k=0; k<5; k++) { 
    idString.concat(uid[k]);
    }
    Serial.print(idString);
    for (int g=0; g<LIST_SIZE; g++) {
      if (idString==classList[g][2]){
        Serial.print("   ");
        timeAttend.concat(now.hour());
        timeAttend.concat(":");
        timeAttend.concat(now.minute());
        timeAttend.concat(":");
        timeAttend.concat(now.second());
        Serial.println(timeAttend);
        String dectime = timeAttend;
        classList[g][1]=dectime;
      }
    }
  }
  
DisplayStudentList();
    
    
    
    

    
  
}
/*
String convertUIDString(uint8_t cardnumber) {
  for (int i=0; i<5; i++) {
      String studentIDString;
      byte number = cardnumber[i];
      studentIDString.concat(number);
      return studentIDString;
    }
}
*/
void DisplayStudentList() {
    index = degrees/LIST_SIZE;
    sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
    StudentListSize = map(sensor_value, 680, 0, 1, LIST_SIZE);
    degrees = getDegree();
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
    //delay(100);
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
