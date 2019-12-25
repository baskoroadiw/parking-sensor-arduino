#include <SoftwareSerial.h>
#define BT_SERIAL_RX 10
#define BT_SERIAL_TX 11

SoftwareSerial blueTooth(BT_SERIAL_RX, BT_SERIAL_TX);

const int pingPin = 13;
const int echoPin = 12;

bool con1 = false;
bool con2 = false;
bool con3 = false;
bool siap = false;

int buzzer = 8;

void setup(){
  Serial.begin(9600);
  blueTooth.begin(9600);
  pinMode(buzzer,OUTPUT);
  pinMode(pingPin,OUTPUT);
  pinMode(echoPin, INPUT);
} 

void loop() { 
  long duration, cm;
  digitalWrite(pingPin,LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin,LOW);
  duration = pulseIn(echoPin, HIGH); 
  cm = microsecondsToCentimeters(duration);

  Serial.print("Jarak :");
  Serial.print("\t");
  Serial.print(cm); 
  Serial.print("cm");
  Serial.println();

  if (cm <= 25){
    con1 = true;
    con2 = false;
    con3 = false;
    
    if (cm <= 15){
      con1 = false;
      con2 = true;
      con3 = false;
      
      if (cm <= 7){
        con1 = false;
        con2 = false;
        con3 = true;
      }
    }
    siap = true;
  }
  else{
    con1 = false;
    con2 = false;
    con3 = false;
    siap = false;
    blueTooth.print("0");
  }

  if (con1 == true && siap == true){
    blueTooth.print("1");
    
    digitalWrite(buzzer, LOW);
    delay(300);
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    delay(300);
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
  }
  else{
    digitalWrite(buzzer, LOW);
  }
  
  if(con2 == true && siap == true){
    blueTooth.print("2");
    
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
  }
  else{
    digitalWrite(buzzer, LOW);
  }

  if(con3 == true && siap == true){
    blueTooth.print("3");
    
    digitalWrite(buzzer, HIGH);
  }
  else{
    digitalWrite(buzzer, LOW);
  }
}

long microsecondsToCentimeters(long microseconds){ 
  return microseconds /29 / 2;
}
