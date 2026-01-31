#include <ESP32Servo.h>

Servo esc;

#define ESC_PIN 18   // GPIO pin connected to ESC signal

// Typical ESC PWM values (microseconds)
#define ESC_MIN 1000   // minimum throttle
#define ESC_ARM 1000
#define ESC_TEST 1100  // very low speed test
#define ESC_STOP 1000

void setup() {
  Serial.begin(115200);

  esc.setPeriodHertz(50);      // 50Hz for ESC
  esc.attach(ESC_PIN, 1000, 2000);

  Serial.println("Arming ESC...");
  esc.writeMicroseconds(ESC_ARM);
  delay(10000);   // wait for ESC arming beeps

  Serial.println("ESC Armed");
}

void loop() {
  Serial.println("Spinning motor slowly...");
  esc.writeMicroseconds(ESC_TEST);
  delay(4000);

  Serial.println("Stopping motor...");
  esc.writeMicroseconds(ESC_STOP);
  delay(5000);
}
