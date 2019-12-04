#pragma once
#include <arduino.h>      //A library for arduino programming, most often not needed
#include "Wire.h"         //A library for I2C communication, native to Arduino
#include "I2Cdev.h"       //Soruce: http://wiki.seeedstudio.com/Grove-IMU_9DOF_v2.0/
#include "MPU9250.h"      //Soruce: http://wiki.seeedstudio.com/Grove-IMU_9DOF_v2.0/
#include "BMP280.h"       //Soruce: http://wiki.seeedstudio.com/Grove-IMU_9DOF_v2.0/
#include "MadgwickAHRS.h" //Source: https://github.com/arduino-libraries/MadgwickAHRS

MPU9250 accelgyro;
I2Cdev   I2C_M;
Madgwick filter;

float pitch, roll;

void setAngles() {
  int16_t ax, ay, az;     //(Temporarily) make 16 bit intergers to write the accelerometer's values too
  int16_t gx, gy, gz;     //(Temporarily) make 16 bit intergers to write the gyroscope's values too

  float Axyz[3];          //(Temporarily) make a float array to store the processed accelerometer data
  float Gxyz[3];          //(Temporarily) make a float array to store the processed gyroschope data

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);     //Read the IMU, write the read values to the 16 bit intergers created earlier
  Axyz[0] = (double) ax / 16384;          //Convert read values to G (9,81 M/S^2) of the x-axis and write to float array
  Axyz[1] = (double) ay / 16384;          //Convert read values to G (9,81 M/S^2) of the y-axis and write to float array
  Axyz[2] = (double) az / 16384;          //Convert read values to G (9,81 M/S^2) of the z-axis and write to float array

  Gxyz[0] = (double) gx * 250 / 32768;    //Convert read values to degrees/s over the x-axis and write to float array
  Gxyz[1] = (double) gy * 250 / 32768;    //Convert read values to degrees/s over the y-axis and write to float array
  Gxyz[2] = (double) gz * 250 / 32768;    //Convert read values to degrees/s over the z-axis and write to float array

  filter.updateIMU(Gxyz[0], Gxyz[1], Gxyz[2], Axyz[0], Axyz[1], Axyz[2]);   //Use the calculated acceleration and angle velocity to calculate a pitch and roll angle using the Madwick algorithm
  roll = filter.getRoll();      //Write the calculated roll to global variable "Roll"
  pitch = filter.getPitch();    //Write the calulated pitch to global variable "Pitch'
  };
