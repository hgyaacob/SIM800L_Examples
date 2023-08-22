#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial sim800(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

// Variable to store text message
String textMessage;

//Motor A connection
int enA = 9;
int in1 = 8;
int in2 = 7;

int jwpn;

//Motor Status
bool isMotorOn;

void setup()
{
  delay(7000);
  
  Serial.begin(9600);
  Serial.println("Arduino serial initialize");
  
  sim800.begin(9600);
  Serial.println("SIM800L software serial initialize");

  // Variable to store text message
String textMessage;

   // AT command to set SIM900 to SMS mode
  sim800.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  sim800.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  //Set motor status OFF
  isMotorOn = 0; //false
}

void loop()
{
  updateSerial();
  updateLCD();
}

void updateSerial(){
  if(sim800.available()>0){
    textMessage = sim800.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
  if(textMessage.indexOf("Motor ON")>=0){
    // Turn on relay and save current state
    turnMotorOn();
    textMessage = "";   
  }
  if(textMessage.indexOf("Motor OFF")>=0){
    turnMotorOff();
    textMessage = ""; 
  }
}

void turnMotorOn(){
  analogWrite(enA, 125); //Set motor half speed ~5V

  //Turn motor A on
  Serial.println("Motor ON");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  isMotorOn = true;
}

void turnMotorOff(){
    //Turn motor A off
  Serial.println("Motor OFF");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  isMotorOn = false;
}

void updateLCD(){
  if(isMotorOn){
    
  }
  else{
    
  }
}
