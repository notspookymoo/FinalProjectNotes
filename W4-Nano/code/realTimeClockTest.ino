#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC module");
    while (1);
  }

  // Uncomment the following line to set the RTC to the date and time you desire.
  // rtc.adjust(DateTime(YYYY, MM, DD, HH, MM, SS));

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time...");
    // If the RTC lost power, set the time here.
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(1000);
}
