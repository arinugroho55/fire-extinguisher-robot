#include <Servo.h>

Servo myservo;

int pos = 0;

const int sensorPin = 2;     
const int buzzer =  11;  
const int fan  = 12;

// variables will change:
int bacasensor = 0;   
 
void setup(){
  myservo.attach(9);
  pinMode(buzzer, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(fan, OUTPUT);
  //myservo.write(0);
  Serial.begin(9600);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW); 
  
  attachInterrupt(digitalPinToInterrupt(sensorPin), flame_ISR, LOW);
  
}

void(* resetFunc)(void) = 0;

void loop(){
  bacasensor = digitalRead(sensorPin);
  digitalWrite(fan, LOW);
  for (pos = 0; pos <= 30; pos += 1) { // goes from 0 degrees to 180 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 20ms for the servo to reach the position
  }
  for (pos = 180; pos >= 150; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 20ms for the servo to reach the position
  }
  
}

void flame_ISR(){
  bacasensor = digitalRead(sensorPin);
  if (bacasensor == LOW) {
    myservo.detach();
    digitalWrite(buzzer, HIGH);
    digitalWrite(fan, HIGH);
    Serial.println("Terdeteksi Panas Api");
    
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(fan, LOW);
    Serial.println("Tidak Terdeteksi Panas Api");
    delay(100);
    myservo.attach(9);
  }
  resetFunc();

  
}
