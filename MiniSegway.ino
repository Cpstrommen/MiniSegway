//pin variables

//tuning variables

int refresh_time = 50;
int low_speed = 20;
int med_speed = 60;
int high_speed = 100;

//gyro variables

#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

//motor pins

int Left_Reverse = 6; // Right motor control 1
int Left_Forward = 8; // Right motor control 2
int Right_Forward = 9; // Left motor control 1
int Right_Reverse = 10; // Left motor control 2

//-----SETUP-----

void setup(){
  pinMode(Left_Forward, OUTPUT);
  pinMode(Left_Reverse, OUTPUT);
  pinMode(Right_Forward, OUTPUT);
  pinMode(Right_Reverse, OUTPUT);
  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

//-------MAIN LOOP------

void loop(){

//------GYRO CODE-----

  //Main Gyro Code

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);

  //-----MOTOR RESPONSES----
  
  //--Main Motor Responses--
  
  //smallest angles
  
  if (GyZ < 180) {
    analogWrite(Right_Reverse, 0);
    analogWrite(Left_Reverse, 0);
    analogWrite(Right_Forward, low_speed);
    analogWrite(Left_Forward, low_speed);
    delay(refresh_time);
  }
  if (GyZ > 180) {
    analogWrite(Right_Forward, 0);
    analogWrite(Left_Forward, 0);
    analogWrite(Right_Reverse, low_speed);
    analogWrite(Left_Reverse, low_speed);
    delay(refresh_time);
  }
  
  //biggest angles
  
  if (GyZ < 170) {
    analogWrite(Right_Reverse, 0);
    analogWrite(Left_Reverse, 0);
    analogWrite(Right_Forward, high_speed);
    analogWrite(Left_Forward, high_speed);
    delay(refresh_time);
  }
   if (GyZ > 190) {
    analogWrite(Right_Forward, 0);
    analogWrite(Left_Forward, 0);
    analogWrite(Right_Reverse, high_speed);
    analogWrite(Left_Reverse, high_speed);
    delay(refresh_time);
  }
  
  //middle angles
  
  if (GyZ < 175) {
    analogWrite(Right_Reverse, 0);
    analogWrite(Left_Reverse, 0);
    analogWrite(Right_Forward, med_speed);
    analogWrite(Left_Forward, med_speed);
    delay(refresh_time);
  }
   if (GyZ > 185) {
    analogWrite(Right_Forward, 0);
    analogWrite(Left_Forward, 0);
    analogWrite(Right_Reverse, med_speed);
    analogWrite(Left_Reverse, med_speed);
    delay(refresh_time);
  }
}
