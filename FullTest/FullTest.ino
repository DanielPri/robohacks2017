#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *Motor3 = AFMS.getMotor(3);
Servo myservo;  // create servo object to control rover direction
Servo shaftServo;  // create servo object to control shaft
int pos = 90; // initial wheel direction angle (straight)
int shaftPos = 40;
const int FULLPOWER = 255;

void setup() {
  AFMS.begin();  
   Serial.begin(9600); 
    
    shaftServo.attach(10);  // attaches the servo on pin SERVO_1 to the servo object 

}

void loop() {
  // put your main code here, to run repeatedly:

}
