#include <avr/wdt.h>

void setup() {
  // Initialize serial communication for debugging (optional)
  Serial.begin(9600);

  // Enable the Watchdog Timer with a timeout of 2 seconds
  // You can choose a different timeout period as needed
  // WDTO_2S, WDTO_1S, WDTO_500MS, WDTO_250MS, WDTO_125MS, WDTO_15MS
  wdt_enable(WDTO_2S);

  // Additional setup code goes here
}

void loop() {
  // Your main loop code goes here
  // Ensure that your code executes in less than the Watchdog timeout period

  // Uncomment the following line to trigger a reset manually (for testing)
  // wdt_reset();

  // Print a message to indicate that the loop is running
  Serial.println("Loop is running...");

  // Simulate a delay to demonstrate Watchdog Timer reset
  delay(5000); // Simulate a 5-second delay (should trigger a reset)
}
