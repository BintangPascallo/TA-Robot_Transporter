#include "Motor.h"
#include "base_config.h"

void Controller::updateSpeed(long encoder_ticks)
{
  //this function calculates the motor's RPM based on encoder ticks and delta time
  unsigned long current_time = millis();
  unsigned long dt = current_time - prev_update_time_;

  //convert the time from milliseconds to minutes
  double dtm = (double)dt / 60000;
  double delta_ticks = encoder_ticks - prev_encoder_ticks_;

  //calculate wheel's speed (RPM)
  rpm = (delta_ticks / counts_per_rev_) / dtm;

  prev_update_time_ = current_time;
  prev_encoder_ticks_ = encoder_ticks;
}

Controller::Controller(int pwm_pin, int motor_pinA, int motor_pinB):
  pwm_pin_(pwm_pin),
  motor_pinA_(motor_pinA),
  motor_pinB_(motor_pinB)
{
  pinMode(en_pinA_, OUTPUT);
  pinMode(en_pinB_, OUTPUT);
  pinMode(motor_pinA_, OUTPUT);
  pinMode(motor_pinB_, OUTPUT);
}

void Controller::spin(int pwm)
{
  // CW
  if (pwm > 0)
  {
    digitalWrite(en_pinA_, LOW);
    digitalWrite(en_pinB_, HIGH);
  }
  // CCW
  else if (pwm < 0)
  {
    digitalWrite(en_pinA_, HIGH);
    digitalWrite(en_pinB_, LOW);
  }
  else
  {
    digitalWrite(en_pinA_, LOW);
    digitalWrite(en_pinB_, LOW);
  }

  analogWrite(pwm_pin_, pwm);
}