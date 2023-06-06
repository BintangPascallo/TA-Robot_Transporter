#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// LOGIC LIBRARY
#include "base_config.h"
#include "Motor.h"
#include "Arduino.h"
#include "Kinematics.h"
#include "ArduinoHardware.h"

// ROS LIBRARY
#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/Twist.h>

// ROS MESSAGE SPEED
#define COMMAND_RATE 20  //Hz
#define DEBUG_RATE 5

// CALCULATE KINEMATICS FOR MECANUM WHEEL
Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER, FR_WHEELS_DISTANCE, LR_WHEELS_DISTANCE);

// MOTOR DECLARE PIN
Controller motor1(MOTOR1_PWM, MOTOR1_IN_A, MOTOR1_IN_B);
Controller motor2(MOTOR2_PWM, MOTOR2_IN_A, MOTOR2_IN_B);
Controller motor3(MOTOR3_PWM, MOTOR3_IN_A, MOTOR3_IN_B);
Controller motor4(MOTOR4_PWM, MOTOR4_IN_A, MOTOR4_IN_B);

// REQUIRED VELOCITIES FROM CMD_VEL
float req_linear_vel_x = 0.0;
float req_linear_vel_y = 0.0;
float req_angular_vel_z = 0.0;

// ENCODER POSITION VALUE
volatile int encoderPos_1 = 0;
volatile int encoderPos_2 = 0;
volatile int encoderPos_3 = 0;
volatile int encoderPos_4 = 0;

// ACTUAL RPM MOTOR VALUE
float actual_rpm_motor1 = 0.0;
float actual_rpm_motor2 = 0.0;
float actual_rpm_motor3 = 0.0;
float actual_rpm_motor4 = 0.0;

// ACTUAL VELOCITY MTOOR VALUE
float actual_veloicity_motor1 = 0.0;
float actual_veloicity_motor2 = 0.0;
float actual_veloicity_motor3 = 0.0;
float actual_veloicity_motor4 = 0.0;

// REAL TIME VARIABLE
unsigned long currentMillis;
unsigned long previousArmMillis;
unsigned long previousMillis;
unsigned long lastDisplayTime = 0;
unsigned long prev_req_time = 0;

// PID SETTINGS
float output = 0.0;
float speed = 0.0;
float lastError = 0;  // declares the last error
float setpoint;       // declares the setpoint
float error = 0;      // current error
float I_error = 0;    // integral gain
float D_error = 0;    // derivative gain

// 100 MS
// float KP = 0.05;      // proportional constant
// float KI = 0.02;  // integrative constant
// float KD = 0.001;    // derivative constant

// 1000 MS
// float KP = 0.15;      // proportional constant
// float KI = 0.00025;  // integrative constant
// float KD = 0.002;    // derivative constant

// ROS NODE HANDLER
ros::NodeHandle nh;

void sub_cmd(const geometry_msgs::Twist& cmd_msg) {
  // GET CMD_VEL VALUE
  req_linear_vel_x = cmd_msg.linear.x;
  req_linear_vel_y = cmd_msg.linear.y;
  req_angular_vel_z = cmd_msg.angular.z;

  prev_req_time = millis();
}

// ROS SUBSRCRIBE FROM CMD_VEL
ros::Subscriber<geometry_msgs::Twist> cmd_sub("cmd_vel", &sub_cmd);

// ROS PUBLISH TO RAW_VEL
geometry_msgs::Twist raw_vel_msg;
ros::Publisher raw_vel("raw_vel", &raw_vel_msg);

void setup() {
  // SETUP ROS PROGRAM
  nh.initNode();
  nh.subscribe(cmd_sub);
  nh.advertise(raw_vel);
  // nh.getHardware()->setBaud(57600);

  // SETUP PIN FOR ARDUINO
  setupPin();

  // Serial.begin(9600);
}

