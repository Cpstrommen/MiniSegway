//pin variables
int prevdir = 1;

//tuning variables

int low_speed = 200;
int med_speed = 300;
int high_speed = 400;

int center = 98;
int medOffset = 100;
int bigOffset = 150;

int refreshLow = 15;
int refreshMed = 35;
int refreshHigh = 60;

//gyro variables

#include <Wire.h>
#include<I2Cdev.h>
#include<MPU6050.h>
 
MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;

//motor pins

int Left_Reverse = 6; // Right motor control 1
int Left_Forward = 8; // Right motor control 2
int Right_Forward = 9; // Left motor control 1
int Right_Reverse = 10; // Left motor control 2

//-----SETUP-----

void setup(){
  //L298
  pinMode(Left_Forward, OUTPUT);
  pinMode(Left_Reverse, OUTPUT);
  pinMode(Right_Forward, OUTPUT);
  pinMode(Right_Reverse, OUTPUT);
  
  //mpu
  Serial.begin(9600);
  Serial.println("Initialize MPU");
  mpu.initialize();
}

//-------MAIN LOOP------

void loop(){

//------GYRO CODE-----

  //Main Gyro Code

   mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
   
   ax = map(ax, -17000, 17000, -1500, 1500);
 
   Serial.println(ax);

  //-----MOTOR RESPONSES----
  
  //--Main Motor Responses--
  
  //forward
  
  if (ax < center) {
    if (ax < center + medOffset) {
      if (prevdir = 0){
        analogWrite(Right_Forward, 0);
        analogWrite(Left_Forward, 0);
      }
    analogWrite(Right_Forward, med_speed);
    analogWrite(Left_Forward, med_speed);
    Serial.println("Medium Speed");
    delay(refreshMed);
    prevdir = 1;
  } 
   if (ax < center + bigOffset) {
     if (prevdir = 0){
        analogWrite(Right_Forward, 0);
        analogWrite(Left_Forward, 0);
      }
    analogWrite(Right_Forward, high_speed);
    analogWrite(Left_Forward, high_speed);
    Serial.println("High Speed");
    delay(refreshHigh);
    prevdir = 1;
  } 
  if (ax < center && ax > center + medOffset) {
    if (prevdir = 0){
        analogWrite(Right_Forward, 0);
        analogWrite(Left_Forward, 0);
      }
    analogWrite(Right_Forward, low_speed);
    analogWrite(Left_Forward, low_speed);
    Serial.println("Low Speed");
    delay(refreshLow);
    prevdir = 1;
  }
 }
 
 //reverse
 
  if (ax > center) { 
    if (ax > center - medOffset) {
      if (prevdir = 1){
        analogWrite(Right_Forward, 0);
        analogWrite(Left_Forward, 0);
      }
    analogWrite(Right_Reverse, med_speed);
    analogWrite(Left_Reverse, med_speed);
    Serial.println("Medium Speed");
    delay(refreshMed);
    prevdir = 0;
  }
   if (ax > center - bigOffset) {
    if (prevdir = 1){
        analogWrite(Right_Forward, 0);
        analogWrite(Left_Forward, 0);
      }
    analogWrite(Right_Reverse, high_speed);
    analogWrite(Left_Reverse, high_speed);
    Serial.println("High Speed");
    delay(refreshHigh);
    prevdir = 0;
  }
   if (ax > center && ax < center - medOffset){
    if (prevdir = 1){
        analogWrite(Right_Forward, 0);
        analogWrite(Left_Forward, 0);
      }
    analogWrite(Right_Reverse, low_speed);
    analogWrite(Left_Reverse, low_speed);
    Serial.println("Low Speed");
    delay(refreshLow);
    prevdir = 0;
   }
  }
  
}
