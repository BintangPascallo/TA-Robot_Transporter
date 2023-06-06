// #if (ARDUINO >= 100)
// #include <Arduino.h>
// #else
// #include <WProgram.h>
// #endif

// #include "Kinematics.h"
// #include "base_config.h"
// #include "Encoder.h"

// #include <ros.h>
// #include <std_msgs/String.h>
// #include <geometry_msgs/Vector3Stamped.h>
// #include <geometry_msgs/Twist.h>

// Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER, LR_WHEELS_DISTANCE, FR_WHEELS_DISTANCE);

// //Encoder encoder(MOTOR_LEFT_ENC_A, MOTOR_LEFT_ENC_B, MOTOR_RIGHT_ENC_A, MOTOR_RIGHT_ENC_A);

// #define COMMAND_RATE 20  //hz

// unsigned long currentMillis;
// unsigned long previousArmMillis;
// unsigned long previousMillis;

// volatile long motor1_encoder_pos = 0;
// volatile long motor2_encoder_pos = 0;
// volatile long motor3_encoder_pos = 0;
// volatile long motor4_encoder_pos = 0;

// float encoder1_diff;
// float encoder2_diff;
// float encoder3_diff;
// float encoder4_diff;

// float encoder1_prev;
// float encoder2_prev;
// float encoder3_prev;
// float encoder4_prev;

// volatile long encoder1_pos;
// volatile long encoder2_pos;
// volatile long encoder3_pos;
// volatile long encoder4_pos;

// float act_rpm_motor1;
// float act_rpm_motor2;
// float act_rpm_motor3;
// float act_rpm_motor4;

// float req_linear_vel_x = 1;
// float req_linear_vel_y;
// float req_angular_vel_z;
// unsigned long prev_req_time = 0;

// ros::NodeHandle nh;

// // void sub_cmd(const geometry_msgs::Twist& cmd_msg) {
// //   //extract cmd_vel to linear and angular vel
// //   req_linear_vel_x = cmd_msg.linear.x;
// //   req_angular_vel_z = cmd_msg.angular.z;

// //   prev_req_time = millis();
// // }

// // ros::Subscriber<geometry_msgs::Twist> cmd_sub("cmd_vel", &sub_cmd);

// void setup() {
//   Serial.begin(9600);

//   // nh.initNode();
//   // nh.getHardware()->setBaud(57600);
//   // nh.subscribe(cmd_sub);

//   //5V pin 13
//   pinMode(53, OUTPUT);
//   digitalWrite(53, HIGH);

//   //GND pin 52
//   pinMode(52, OUTPUT);
//   digitalWrite(52, LOW);

//   pinMode(MOTOR1_ENCODER_A, INPUT_PULLUP);
//   pinMode(MOTOR1_ENCODER_B, INPUT_PULLUP);
//   pinMode(MOTOR2_ENCODER_A, INPUT_PULLUP);
//   pinMode(MOTOR2_ENCODER_B, INPUT_PULLUP);
//   pinMode(MOTOR3_ENCODER_A, INPUT_PULLUP);
//   pinMode(MOTOR3_ENCODER_B, INPUT_PULLUP);
//   pinMode(MOTOR4_ENCODER_A, INPUT_PULLUP);
//   pinMode(MOTOR4_ENCODER_B, INPUT_PULLUP);

//   attachInterrupt(digitalPinToInterrupt(MOTOR1_ENCODER_A), MOTOR1_ENC_A, CHANGE);
//   attachInterrupt(digitalPinToInterrupt(MOTOR1_ENCODER_B), MOTOR1_ENC_B, CHANGE);
// }

// void loop() {
//   static unsigned long prev_control_time = 0;
//   static unsigned long prev_debug_time = 0;
//   currentMillis = millis();

//   if (currentMillis - previousMillis >= 1000) {
//     detachInterrupt(digitalPinToInterrupt(MOTOR1_ENCODER_A));
//     previousMillis = currentMillis;

//     encoder1_diff = encoder1_pos - encoder1_prev;

//     act_rpm_motor1 = (encoder1_diff / COUNTS_PER_REV) * 60;

//     Serial.print("RPM _1 : ");
//     Serial.print(act_rpm_motor1);
//     Serial.println();

//     encoder1_prev = encoder1_pos;
//     attachInterrupt(digitalPinToInterrupt(MOTOR1_ENCODER_A), MOTOR1_ENC_A, CHANGE);
//   }

//   if ((millis() - prev_control_time) >= (1000 / COMMAND_RATE)) {
//     moveBase();
//     prev_control_time = millis();
//   }

//   // nh.spinOnce();
// }

