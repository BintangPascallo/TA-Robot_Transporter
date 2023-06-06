#include "Motor.h"
#include "base_config.h"
#include "Arduino.h"

void Controller::updateSpeed(long encoder_ticks) {
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

Controller::Controller(int pwm_pin, int motor_pinA, int motor_pinB)
  : pwm_pin_(pwm_pin),
    motor_pinA_(motor_pinA),
    motor_pinB_(motor_pinB) {
  // enc_pinA_(enc_pinA),
  // enc_pinB_(enc_pinB) {

  // pinMode(enc_pinA_, INPUT_PULLUP);
  // pinMode(enc_pinB_, INPUT_PULLUP);
  pinMode(motor_pinA_, OUTPUT);
  pinMode(motor_pinB_, OUTPUT);
  pinMode(pwm_pin_, OUTPUT);

  // attachInterrupt(digitalPinToInterrupt(enc_pinA_), handleEncoderInterrupt, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(enc_pinB_), handleEncoderInterrupt, CHANGE);
}

void Controller::spin(int pwm) {
  // CW
  if (pwm > 0) {
    digitalWrite(motor_pinA_, HIGH);
    digitalWrite(motor_pinB_, LOW);
  }
  // CCW
  else if (pwm < 0) {
    digitalWrite(motor_pinA_, LOW);
    digitalWrite(motor_pinB_, HIGH);
  } else {
    digitalWrite(motor_pinA_, LOW);
    digitalWrite(motor_pinB_, LOW);
  }

  analogWrite(pwm_pin_, pwm);
  // Serial.print("PWM : ");
  // Serial.println(pwm);
  // Serial.println(motor_pinA_);
  // Serial.println(motor_pinB_);
}