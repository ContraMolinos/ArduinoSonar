#include <Servo.h>

Servo sMotor;
int trigPin=6;
int echoPin=7;
int servoPin=2;

long duration;
int angle=0;
int step=2;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  sMotor.attach(servoPin);
  sMotor.write(angle);
  delay(50);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin,HIGH,500000);
  
  Serial.print(angle);
  Serial.print("->");
  Serial.print(duration);
  Serial.print("->");
  Serial.println(17490);  //Detection limit, 3m.
 
  //Serial.println(duration/58.2);
  if(angle>(180-step) || angle<-step)
    step=-step;
  
  angle+=step;
  sMotor.write(angle);
  delay(50);
}
