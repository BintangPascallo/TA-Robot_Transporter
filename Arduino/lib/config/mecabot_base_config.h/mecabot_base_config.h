#ifndef MECABOT_BASE_CONFIG_H
#define MECABOT_BASE_CONFIG_H

// PID CONTROL
#define K_P 0.6  // P constant
#define K_I 0.3  // I constant
#define K_D 0.5  // D constant

// ROBOT CONFIGURATION
#define MAX_RPM 330               // motor's maximum RPM
#define COUNTS_PER_REV 365        // wheel encoder's no of ticks per rev
#define WHEEL_DIAMETER 0.08       // wheel's diameter in meters
#define PWM_BITS 8                // PWM Resolution of the microcontroller
#define LR_WHEELS_DISTANCE 0.235  // distance between left and right wheels
#define FR_WHEELS_DISTANCE 0.30   // distance between front and rear wheels. Ignore this if you're on 2WD/ACKERMANN

// ENCODER PINS
#define MOTOR1_ENCODER_A 15
#define MOTOR1_ENCODER_B 14

#define MOTOR2_ENCODER_A 11
#define MOTOR2_ENCODER_B 12

#define MOTOR3_ENCODER_A 17
#define MOTOR3_ENCODER_B 16

#define MOTOR4_ENCODER_A 9
#define MOTOR4_ENCODER_B 10

// MOTOR PINS
#define MOTOR1_PWM 1
#define MOTOR1_IN_A 21
#define MOTOR1_IN_B 20

#define MOTOR2_PWM 8
#define MOTOR2_IN_A 5
#define MOTOR2_IN_B 6

#define MOTOR3_PWM 0
#define MOTOR3_IN_A 22
#define MOTOR3_IN_B 23

#define MOTOR4_PWM 2
#define MOTOR4_IN_A 4
#define MOTOR4_IN_B 3

// #define PWM_MAX 400
// #define PWM_MIN -PWM_MAX

#endif
