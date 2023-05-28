// ARDUINO SETUP
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// HARDWARE CONFIGURATION
#include <Kinematics.h>
#include "base_config.h"
#include "Motor.h"
#include "ArduinoHardware.h"
#include "Encoder.h"

// ROS PROGRAM
#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/Twist.h>
#include <ros/time.h>

// MESSAGE 
#define COMMAND_RATE 20 //hz
#define DEBUG_RATE 5

// KINEMATICS CONFIGURATION
Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER, WHEELS_DISTANCE, PWM_BITS);

// ENCODER CONFIGURATION
Encoder motor1_encoder(MOTOR1_ENCODER_A, MOTOR1_ENCODER_B, COUNTS_PER_REV);
Encoder motor2_encoder(MOTOR2_ENCODER_A, MOTOR2_ENCODER_B, COUNTS_PER_REV); 
Encoder motor3_encoder(MOTOR3_ENCODER_A, MOTOR3_ENCODER_B, COUNTS_PER_REV); 
Encoder motor4_encoder(MOTOR4_ENCODER_A, MOTOR4_ENCODER_B, COUNTS_PER_REV); 

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
