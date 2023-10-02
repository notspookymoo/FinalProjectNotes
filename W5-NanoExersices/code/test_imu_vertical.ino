#include <Arduino_LSM6DS3.h>
void setup() {
  // Initialize the IMU
  if (!IMU.begin()) {
    while (1);
  }

  // Set the embedded LED as an output
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // Read accelerometer data
  float x, y, z;
  IMU.readAcceleration(x, y, z);

  // Check if the board is held vertically
  if (abs(x) < 0.1 && abs(y) < 0.1 && z > 9.0) {
    // If the board is held vertically, turn on the LED
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    // Otherwise, turn off the LED
    digitalWrite(LED_BUILTIN, LOW);
  }

}
