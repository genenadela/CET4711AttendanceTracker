import processing.serial.*;
import controlP5.*;
Serial myPort;
String studentStatus="";
ControlP5 cp5;
String[] classList;


void setup(){
  size(500, 900);
  myPort = new Serial(this, "COM29", 9600); // Starts the serial communication
  myPort.bufferUntil('\n'); // Defines up to which character the data from the serial port will be read. The character '\n' or 'New Line'
  cp5 = new ControlP5(this);
}

void serialEvent(Serial myPort){
  
  studentStatus = myPort.readStringUntil('\n');

}

void draw() {
  classList = split(studentStatus, ','); //Splits received string from bluetooth into vertical list of entries
  background(0,0,0);
  textSize(18);
  for (int i=0; i<11; i++) {
    text(classList[i], 100, 100+i*30);
  }
 
  
  
}
