#include "Motor.h"
#include "base_config.h"

Controller motor1(MOTOR1_PWM, MOTOR1_IN_A, MOTOR1_IN_B);
int Controller::counts_per_rev_ = 0;
long ticks = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //5V pin 21
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);
  //GND pin 18
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
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

void loop() {
  motor1.updateSpeed(ticks);
  Serial.println(ticks);
  delay(1000);
}
