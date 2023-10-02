void setup() {
  rtc.begin();

  // Set the RTC time to match the lab time on the wall
  rtc.setHours(4);
  rtc.setMinutes(35);
  rtc.setSeconds(0);
  rtc.setDay(18);
  rtc.setMonth(9);
  rtc.setYear(2023);
}

void loop() {
  int hours = rtc.getHours();
  int minutes = rtc.getMinutes();
  int seconds = rtc.getSeconds();

  Serial.print("Time: ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
}

