#include "Kinematics.h"
// #include "base_config.h"

#define MOTOR_MAX_RPM 330
#define WHEEL_DIAMETER 0.8
#define WHEEL_DIST_X 0.33
#define WHEEL_DIST_Y 0.37

Kinematics kinematics(MOTOR_MAX_RPM, WHEEL_DIAMETER, WHEEL_DIST_X, WHEEL_DIST_Y);

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
  float linear_vel_x = 1;
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