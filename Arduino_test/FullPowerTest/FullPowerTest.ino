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
    Serial.println("All systems go!");
       Motor1->run(FORWARD);
       Motor2->run(FORWARD);          
       Motor3->run(FORWARD);
       Motor4->run(FORWARD);
      
        Motor1->setSpeed(100);  
        Motor2->setSpeed(100);  
        Motor3->setSpeed(0);  
        Motor4->setSpeed(0);  
       delay(5000);
       Serial.println("All systems rest!");
      Motor1->run(RELEASE);
      Motor2->run(RELEASE);
      Motor3->run(RELEASE);
      Motor4->run(RELEASE);
      delay(5000);
   
}

