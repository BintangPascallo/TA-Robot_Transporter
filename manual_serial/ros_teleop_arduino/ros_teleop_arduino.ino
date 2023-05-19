#include <ros.h>
#include <geometry_msgs/Twist.h>

#define BRAKE 0
#define CW 1
#define CCW 2
#define CS_THRESHOLD 15  // Definition of safety current (Check: "1.3 Monster Shield Example").

// MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

// MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

// MOTOR 3
#define MOTOR_A3_PIN 14
#define MOTOR_B3_PIN 15

// MOTOR 4
#define MOTOR_A4_PIN 16
#define MOTOR_B4_PIN 17

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6
#define PWM_MOTOR_3 10
#define PWM_MOTOR_4 11

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3
#define CURRENT_SEN_3 A4
#define CURRENT_SEN_4 A5

#define EN_PIN_1 A0
#define EN_PIN_2 A1
#define EN_PIN_3 A6
#define EN_PIN_4 A7

#define MOTOR_1 0
#define MOTOR_2 1
#define MOTOR_3 20
#define MOTOR_4 21

short usSpeed = 130;  //default motor speed
unsigned short usMotor_Status = BRAKE;
unsigned short usMotor_Status1 = BRAKE;
unsigned short usMotor_Status2 = BRAKE;

void onTwist(const geometry_msgs::Twist& msg) {
  // forward
  if (msg.linear.x > 0) {
    Forward();
  }
  // backward
  else if (msg.linear.x < 0) {
    Backward();
  }
  // right
  else if (msg.angular.z < 0) {
    Right();
  }
  // left
  else if (msg.angular.z > 0) {
    Left();
  }
  // upright
  else if (msg.linear.x > 0 && msg.angular.z < 0) {
    UpRight();
  }
  // upleft
  else if (msg.linear.x > 0 && msg.angular.z > 0) {
    UpRight();
  }
  // bottomright
  else if (msg.linear.x < 0 && msg.angular.z > 0) {
    UpRight();
  }
  // bottomleft
  else if (msg.linear.x < 0 && msg.angular.z < 0) {
    UpRight();
  }
  // stop
  else {
    Stop();
  }

  delay(100);  //waktu tunda sebesar 100ms
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", onTwist);

ros::NodeHandle nh;

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);

  //motor 1
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);
  //motor 2
  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);
  //motor 3
  pinMode(MOTOR_A3_PIN, OUTPUT);
  pinMode(MOTOR_B3_PIN, OUTPUT);
  //motor 4
  pinMode(MOTOR_A4_PIN, OUTPUT);
  pinMode(MOTOR_B4_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);
  pinMode(PWM_MOTOR_3, OUTPUT);
  pinMode(PWM_MOTOR_4, OUTPUT);

  pinMode(CURRENT_SEN_1, OUTPUT);
  pinMode(CURRENT_SEN_2, OUTPUT);
  pinMode(CURRENT_SEN_3, OUTPUT);
  pinMode(CURRENT_SEN_4, OUTPUT);

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);
  pinMode(EN_PIN_3, OUTPUT);
  pinMode(EN_PIN_4, OUTPUT);

  //5V pin 13
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);

  //GND pin 52
  pinMode(52, OUTPUT);
  digitalWrite(52, LOW);

  digitalWrite(EN_PIN_1, HIGH);
  digitalWrite(EN_PIN_2, HIGH);
  digitalWrite(EN_PIN_3, HIGH);
  digitalWrite(EN_PIN_4, HIGH);

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  // put your main code here, to run repeatedly:
  // char serial_input;

  // serial_input = Serial.read();
  nh.spinOnce();
}

void Stop() {
  // Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
  motorGo(MOTOR_2, usMotor_Status, 0);
  motorGo(MOTOR_3, usMotor_Status, 0);
  motorGo(MOTOR_4, usMotor_Status, 0);
}

void Forward() {
  // Serial.println("Forward");
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  motorGo(MOTOR_3, usMotor_Status, usSpeed);
  motorGo(MOTOR_4, usMotor_Status, usSpeed);
}

