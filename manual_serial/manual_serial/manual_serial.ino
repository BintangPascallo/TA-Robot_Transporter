// #include <ezButton.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

#define BRAKE 0
#define CW 1
#define CCW 2
#define CS_THRESHOLD 15  // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

//Motor 3
#define MOTOR_A3_PIN 14
#define MOTOR_B3_PIN 15

//Motor 4
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

//ini joystick
int x_Pin = A15;  //Nama alias pin A1 yaitu xPin
int y_Pin = A14;  //Nama aliasa pin A0 yaitu yPin
// #define SW_PIN 51  // Arduino pin connected to SW  pin

// ezButton button(SW_PIN);

//nilai default
// int x_Position = 0;
// int y_Position = 0;
// int bValue = 0;  // To store value of the button

short usSpeed = 200;  //default motor speed
unsigned short usMotor_Status = BRAKE;
unsigned short usMotor_Status1 = BRAKE;
unsigned short usMotor_Status2 = BRAKE;

void setup() {
  // JOYSTICK //
  // pinMode(x_Pin, INPUT);
  // pinMode(y_Pin, INPUT);
  // button.setDebounceTime(50);  // set debounce time to 50 milliseconds

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

  Serial.begin(9600);

  //Initiates the serial to do the monitoring
  Serial.println("Begin motor control");
  Serial.println();  //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("0.Gerakan Parabola");
  Serial.println("1. STOP");
  Serial.println("2. FORWARD");
  Serial.println("3. REVERSE");
  Serial.println("4.Putar balik kanan");
  Serial.println("5. Jalan Samping Kanan");
  Serial.println("6. Jalan Samping Kiri");
  Serial.println("7.360");
  Serial.println("8.Serong Kanan");
  Serial.println("9.Serong Kiri");
  Serial.println("+. INCREASE SPEED");
  Serial.println("-. DECREASE SPEED");
  Serial.println();

  digitalWrite(EN_PIN_1, HIGH);
  digitalWrite(EN_PIN_2, HIGH);
  digitalWrite(EN_PIN_3, HIGH);
  digitalWrite(EN_PIN_4, HIGH);
}

void loop() {
  char user_input;

  //   button.loop();

  //   //Pembacaan kondisi
  //   x_Position = analogRead(x_Pin);
  //   y_Position = analogRead(y_Pin);

  //   // // Read the button value
  //   bValue = button.getState();

  //   if (button.isPressed()) {
  //     Serial.println("The button is pressed");
  // #ion < 600) {
  //   Forward();
  // } else if (x_Position > 700 && y_Position < 600 && y_Position > 400) {
  //   Reverse();
  // } else if (x_Position > 400 && x_Position < 600 && y_Position < 200) {
  //   jalansampingkanan();
  // } else if (x_Position > 400 && x_Position < 600 && y_Position > 700) {
  //   jalansampingkiri();
  // } else if (x_Position < 200 && y_Position < 200) {
  //   gerak360();
  // } else if (x_Position < 200 && y_Position > 700) {
  //   gerakanparabola();
  // } else if (x_Position > 700 && y_Position < 200) {
  //   putarbalik();
  // } else if (x_Position > 700 && y_Position > 700) {
  //   serongkananbawah();
  // } else {
  //   Stop();
  // }

  // Serial.print("X: ");
  // Serial.println(x_Position);
  // Serial.print("Y: ");
  // Serial.println(y_Position);

  while (Serial.available()) {
    user_input = Serial.read();  //Read user input and trigger appropriate function
    digitalWrite(EN_PIN_1, HIGH);
    digitalWrite(EN_PIN_2, HIGH);
    digitalWrite(EN_PIN_3, HIGH);
    digitalWrite(EN_PIN_4, HIGH);

    //Pembacaan kondisi
    // x_Position = analogRead(x_Pin);
    // y_Position = analogRead(y_Pin);

    // Serial.print("X: ");
    // Serial.println(x_Position);
    // Serial.print("Y: ");
    // Serial.println(y_Position);#

    if (user_input == '1') {
      Stop();
    } else if (user_input == '2') {
      Forward();
    } else if (user_input == '3') {
      Reverse();
    } else if (user_input == '4') {
      putarbalik();
    } else if (user_input == '5') {
      jalansampingkanan();
    } else if (user_input == '6') {
      jalansampingkiri();
    } else if (user_input == '7') {
      gerak360();
    } else if (user_input == '0') {
      gerakanparabola();
    }

    else if (user_input == '+') {
      IncreaseSpeed();
    } else if (user_input == '-') {
      DecreaseSpeed();
    } else {
      Serial.println("Invalid option entered.");
    }
  }
  delay(100);  //waktu tunda sebesar 100ms
}

