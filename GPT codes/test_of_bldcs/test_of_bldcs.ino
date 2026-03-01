#include <ESP32Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

/* ESC signal pins */
#define M1_PIN 18
#define M2_PIN 19
#define M3_PIN 21
#define M4_PIN 22

/* ESC PWM limits */
#define MIN_THROTTLE 1000
#define MAX_THROTTLE 2000
#define ARM_THROTTLE 1000

int throttle = 0;   // Base throttle
int roll = 0;
int pitch = 0;
int yaw = 0;

void setup() {
  Serial.begin(115200);

  motor1.setPeriodHertz(50);
  motor2.setPeriodHertz(50);
  motor3.setPeriodHertz(50);
  motor4.setPeriodHertz(50);

  motor1.attach(M1_PIN, MIN_THROTTLE, MAX_THROTTLE);
  motor2.attach(M2_PIN, MIN_THROTTLE, MAX_THROTTLE);
  motor3.attach(M3_PIN, MIN_THROTTLE, MAX_THROTTLE);
  motor4.attach(M4_PIN, MIN_THROTTLE, MAX_THROTTLE);

  armESCs();
}

void loop() {
  // Example: slowly increase throttle
  throttle = 1200;

  mixMotors(throttle, roll, pitch, yaw);

  delay(20); // 50Hz loop
}

/* Arm ESCs */
void armESCs() {
  motor1.writeMicroseconds(ARM_THROTTLE);
  motor2.writeMicroseconds(ARM_THROTTLE);
  motor3.writeMicroseconds(ARM_THROTTLE);
  motor4.writeMicroseconds(ARM_THROTTLE);

  Serial.println("Arming ESCs...");
  delay(10000);
  Serial.println("ESCs Armed");
}

/* Motor mixing */
void mixMotors(int t, int r, int p, int y) {
  int m1 = t + p + r - y; // Front Left
  int m2 = t + p - r + y; // Front Right
  int m3 = t - p - r - y; // Rear Right
  int m4 = t - p + r + y; // Rear Left

  m1 = constrain(m1, MIN_THROTTLE, MAX_THROTTLE);
  m2 = constrain(m2, MIN_THROTTLE, MAX_THROTTLE);
  m3 = constrain(m3, MIN_THROTTLE, MAX_THROTTLE);
  m4 = constrain(m4, MIN_THROTTLE, MAX_THROTTLE);

  motor1.writeMicroseconds(m1);
  motor2.writeMicroseconds(m2);
  motor3.writeMicroseconds(m3);
  motor4.writeMicroseconds(m4);
}