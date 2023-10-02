#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  while (!Serial); // Wait for Serial Monitor to open
  Serial.println("Initializing I2C devices...");
  mpu.initialize();
  
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1); // Stop here if the connection fails
  }
}

void loop() {
  // Read accelerometer and gyroscope data
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Calculate accelerometer angles
  float accelAngleX = atan2(ay, az) * 180.0 / PI;
  float accelAngleY = atan2(-ax, az) * 180.0 / PI;

  // Print data
  Serial.print("Accel X: "); Serial.print(ax); Serial.print(" | ");
  Serial.print("Accel Y: "); Serial.print(ay); Serial.print(" | ");
  Serial.print("Accel Z: "); Serial.print(az); Serial.print(" | ");
  Serial.print("Gyro X: "); Serial.print(gx); Serial.print(" | ");
  Serial.print("Gyro Y: "); Serial.print(gy); Serial.print(" | ");
  Serial.print("Gyro Z: "); Serial.print(gz); Serial.print(" | ");
  Serial.print("Accel Angle X: "); Serial.print(accelAngleX); Serial.print(" | ");
  Serial.print("Accel Angle Y: "); Serial.println(accelAngleY);
  
  delay(1000); // Adjust the delay according to your needs
}
