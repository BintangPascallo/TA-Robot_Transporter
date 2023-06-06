#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Controller
{
  public:
    int rpm;
    static int counts_per_rev_;
    volatile int encoderPos;
    unsigned long lastDisplayTime;
    unsigned long currentTime;
    unsigned long elapsedTime;
    float velocity;

    Controller(int pwm_pin, int motor_pinA, int motor_pinB);
    void updateSpeed(long encoder_ticks);
    void spin(int pwm);

  private:
    long prev_encoder_ticks_;
    unsigned long prev_update_time_;
    int motor_pinA_;
    int motor_pinB_;
    int enc_pinA_;
    int enc_pinB_;
    int pwm_pin_;
};

#endif