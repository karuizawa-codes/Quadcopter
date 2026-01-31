#include <Servo.h>

// Create motor objects
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

// ESC pulse width limits (microseconds)
const int throttleMin = 1000; // minimum
const int throttleMax = 2000; // maximum

void setup() {
  // Attach motors with min/max constraints
  motor1.attach(3, throttleMin, throttleMax);
  motor2.attach(5, throttleMin, throttleMax);
  motor3.attach(6, throttleMin, throttleMax);
  motor4.attach(9, throttleMin, throttleMax);

  // Initialize motors to minimum throttle
  motor1.writeMicroseconds(throttleMin);
  motor2.writeMicroseconds(throttleMin);
  motor3.writeMicroseconds(throttleMin);
  motor4.writeMicroseconds(throttleMin);

  delay(10000); // Give ESCs time to arm
}

void loop() {
  // ----- ALL MOTORS TOGETHER -----
  Serial.println("Ramping up all motors...");
  for(int t = throttleMin; t <= throttleMax; t += 20){
    motor1.writeMicroseconds(t);
    motor2.writeMicroseconds(t);
    motor3.writeMicroseconds(t);
    motor4.writeMicroseconds(t);
    delay(200);
  }

  delay(2000); // Hold max throttle

  Serial.println("Ramping down all motors...");
  for(int t = throttleMax; t >= throttleMin; t -= 20){
    motor1.writeMicroseconds(t);
    motor2.writeMicroseconds(t);
    motor3.writeMicroseconds(t);
    motor4.writeMicroseconds(t);
    delay(200);
  }

  delay(2000); // Wait before next loop

  // ----- OPTIONAL: INDIVIDUAL MOTOR TEST -----
  // Uncomment if you want to test motors one by one
  /*
  testSingleMotor(motor1, "Motor1");
  testSingleMotor(motor2, "Motor2");
  testSingleMotor(motor3, "Motor3");
  testSingleMotor(motor4, "Motor4");
  */
}

// Helper function to test one motor at a time
void testSingleMotor(Servo &motor, String name){
  Serial.println("Testing " + name);
  motor.writeMicroseconds(throttleMax);
  delay(2000);
  motor.writeMicroseconds(throttleMin);
  delay(1000);
}