// void moveBase() {
//   //get required rpm for each motor based on required velocities
//   Kinematics::rpm
//     req_rpm = kinematics.getRPM(req_linear_vel_x, req_linear_vel_y, req_angular_vel_z);

//   //get the current rpm of each motor
//   int motor1_rpm = req_rpm.motor1;
//   int motor2_rpm = req_rpm.motor2;
//   int motor3_rpm = req_rpm.motor3;
//   int motor4_rpm = req_rpm.motor4;

//   Serial.print("RPM 1 : ");
//   Serial.print(motor1_rpm);
//   Serial.println();

//   // get actual rpm from encoder data
//   Kinematics::velocities current_vel;
//   current_vel = kinematics.getVelocities(motor1_rpm, motor2_rpm, motor3_rpm, motor4_rpm);

//   Serial.print("VEL X: ");
//   Serial.print(current_vel.linear_x, 4);
//   Serial.println("");

//   Serial.print("VEL_Y: ");
//   Serial.print(current_vel.linear_y, 4);
//   Serial.println("");

//   Serial.print(" ANGULAR_Z: ");
//   Serial.println(current_vel.angular_z, 4);
//   Serial.println("");

//   // raw_vel_msg

//   delay(1000);
// }

// void MOTOR1_ENC_A() {
//   // look for a low-to-high on channel A
//   if (digitalRead(MOTOR1_ENCODER_A) == HIGH) {
//     // check channel B to see which way encoder is turning
//     if (digitalRead(MOTOR1_ENCODER_B) == LOW) { encoder1_pos = encoder1_pos + 1; }  // CW
//     else {
//       encoder1_pos = encoder1_pos - 1;
//     }     // CCW
//   } else  // must be a high-to-low edge on channel A
//   {
//     // check channel B to see which way encoder is turning
//     if (digitalRead(MOTOR1_ENCODER_B) == HIGH) { encoder1_pos = encoder1_pos + 1; }  // CW
//     else {
//       encoder1_pos = encoder1_pos - 1;
//     }  // CCW
//   }
// }

// void MOTOR1_ENC_B() {
//   // look for a low-to-high on channel B
//   if (digitalRead(MOTOR1_ENCODER_B) == HIGH) {
//     // check channel A to see which way encoder is turning
//     if (digitalRead(MOTOR1_ENCODER_A) == HIGH) { encoder1_pos = encoder1_pos + 1; }  // CW
//     else {
//       encoder1_pos = encoder1_pos - 1;
//     }  // CCW
//   }
//   // Look for a high-to-low on channel B
//   else {
//     // check channel B to see which way encoder is turning
//     if (digitalRead(MOTOR1_ENCODER_A) == LOW) { encoder1_pos = encoder1_pos + 1; }  // CW
//     else {
//       encoder1_pos = encoder1_pos - 1;
//     }  // CCW
//   }
// }

#include "Kinematics.h"
#include "base_config.h"

Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER, LR_WHEELS_DISTANCE, FR_WHEELS_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Kinematics::rpm rpm;

  /*kinematics.getRPM(linear_x, linear_y, angular_z);
    linear_x = target linear velocity in x axis (right hand rule)
    linear_y = target linear velocity in y axis (right hand rule)
    angular_z = target angular velocity in z axis (right hand rule)
  */
  //target velocities
  float linear_vel_x = 1.3;
  float linear_vel_y = 0;
  float angular_vel_z = 0;
  rpm = kinematics.getRPM(linear_vel_x, linear_vel_y, angular_vel_z);

  Serial.print(" FRONT LEFT MOTOR: ");
  Serial.print(rpm.motor1);
  Serial.println("");

  Serial.print(" FRONT RIGHT MOTOR: ");
  Serial.print(rpm.motor2);
  Serial.println("");

  Serial.print(" REAR LEFT MOTOR: ");
  Serial.print(rpm.motor3);
  Serial.println("");

  Serial.print(" REAR RIGHT MOTOR: ");
  Serial.println(rpm.motor4);
  Serial.println("");

  delay(1000);


  int motor1_feedback = rpm.motor1;  //in rpm
  int motor2_feedback = rpm.motor2;  //in rpm
  int motor3_feedback = rpm.motor3;  //in rpm
  int motor4_feedback = rpm.motor4;  //in rpm

  Kinematics::velocities vel;
  vel = kinematics.getVelocities(motor1_feedback, motor2_feedback, motor3_feedback, motor4_feedback);
  Serial.print(" VEL X: ");
  Serial.print(vel.linear_x, 4);
  Serial.println("");

  Serial.print(" VEL_Y: ");
  Serial.print(vel.linear_y, 4);
  Serial.println("");

  Serial.print(" ANGULAR_Z: ");
  Serial.println(vel.angular_z, 4);
  Serial.println("");
  Serial.println("");
}