void Stop() {
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
  motorGo(MOTOR_2, usMotor_Status, 0);
  motorGo(MOTOR_3, usMotor_Status, 0);
  motorGo(MOTOR_4, usMotor_Status, 0);
}

void Forward() {
  Serial.println("Forward");
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  motorGo(MOTOR_3, usMotor_Status, usSpeed);
  motorGo(MOTOR_4, usMotor_Status, usSpeed);
}

void Reverse() {
  Serial.println("Reverse");
  usMotor_Status = CCW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  motorGo(MOTOR_3, usMotor_Status, usSpeed);
  motorGo(MOTOR_4, usMotor_Status, usSpeed);
}
void jalansampingkanan() {
  Serial.println("kanan");
  usMotor_Status1 = CCW;
  usMotor_Status2 = CW;
  motorGo(MOTOR_1, usMotor_Status2, usSpeed);
  motorGo(MOTOR_2, usMotor_Status1, usSpeed);
  motorGo(MOTOR_3, usMotor_Status1, usSpeed);
  motorGo(MOTOR_4, usMotor_Status2, usSpeed);
}
void jalansampingkiri() {
  Serial.println("kiri");
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  motorGo(MOTOR_1, usMotor_Status2, usSpeed);
  motorGo(MOTOR_2, usMotor_Status1, usSpeed);
  motorGo(MOTOR_3, usMotor_Status1, usSpeed);
  motorGo(MOTOR_4, usMotor_Status2, usSpeed);
}
void gerak360() {
  Serial.println("");
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  motorGo(MOTOR_1, usMotor_Status1, usSpeed);
  motorGo(MOTOR_2, usMotor_Status2, usSpeed);
  motorGo(MOTOR_3, usMotor_Status1, usSpeed);
  motorGo(MOTOR_4, usMotor_Status2, usSpeed);
}
void serongkananatas() {
  Serial.println("serong kanan atas");
  usSpeed = usSpeed;
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  motorGo(MOTOR_1, usMotor_Status1, 150);
  motorGo(MOTOR_4, usMotor_Status1, 150);
}
void serongkananbawah() {
  Serial.println("serong kanan bawah");
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  motorGo(MOTOR_1, usMotor_Status2, 150);
  motorGo(MOTOR_4, usMotor_Status2, 150);
}
void serongkiriatas() {
  Serial.println("serong kiri atas");
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  motorGo(MOTOR_2, usMotor_Status1, 150);
  motorGo(MOTOR_3, usMotor_Status1, 150);
}
void serongkiribawah() {
  Serial.println("serong kiri bawah");
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  motorGo(MOTOR_2, usMotor_Status2, 150);
  motorGo(MOTOR_3, usMotor_Status2, 150);
}
void putarbalik() {
  Serial.println("");
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  motorGo(MOTOR_1, usMotor_Status1, usSpeed);
  motorGo(MOTOR_2, usMotor_Status2, usSpeed);
}
void gerakanparabola() {
  Serial.println("");
  usMotor_Status1 = CW;
  usMotor_Status2 = CCW;
  motorGo(MOTOR_1, usMotor_Status1, usSpeed);
  motorGo(MOTOR_3, usMotor_Status1, usSpeed);
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

  // motorGo(MOTOR_1, usMotor_Status1, usSpeed);
  // motorGo(MOTOR_2, usMotor_Status1, usSpeed);
  // motorGo(MOTOR_3, usMotor_Status1, usSpeed);
  // motorGo(MOTOR_4, usMotor_Status1, usSpeed);

  // motorGo(MOTOR_1, usMotor_Status2, usSpeed);
  // motorGo(MOTOR_2, usMotor_Status2, usSpeed);
  // motorGo(MOTOR_3, usMotor_Status2, usSpeed);
  // motorGo(MOTOR_4, usMotor_Status2, usSpeed);
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
      digitalWrite(MOTOR_A4_PIN, HIGH);
      digitalWrite(MOTOR_B4_PIN, LOW);
    } else if (direct == CCW) {
      digitalWrite(MOTOR_A4_PIN, LOW);
      digitalWrite(MOTOR_B4_PIN, HIGH);
    } else {
      digitalWrite(MOTOR_A4_PIN, LOW);
      digitalWrite(MOTOR_B4_PIN, LOW);
    }
    analogWrite(PWM_MOTOR_4, pwm);
  }
}
