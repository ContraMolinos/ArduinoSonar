#include <Servo.h>

Servo sMotor;
int trigPin=6;
int echoPin=7;
int servoPin=2;

int nLoops=5;
//int tLimit=17490;//Detection limit, 3m.
int tLimit=29150;//Detection limit, 5m.

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
  duration=0;
  for(int i=0;i<nLoops;i++)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration+=pulseIn(echoPin,HIGH,2*tLimit);
  }
  
  duration=duration/nLoops;
  
  Serial.print(angle);
  Serial.print("->");
  Serial.print(duration);
  Serial.print("->");
  Serial.println(tLimit);  
 
  //Serial.println(duration/58.2);
  if(angle>(180-step) || angle<-step)
    step=-step;
  
  angle+=step;
  sMotor.write(angle);
  delay(50);
}