void loop() {
  static unsigned long prev_control_time = 0;
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - lastDisplayTime;

  if (elapsedTime >= 100) {
    detachInterrupt(digitalPinToInterrupt(MOTOR1_ENCODER_A));
    detachInterrupt(digitalPinToInterrupt(MOTOR2_ENCODER_A));
    detachInterrupt(digitalPinToInterrupt(MOTOR3_ENCODER_A));
    detachInterrupt(digitalPinToInterrupt(MOTOR4_ENCODER_A));

    actual_rpm_motor1 = (encoderPos_1 * 60.0) / 665.0 * 10;
    actual_rpm_motor2 = (encoderPos_2 * 60.0) / 665.0 * 10;
    actual_rpm_motor3 = (encoderPos_3 * 60.0) / 665.0 * 10;
    actual_rpm_motor4 = (encoderPos_4 * 60.0) / 665.0 * 10;

    encoderPos_1 = 0;
    encoderPos_2 = 0;
    encoderPos_3 = 0;
    encoderPos_4 = 0;

    // actual_veloicity_motor1 = (3.1415926536 * 0.08 * actual_rpm_motor1) / 60;
    // actual_veloicity_motor2 = (3.1415926536 * 0.08 * actual_rpm_motor2) / 60;
    // actual_veloicity_motor3 = (3.1415926536 * 0.08 * actual_rpm_motor3) / 60;
    // actual_veloicity_motor4 = (3.1415926536 * 0.08 * actual_rpm_motor4) / 60;

    // Serial.print("RPM 1 : ");
    // Serial.print(actual_rpm_motor1);
    // Serial.print(" | RPM 2 : ");
    // Serial.print(actual_rpm_motor2);
    // Serial.print(" | RPM 3 : ");
    // Serial.print(actual_rpm_motor3);
    // Serial.print(" | RPM 4 : ");
    // Serial.print(actual_rpm_motor4);
    // Serial.println("");

    // Serial.print("VEL 1 : ");
    // Serial.print(actual_veloicity_motor1);
    // Serial.print("   | VEL 2 : ");
    // Serial.print(actual_veloicity_motor2);
    // Serial.print("   | VEL 3 : ");
    // Serial.print(actual_veloicity_motor3);
    // Serial.print("   | VEL 4 : ");
    // Serial.print(actual_veloicity_motor4);
    // Serial.println("");

    Kinematics::velocities current_vel;
    current_vel = kinematics.getVelocities(actual_rpm_motor1, actual_rpm_motor2, actual_rpm_motor3, actual_rpm_motor4);

    // Serial.print("X : ");
    // Serial.println(current_vel.linear_x);
    // Serial.print("Y : ");
    // Serial.println(current_vel.linear_y);
    // Serial.print("Z : ");
    // Serial.println(current_vel.angular_z);
    // Serial.println();

    // Serial.print("X : ");
    // Serial.println(current_vel.linear_x);
    // Serial.print("Y : ");
    // Serial.println(current_vel.linear_y);
    // Serial.print("Z : ");
    // Serial.println(current_vel.angular_z);
    // Serial.println();

    raw_vel_msg.linear.x = current_vel.linear_x;
    raw_vel_msg.linear.y = current_vel.linear_y;
    raw_vel_msg.angular.z = current_vel.angular_z;
    raw_vel.publish(&raw_vel_msg);

    lastDisplayTime = currentTime;
    attachInterrupt(digitalPinToInterrupt(MOTOR1_ENCODER_A), encoder_1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MOTOR2_ENCODER_A), encoder_2, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MOTOR3_ENCODER_A), encoder_3, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MOTOR4_ENCODER_A), encoder_4, CHANGE);
  }

  if ((millis() - prev_control_time) >= (1000 / COMMAND_RATE)) {
    Kinematics::rpm req_rpm = kinematics.getRPM(req_linear_vel_x, req_linear_vel_y, req_angular_vel_z);

    int motor1_rpm = req_rpm.motor1;
    int motor2_rpm = req_rpm.motor2;
    int motor3_rpm = req_rpm.motor3;
    int motor4_rpm = req_rpm.motor4;

    // setpoint = motor1_rpm; // rpm motor yang dibutuhkan
    // speed = actual_rpm_motor1;
    // error = setpoint - speed;

    // I_error += error;
    // D_error = lastError - error;

    // output += KP * error + KI * I_error + KD * D_error;
    // output = constrain(output, 10, 255);
    // Serial.println(actual_rpm_motor1);

    // Serial.print("RPM 1 : ");
    // Serial.println(actual_rpm_motor1);
    // Serial.print(" | RPM 2 : ");
    // Serial.print(motor2_rpm);
    // Serial.print(" | RPM 3 : ");
    // Serial.print(motor3_rpm);
    // Serial.print(" | RPM 4 : ");
    // Serial.print(motor4_rpm);
    // Serial.println("");

    motor1.spin(map(((int)motor1_rpm), 0, MAX_RPM, 0, 255));
    motor2.spin(map(((int)motor2_rpm), 0, MAX_RPM, 0, 255));
    motor3.spin(map(((int)motor3_rpm), 0, MAX_RPM, 0, 255));
    motor4.spin(map(((int)motor4_rpm), 0, MAX_RPM, 0, 255));

    // motor1.spin(map(((int)output), 0, MAX_RPM, 0, 255));
    // motor2.spin(map(((int)motor2_rpm), 0, MAX_RPM, 0, 255));
    // motor3.spin(map(((int)motor3_rpm), 0, MAX_RPM, 0, 255));
    // motor4.spin(map(((int)motor4_rpm), 0, MAX_RPM, 0, 255));

    prev_control_time = millis();
  }

  if ((millis() - prev_control_time) >= 400) {
    req_linear_vel_x = 0;
    req_linear_vel_y = 0;
    req_angular_vel_z = 0;
  }

  nh.spinOnce();
}

