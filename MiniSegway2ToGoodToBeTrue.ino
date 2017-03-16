//pin variables


//tuning variables

int low_speed = 175;
int med_speed = 250;
int high_speed = 325;

int center = 130;
int medOffset = 100;
int bigOffset = 150;

int refreshLow = 25;
int refreshMed = 50;
int refreshHigh = 75;

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
  
  //smallest angles
  
  if (ax < center) {
    analogWrite(Right_Reverse, 0);
    analogWrite(Left_Reverse, 0);
    analogWrite(Right_Forward, low_speed);
    analogWrite(Left_Forward, low_speed);
    Serial.println("Low Speed");
    delay(refreshLow);
  }
  if (ax > center) {
    analogWrite(Right_Forward, 0);
    analogWrite(Left_Forward, 0);
    analogWrite(Right_Reverse, low_speed);
    analogWrite(Left_Reverse, low_speed);
    Serial.println("Low Speed");
    delay(refreshLow);
  }
  
  //biggest angles
  
  if (ax < center + bigOffset) {
    analogWrite(Right_Reverse, 0);
    analogWrite(Left_Reverse, 0);
    analogWrite(Right_Forward, high_speed);
    analogWrite(Left_Forward, high_speed);
    Serial.println("High Speed");
    delay(refreshMed);
  }
   if (ax > center - bigOffset) {
    analogWrite(Right_Forward, 0);
    analogWrite(Left_Forward, 0);
    analogWrite(Right_Reverse, high_speed);
    analogWrite(Left_Reverse, high_speed);
    Serial.println("High Speed");
    delay(refreshMed);
  }
  
  //middle angles
  
  if (ax < center + medOffset) {
    analogWrite(Right_Reverse, 0);
    analogWrite(Left_Reverse, 0);
    analogWrite(Right_Forward, med_speed);
    analogWrite(Left_Forward, med_speed);
    Serial.println("Medium Speed");
    delay(refreshMed);
  }
   if (ax > center - medOffset) {
    analogWrite(Right_Forward, 0);
    analogWrite(Left_Forward, 0);
    analogWrite(Right_Reverse, med_speed);
    analogWrite(Left_Reverse, med_speed);
    Serial.println("Medium Speed");
    delay(refreshMed);
  }
}