void Backward() {
  usMotor_Status = CCW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  motorGo(MOTOR_3, usMotor_Status, usSpeed);
  motorGo(MOTOR_4, usMotor_Status, usSpeed);
}

void Right() {
  usMotor_Status1 = CCW;
  usMotor_Status2 = CW;
  motorGo(MOTOR_1, usMotor_Status2, usSpeed);
  motorGo(MOTOR_2, usMotor_Status1, usSpeed);
  motorGo(MOTOR_3, usMotor_Status1, usSpeed);
  motorGo(MOTOR_4, usMotor_Status2, usSpeed);
}

void Left() {
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  motorGo(MOTOR_1, usMotor_Status2, usSpeed);
  motorGo(MOTOR_2, usMotor_Status1, usSpeed);
  motorGo(MOTOR_3, usMotor_Status1, usSpeed);
  motorGo(MOTOR_4, usMotor_Status2, usSpeed);
}

void UpRight() {
  usSpeed = usSpeed;
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status1, 150);
  motorGo(MOTOR_2, usMotor_Status, 0);
  motorGo(MOTOR_3, usMotor_Status, 0);
  motorGo(MOTOR_4, usMotor_Status1, 150);
}

void BottomRight() {
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status2, 150);
  motorGo(MOTOR_2, usMotor_Status, 0);
  motorGo(MOTOR_3, usMotor_Status, 0);
  motorGo(MOTOR_4, usMotor_Status2, 150);
}

void UpLeft() {
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
  motorGo(MOTOR_2, usMotor_Status1, 150);
  motorGo(MOTOR_3, usMotor_Status1, 150);
  motorGo(MOTOR_4, usMotor_Status, 0);
}

void BottonLeft() {
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
  motorGo(MOTOR_2, usMotor_Status2, 150);
  motorGo(MOTOR_3, usMotor_Status2, 150);
  motorGo(MOTOR_4, usMotor_Status, 0);
}

void IncreaseSpeed() {
  usSpeed = usSpeed + 10;
  if (usSpeed > 255) {
    usSpeed = 255;
  }

  Serial.print("Speed +: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  motorGo(MOTOR_3, usMotor_Status, usSpeed);
  motorGo(MOTOR_4, usMotor_Status, usSpeed);
}

void DecreaseSpeed() {
  usSpeed = usSpeed - 10;
  if (usSpeed < 0) {
    usSpeed = 0;
  }

  Serial.print("Speed -: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  motorGo(MOTOR_3, usMotor_Status, usSpeed);
  motorGo(MOTOR_4, usMotor_Status, usSpeed);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)  //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if (motor == MOTOR_1) {
    if (direct == CW) {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);
    } else if (direct == CCW) {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, HIGH);
    } else {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);
    }
    analogWrite(PWM_MOTOR_1, pwm);
  } else if (motor == MOTOR_2) {
    if (direct == CW) {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, HIGH);
    } else if (direct == CCW) {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);
    } else {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);
    }
    analogWrite(PWM_MOTOR_2, pwm);
  } else if (motor == MOTOR_3) {
    if (direct == CW) {
      digitalWrite(MOTOR_A3_PIN, LOW);
      digitalWrite(MOTOR_B3_PIN, HIGH);
    } else if (direct == CCW) {
      digitalWrite(MOTOR_A3_PIN, HIGH);
      digitalWrite(MOTOR_B3_PIN, LOW);
    } else {
      digitalWrite(MOTOR_A3_PIN, LOW);
      digitalWrite(MOTOR_B3_PIN, LOW);
    }
    analogWrite(PWM_MOTOR_3, pwm);
  } else if (motor == MOTOR_4) {
    if (direct == CW) {
      digitalWrite(MOTOR_A4_PIN, LOW);
      digitalWrite(MOTOR_B4_PIN, HIGH);
    } else if (direct == CCW) {
      digitalWrite(MOTOR_A4_PIN, HIGH);
      digitalWrite(MOTOR_B4_PIN, LOW);

    } else {
      digitalWrite(MOTOR_A4_PIN, LOW);
      digitalWrite(MOTOR_B4_PIN, LOW);
    }
    analogWrite(PWM_MOTOR_4, pwm);
  }
}