// INTERRUPT FOR CALCULATE ENCODER
void encoder_1() {
  // Cek arah putaran
  if (digitalRead(MOTOR1_ENCODER_A) == digitalRead(MOTOR1_ENCODER_B)) {
    encoderPos_1--;
  } else {
    encoderPos_1++;
  }
}

void encoder_2() {
  // Cek arah putaran
  if (digitalRead(MOTOR2_ENCODER_A) == digitalRead(MOTOR2_ENCODER_B)) {
    encoderPos_2++;
  } else {
    encoderPos_2--;
  }
}

void encoder_3() {
  // Cek arah putaran
  if (digitalRead(MOTOR3_ENCODER_A) == digitalRead(MOTOR3_ENCODER_B)) {
    encoderPos_3++;
  } else {
    encoderPos_3--;
  }
}
void encoder_4() {
  // Cek arah putaran
  if (digitalRead(MOTOR4_ENCODER_A) == digitalRead(MOTOR4_ENCODER_B)) {
    encoderPos_4++;
  } else {
    encoderPos_4--;
  }
}

void setupPin() {
  // ENCODER PIN MODE
  pinMode(MOTOR1_ENCODER_A, INPUT_PULLUP);
  pinMode(MOTOR1_ENCODER_B, INPUT_PULLUP);
  pinMode(MOTOR2_ENCODER_A, INPUT_PULLUP);
  pinMode(MOTOR2_ENCODER_B, INPUT_PULLUP);
  pinMode(MOTOR3_ENCODER_A, INPUT_PULLUP);
  pinMode(MOTOR3_ENCODER_B, INPUT_PULLUP);
  pinMode(MOTOR4_ENCODER_A, INPUT_PULLUP);
  pinMode(MOTOR4_ENCODER_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(MOTOR1_ENCODER_A), encoder_1, CHANGE);
  //   // attachInterrupt(digitalPinToInterrupt(MOTOR1_ENCODER_B), handleEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MOTOR2_ENCODER_A), encoder_2, CHANGE);
  //   // attachInterrupt(digitalPinToInterrupt(MOTOR2_ENCODER_B), handleEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MOTOR3_ENCODER_A), encoder_3, CHANGE);
  //   // attachInterrupt(digitalPinToInterrupt(MOTOR3_ENCODER_B), handleEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MOTOR4_ENCODER_A), encoder_4, CHANGE);
  //   // attachInterrupt(digitalPinToInterrupt(MOTOR4_ENCODER_B), handleEncoderInterrupt, CHANGE);

  //5V pin 21
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);
  //GND pin 22
  pinMode(22, OUTPUT);
  digitalWrite(22, LOW);
  //5V pin 26
  pinMode(26, OUTPUT);
  digitalWrite(26, HIGH);
  //5V pin 40
  pinMode(40, OUTPUT);
  digitalWrite(40, HIGH);
  //5V pin 47
  pinMode(47, OUTPUT);
  digitalWrite(47, HIGH);
  //GND pin 29
  pinMode(29, OUTPUT);
  digitalWrite(29, LOW);
  //GND pin 43
  pinMode(43, OUTPUT);
  digitalWrite(43, LOW);
  //GND pin 44
  pinMode(44, OUTPUT);
  digitalWrite(44, LOW);
  //5V pin 13
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
  //GND pin 52
  pinMode(52, OUTPUT);
  digitalWrite(52, LOW);
}
