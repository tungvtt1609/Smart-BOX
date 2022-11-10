#include <SPI.h>
#include <RFID.h>
#include <string.h>
 
const int trigPin = 23;
const int echoPin = 25;
/* Ket noi chan (Arduino Mega)
 *  Reset     5
 *  SPI SDA   53
 *  SPI MOSI  51
 *  SPI MISO  50
 *  SPI SCK   52
 */

#define SDA_DIO 53
#define RESET_DIO 5

RFID RC522(SDA_DIO, RESET_DIO);
long duration;
int distance;
String id = "rfid:";
String idx = "set:";
String idx2 = "get:";
String p_check = "p:";
bool check = false;
String message = "";
int checkcount1 = 0;
int checkcount2 = 0;
bool isperson = false;
bool checkgetslot = false;
bool checkinterupt = false;
bool isdoorclose = true;
void setup()
{ 
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
//  Serial.print("Oke");
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT);
  pinMode(3, INPUT);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  attachInterrupt(digitalPinToInterrupt(18), slot1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), slot2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(20), slot3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(21), slot4, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), door, CHANGE);
  
  pinMode(15,OUTPUT);
  pinMode(27,INPUT);
  digitalWrite(15,HIGH);
}
void sendRFID(String data){
  Serial.println(data);
  
}
void readDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  //Serial.println(distance);

  if (distance <= 35  && !isperson){
    if (checkcount1 <= 20) {
      checkcount1++; 
    }
    else {
      isperson = true;
      checkcount1 = 0;
      Serial.println("p:1");
    }
  }
  else if (distance >=  35  && isperson){
    if (checkcount2 <= 20) {
      checkcount2++;
    }
    else {
      isperson = false;
      checkcount2 = 0;
      Serial.println("p:0");
    }
  }
  
  
}
void openDoor(){
  digitalWrite(15,LOW);
  delay(1000);
}

void slot1(){
  if (digitalRead(18) == HIGH){
  message = "";
  message += idx;
  message += "A_1:";
  readRFID();
  }
}
void slot2(){
  if (digitalRead(19) == HIGH){
  message = "";
  message += idx;
  message += "A_2:";
 
  readRFID();
  }
}
void slot3(){
  if (digitalRead(20) == HIGH){
  message = "";
  message += idx;
  message += "A_3:";
 
  readRFID();
  }
}
void slot4(){
  if (digitalRead(21) == HIGH){
  message = "";
  message += idx;
  message += "A_4:";
  readRFID();
  }
}

void door(){
  int doorstate = digitalRead(3);
    
    if (doorstate == 0 && !isdoorclose){
      Serial.println("check:closed");
      delay(200);
      isdoorclose = true;
    }
    else if(doorstate == 1 && isdoorclose){
      Serial.println("check:opened");
      isdoorclose = false;
    }
}

void readRFID(){
  bool state = true;
  if (checkinterupt){
    if (!checkgetslot){
      while (state){
    
         if (RC522.isCard()){
            RC522.readCardSerial();
            String b = "";
            for(int i = 0 ; i < 5; i++){
              b+= String(RC522.serNum[i]);
            }
      message += b;
      sendRFID(message);
      state = false;
         }
      }
    }
  }
}
void readSerialString(){
  String incomingString;
  if (Serial.available() > 0) {
    // read the incoming string:
    incomingString = Serial.readStringUntil('\n');
    checkgetslot = true;

    char opendoor = "";
    char slot = "";
    if (incomingString.length() == 4){
      opendoor = incomingString.charAt(0);  
    }
    else {
      opendoor = incomingString.charAt(0);
      slot = incomingString.charAt(5);  
    }

    if(opendoor == 'd'){
      checkinterupt = false;
      digitalWrite(15,LOW);
      delay(3000);
      digitalWrite(15,HIGH); 
      Serial.println("opendone");
    }
    else if (opendoor == 'o'){
      checkinterupt = true;
    }
  
    bool getcheck= true;
    switch (slot){
      case '1':
        digitalWrite(8,HIGH); //8
        while(getcheck){
          if (digitalRead(18)){
            digitalWrite(8,LOW);
            Serial.println("check:get");
            getcheck = false;
          }
        }
      break;
    case '2':
      digitalWrite(6,HIGH);//
      while(getcheck){
        if (digitalRead(19)){
          digitalWrite(6,LOW);
          getcheck = false;
          Serial.println("check:get");
        }
      }
      break;
    case '3':
      digitalWrite(7,HIGH); //7
      while(getcheck){
        if (digitalRead(20)){
          digitalWrite(7,LOW);
          getcheck = false;
          Serial.println("check:get");
        }
      }
      break;
      
    case '4':
      digitalWrite(10,HIGH);
      while(getcheck){
        if (digitalRead(21)){
          digitalWrite(10,LOW);
          getcheck = false;
          Serial.println("check:get");
        }
      }
      break;
  }
  }
  else{
    checkgetslot = false;
  }
  
}

void loop(){

  readDistance();
  readSerialString();
}
