#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//Setup AFMS class
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

//Set up all four motors with their corresponding ports
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *Motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *Motor4 = AFMS.getMotor(4);


void setup(){
  Serial.begin(9600); 
  Serial.println("Testing all four motors!");
  
  // create a connection to the Motor Shield with the default frequency 1.6KHz
  AFMS.begin();  
}

void loop()
{
  uint8_t i;
  
    Serial.println("Motor 1");
    
       Motor1->run(FORWARD);
      for (i=0; i<255; i++) {
        Motor1->setSpeed(i);  
        delay(10);
      }
      for (i=255; i!=0; i--) {
        Motor1->setSpeed(i);  
        delay(10);
      }
      Motor1->run(RELEASE);
    
    
    Serial.println("Motor 2");
          
       Motor2->run(FORWARD);
      for (i=0; i<255; i++) {
        Motor2->setSpeed(i);  
        delay(10);
      }
      for (i=255; i!=0; i--) {
        Motor2->setSpeed(i);  
        delay(10);
      }
      Motor2->run(RELEASE);
    
  
    Serial.println("Motor 3");
          
       Motor3->run(FORWARD);
      for (i=0; i<255; i++) {
        Motor3->setSpeed(i);  
        delay(10);
      }
      for (i=255; i!=0; i--) {
        Motor3->setSpeed(i);  
        delay(10);
      }
      Motor3->run(RELEASE);
    
  
    Serial.println("Motor 4");
          
       Motor4->run(FORWARD);
      for (i=0; i<255; i++) {
        Motor4->setSpeed(i);  
        delay(10);
      }
      for (i=255; i!=0; i--) {
        Motor4->setSpeed(i);  
        delay(10);
      }
    
    Motor4->run(RELEASE);
}

