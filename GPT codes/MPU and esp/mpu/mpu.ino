#include <Wire.h>

#define MPU_ADDR 0x68

// Raw sensor values
int16_t AX, AY, AZ;
int16_t GX, GY, GZ;

// Angles
float roll = 0.0;
float pitch = 0.0;

// Accelerometer angles
float rollA, pitchA;

// Gyro rates
float GRollRate, GPitchRate;

// Timing
unsigned long lastTime = 0;
float dt;

// Complementary filter constant
float alpha = 0.98;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  lastTime = micros();
}

void loop() {
  // -------- TIME STEP --------
  unsigned long currentTime = micros();
  dt = (currentTime - lastTime) * 1e-6;
  lastTime = currentTime;

  // -------- READ MPU6050 --------
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  AX = Wire.read() << 8 | Wire.read();
  AY = Wire.read() << 8 | Wire.read();
  AZ = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read(); // temperature (ignore)
  GX = Wire.read() << 8 | Wire.read();
  GY = Wire.read() << 8 | Wire.read();
  GZ = Wire.read() << 8 | Wire.read();

  // -------- CONVERT RAW DATA --------
  float Ax = AX / 16384.0;
  float Ay = AY / 16384.0;
  float Az = AZ / 16384.0;

  GRollRate  = GX / 131.0;
  GPitchRate = GY / 131.0;

  // -------- AELEROMETER ANGLES --------
  rollA  = atan2(Ay, sqrt(Ax * Ax + Az * Az)) * 180 / PI;
  pitchA = atan2(Ax, sqrt(Ay * Ay + Az * Az)) * 180 / PI;

  // -------- G INTEGRATION --------
  rollG  += GRollRate * dt;
  pitchG += GPitchRate * dt;

  // -------- COMPLEMENTARY FILTER --------
  roll  = alpha * rollG  + (1 - alpha) * rollA;
  pitch = alpha * pitchG + (1 - alpha) * pitchA;

  // -------- OUTPUT --------
  Serial.print("Roll:");
  Serial.print(roll);
  Serial.print(",");
  Serial.print("Pitch:");
  Serial.println(pitch);

  delay(5); // ~200 Hz loop
}
