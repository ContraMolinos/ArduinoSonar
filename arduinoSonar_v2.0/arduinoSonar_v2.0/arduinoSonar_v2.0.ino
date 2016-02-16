/**
  Arduino Sonar v2.0.
  FJS. Feb. 2016
  
  New version that uses the NewPing library, instead
  of the pulseIn function. It uses the ping_median
  function for better stability in the measurements.
*/

#include <Servo.h>
#include <NewPing.h>

Servo sMotor;
int trigPin=6;
int echoPin=7;
int servoPin=2;

int nLoops=3;
int limit=200;

NewPing sonar(trigPin,echoPin,limit);

long duration;
int angle=0;
int step=2;

void setup() {
  Serial.begin(9600);
  sMotor.attach(servoPin);
  sMotor.write(angle);
  delay(50);
}

void loop() {
  
  //duration=sonar.ping();
  duration=sonar.ping_median(nLoops);
  
  Serial.print(angle);
  Serial.print("->");
  Serial.print(duration);
  Serial.print("->");
  Serial.println(limit);  
 
  //Serial.println(duration/58.2);
  if(angle>(180-step) || angle<-step)
    step=-step;
  
  angle+=step;
  sMotor.write(angle);
  delay(50);
}
