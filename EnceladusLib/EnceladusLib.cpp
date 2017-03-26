#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <NewPing.h>
#include <Servo.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//Setup AFMS class
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//Set up all four motors with their corresponding ports
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *Motor3 = AFMS.getMotor(3);

const int FULLPOWER = 255;
Servo myservo;  // create servo object to control rover direction
Servo shaftServo;  // create servo object to control shaft

int pos = 90; // initial wheel direction angle (straight)
int shaftPos = 40;

//gives distance measured by ultrasound in cm
int getUltrasound(){
  unsigned int ultraDistance = sonar.ping_median();
  ultraDistance = sonar.convert_cm(ultraDistance);
  return ultraDistance;
}

//moves forward for amount multiplier (from 0-1), for a duration in milliseconds
void forward(float amount, int duration){
       Motor1->run(FORWARD);
       Motor2->run(FORWARD);

        //start with a boost for 300 milliseconds
        Motor1->setSpeed(FULLPOWER);  
        Motor2->setSpeed(FULLPOWER);
        if(duration <= 2000){
          delay(duration/4);          
        }
        else
          delay(300);
        //boost ends
          
        Motor1->setSpeed(FULLPOWER*amount);  
        Motor2->setSpeed(FULLPOWER*amount);  
         delay(duration);
       Motor1->run(RELEASE);
       Motor2->run(RELEASE); 
       delay(100);
}

//moves backward for amount multiplier (from 0-1), for a duration in milliseconds
void backward(float amount, int duration){
       Motor1->run(BACKWARD);
       Motor2->run(BACKWARD);

        //start with a boost for 300 milliseconds
        Motor1->setSpeed(FULLPOWER);  
        Motor2->setSpeed(FULLPOWER);
        if(duration <= 2000){
          delay(duration/4);          
        }
        else
          delay(300);
        //boost ends
          
        Motor1->setSpeed(FULLPOWER*amount);  
        Motor2->setSpeed(FULLPOWER*amount);  
         delay(duration);
       Motor1->run(RELEASE);
       Motor2->run(RELEASE); 
       delay(100);
}

//Turns right amount intensity for duration milliseconds
void turnRight(float amount, int duration) {
       Motor1->run(RELEASE);
       Motor2->run(RELEASE);    
        delay(100);
        
        myservo.attach(9);  // attaches the servo on pin 9 to the servo object
        for (pos = 90; pos <= 120; pos += 1) { // goes from 90(straight) degrees to 120(right) degrees
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          Serial.println(pos);
          delay(40);                       // waits 15ms for the servo to reach the position
        }
        myservo.detach();  // attaches the servo on pin 9 to the servo object
        Motor1->run(FORWARD);
        Motor2->run(FORWARD);   
        Motor1->setSpeed(FULLPOWER*amount);  
        Motor2->setSpeed(FULLPOWER*amount);
                     
         delay(duration);
             
       Motor1->run(RELEASE);
       Motor2->run(RELEASE);       
       delay(100);
       myservo.attach(9);  // attaches the servo on pin 9 to the servo object
       for (pos = 120; pos >= 90; pos -= 1) { // goes from 120(right) degrees to 90(straight) degrees
         myservo.write(pos);              // tell servo to go to position in variable 'pos'
         Serial.println(pos);
         delay(40);                       // waits 15ms for the servo to reach the position
       }
       myservo.detach();  // attaches the servo on pin 9 to the servo object
}

//Turns left amount intensity for duration milliseconds
void turnLeft(float amount, int duration) {
       Motor1->run(RELEASE);
       Motor2->run(RELEASE);    
        delay(100);
        
        myservo.attach(9);  // attaches the servo on pin 9 to the servo object
        for (pos = 90; pos >= 60; pos -= 1) { // goes from 90(straight) degrees to 60(right) degrees
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          Serial.println(pos);
          delay(40);                       // waits 15ms for the servo to reach the position
        }
        myservo.detach();  // attaches the servo on pin 9 to the servo object
        Motor1->run(FORWARD);
        Motor2->run(FORWARD);   
        Motor1->setSpeed(FULLPOWER*amount);  
        Motor2->setSpeed(FULLPOWER*amount);
                     
         delay(duration);
             
       Motor1->run(RELEASE);
       Motor2->run(RELEASE);       
       delay(100);
       myservo.attach(9);  // attaches the servo on pin 9 to the servo object
       for (pos = 60; pos <= 90; pos += 1) { // goes from 120(right) degrees to 90(straight) degrees
         myservo.write(pos);              // tell servo to go to position in variable 'pos'
         Serial.println(pos);
         delay(40);                       // waits 15ms for the servo to reach the position
       }
       myservo.detach();  // attaches the servo on pin 9 to the servo object
}

void drill(){
  shaftServo.attach(10);  // attaches the servo on pin SERVO_1 to the servo object 
   shaftDown();
   rotateDrill(2000);
   shaftUp();
   Motor3->run(RELEASE); 
   shaftServo.detach();   
 }

//use only for drill function
void shaftUp(){ 
  
  for (shaftPos = 180; shaftPos >= 40; shaftPos -= 1) { // pulls drill up
      shaftServo.write(shaftPos);              // tell servo to go to shaftPosition in variable 'shaftPost
      delay(30);                       // waits 15ms for the servo to reach the shaftPosition
    }
}

//use only for drill function
void shaftDown(){ 
    rotateDrill();
    for (shaftPos = 40; shaftPos <= 180; shaftPos += 1) { // pushes drill down towards ground
        // in steps of 1 degree
        shaftServo.write(shaftPos);              // tell servo to go to shaftPosition in variable 'shaftPos'
        //Serial.println(shaftPos);
        delay(30);                       // waits 15ms for the servo to reach the shaftPosition
  }
    rotateDrill(0);
}

void rotateDrill(){
     Motor3->run(FORWARD);
     Motor3->setSpeed(FULLPOWER); 
}

void rotateDrill(int duration){
  Motor3->run(RELEASE);
  Motor3->run(FORWARD);
  Motor3->setSpeed(FULLPOWER); 
  delay(duration);
  Motor3->run(RELEASE);
}
