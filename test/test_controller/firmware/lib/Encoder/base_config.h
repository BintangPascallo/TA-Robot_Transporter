#ifndef MECABOT_BASE_CONFIG_H
#define MECABOT_BASE_CONFIG_H

// PID CONTROL
#define K_P 0.6  // P constant
#define K_I 0.3  // I constant
#define K_D 0.5  // D constant

// ROBOT CONFIGURATION
#define MAX_RPM 330               // motor's maximum RPM
#define COUNTS_PER_REV 665        // wheel encoder's no of ticks per rev
#define WHEEL_DIAMETER 0.08       // wheel's diameter in meters
#define PWM_BITS 8                // PWM Resolution of the microcontroller
#define LR_WHEELS_DISTANCE 0.37  // distance between left and right wheels
#define FR_WHEELS_DISTANCE 0.335   // distance between front and rear wheels. Ignore this if you're on 2WD/ACKERMANN

// ENCODER PINS
#define MOTOR1_ENCODER_A 28
#define MOTOR1_ENCODER_B 45

#define MOTOR2_ENCODER_A 19
#define MOTOR2_ENCODER_B 20

#define MOTOR3_ENCODER_A 45
#define MOTOR3_ENCODER_B 46

#define MOTOR4_ENCODER_A 41
#define MOTOR4_ENCODER_B 42

// MOTOR PINS PWM
#define MOTOR1_PWM 10
#define MOTOR2_PWM 5
#define MOTOR3_PWM 11
#define MOTOR4_PWM 6

// MOTOR PINS POLARITY
#define MOTOR1_IN_A 14
#define MOTOR1_IN_B 15

#define MOTOR2_IN_A 7
#define MOTOR2_IN_B 8

#define MOTOR3_IN_A 16
#define MOTOR3_IN_B 17

#define MOTOR4_IN_A 4
#define MOTOR4_IN_B 9

#define PWM_MAX pow(2, PWM_BITS) - 1
#define PWM_MIN -PWM_MAX

#endif