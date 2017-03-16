//tuning variables
float center = 50;
float multiplier = 2;

//float

float right_speed = 0;
float left_speed = 0;
float location_offset = 0;

float forward_speed = 0;
float reverse_speed = 0;

float refresh_time = 25;

float loop_counter = 0;

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
  
  location_offset = center - ax;
  refresh_time = location_offset/2;
  Serial.print("Location Offset: ");
  Serial.println(location_offset);
  if (location_offset < 0) {
    forward_speed = abs(location_offset)*multiplier;
  }
  if (location_offset > 0) {
    reverse_speed = abs(location_offset)*multiplier;
  }
  
  //cancelling the opposite
  
  if (forward_speed > 0){
    reverse_speed = 0;
  }
  if (reverse_speed > 0){
    forward_speed = 0;
  }
  
  //running the motors
  
  analogWrite(Right_Forward, forward_speed);
  analogWrite(Left_Forward, forward_speed);
  
  analogWrite(Right_Reverse, reverse_speed);
  analogWrite(Left_Reverse, reverse_speed);
  
  loop_counter = loop_counter + 1;
  
  if (loop_counter < 5){
    delay(20);
  }
  if (loop_counter > 4){
    delay(refresh_time);
  }
}
