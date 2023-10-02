#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_PN532.h>
#include <Notes.h>
#include <Keypad.h>
#include <SPI.h>
#include <String.h>
#include <Wire.h>
#include <user.h>

#define TFT_CS   1
#define SD_CS    2
#define TFT_RST  3
#define TFT_DC   4
#define MOSI     5
#define MISO     6
#define SCK      7
#define PN532_CS 11
#define C147s    12
#define C2580    13
#define C369p    14
#define BUZZER   15
#define R123     16
#define R456     17
#define R789     22
#define Rs0p     23
#define SOLENOID 28

#define STARTx 0xA1
#define SCANxx 0xC1
#define SYNCxx 0xC2
#define NAMExx 0xB0
#define ACTIVE 0xB1
#define PINxxx 0xB2
#define TAGxxx 0xB3
#define ENDxxx 0xA2

int tone_ = 0;
int beat = 0;
long duration = 0;

//typedef struct user {
//  String Name;
//  bool Active;
//  int PIN;
//  uint8_t Tag[7];
//} User;
//
//User USERLIST[10] = {
//  {"Anubis",  true, 1235, { 81,  21,  11,  11,   0,   0,   0}},
//  {"Apophis", true, 2468, { 66,  68,  66, 242,   0,   0,   0}},
//  {"Ba'al",   true, 3692, { 33, 112,  51,  15,   0,   0,   0}},
//  {"Ra",      true, 4826, {188, 202, 170, 190,   0,   0,   0}},
//  {"Vandal",  true,  420, { 15, 178, 147, 195,   0,   0,   0}},
//  {"User6",  false, 1234, {  0,   0,   0,   0,   0,   0,   0}},
//  {"User7",  false, 1234, {  0,   0,   0,   0,   0,   0,   0}},
//  {"User8",  false, 1234, {  0,   0,   0,   0,   0,   0,   0}},
//  {"User9",  false, 1234, {  0,   0,   0,   0,   0,   0,   0}},
//  {"User10", false, 1234, {  0,   0,   0,   0,   0,   0,   0}},
//};

int USERCOUNT = sizeof(USERLIST) / sizeof(User);

Adafruit_PN532 pn532(SCK, MISO, MOSI, PN532_CS);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, MOSI, SCK, TFT_RST, MISO);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {R123, R456, R789, Rs0p}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {C147s, C2580, C369p}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned char cmdBuffer[24];
bool cmdRdy = false;
int retVal = 0;

/************************************************************/
//BEGIN: MAIN()
void setup() {
  Serial.begin(9600);
  pinMode(SOLENOID, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pn532.begin();
  uint32_t versiondata = pn532.getFirmwareVersion();
  if (! versiondata) {
    //Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  //Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  //Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  //Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  pn532.SAMConfig();
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setRotation(3);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2);
  tft.println("DARK Lock v1.2");
  tft.setCursor(0, 100);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Swipe or Type");
}

void loop() {
  tft.fillRect(0, 125, 360, 100, ILI9341_BLACK);
  tft.setCursor(0, 125);
  if (cmdRdy == true) {
    cmdRdy = false;
    switch (cmdBuffer[1]) {
      case SCANxx:
        scan();
        break;
    }
  }
  superWireless();
  superKeypad();
} //END: MAIN()
/************************************************************/
//BEGIN: KEYPAD
void superKeypad() {
  int M_ATeam[] = { n_F5,  n_C5,  n_F5, n_B4f, n_C5, n_F4, n_A4, n_C5, n_F5, n_C5, n_G5, n_F5,
                    n_E5f, n_D5, n_D5f, n_B4f, n_C5
                  };
  int B_ATeam[] = { 16, 8, 40, 8, 16, 24, 4, 4, 8, 8, 8, 40, 8, 4, 4, 4, 8, 32 };
  int M_Twinkle[] = { n_C4, n_C4, n_G4, n_G4, n_A4, n_A4, n_G4, n_F4, n_F4, n_E4, n_E4, n_D4, n_D4, n_C4,
                      n_G4, n_G4, n_F4, n_F4, n_E4, n_E4, n_D4
                    };
  int B_Twinkle[] = { 16, 16, 16, 16, 16, 16, 32, 16, 16, 16, 16, 16, 16, 24 };

  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2);
  //tft.print("Enter PIN: ");
  String input = "";
  char key;
  int freedom = 0;
  while (key != '#') {
    key = keypad.getKey();
    if (key != NO_KEY) {
      if (key != '#')
        tft.print("*");
      input += key;
    }
    if (input == "") //If user hasn't typed anything ever for a while, break free
      freedom++;
    //Serial.println(freedom); //DIAG
    if (freedom > 50 && input == "") //If user hasn't typed anything ever for a while, break free
      break;
  }
  if (input == "*28326#") {
    playTrack(M_ATeam, B_ATeam, sizeof(M_ATeam) / sizeof(int));
    key = 'a';
  }
  if (key == '#') {
    tft.println("");
    unlock(authPIN(input));
  }
}

bool authPIN(String u) {
  bool match = false;
  u[u.length() - 1] = '\0';
  //Serial.print(" u = " + u); //DIAG
  //Serial.print(" PIN = " + p); //DIAG
  int uInt = u.toInt();
  for (int8_t i = 0 ; i < USERCOUNT ; i++) {
    if (USERLIST[i].PIN == uInt) {
      match = true;
      tft.setTextColor(ILI9341_YELLOW);  tft.setTextSize(2);
      tft.println(USERLIST[i].Name);
    }
  }
  if (match == false) {
    tft.setTextColor(ILI9341_MAGENTA);  tft.setTextSize(2);
    tft.println("UNRECOGNIZED");
  }
  return match;
} //END: KEYPAD
/************************************************************/
//BEGIN: SOLENOID
void unlock(bool x) {
  int M_Denied[] = { n_C3, n_C3 };
  int B_Denied[] = { 8, 8 };
  int M_Granted[] = { n_A5, n_C6 };
  int B_Granted[] = { 8, 8 };

  if (x == true) {
    playTrack(M_Granted, B_Granted, sizeof(B_Granted) / sizeof(int));
    tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(3);
    tft.print("ACCESS GRANTED");
    digitalWrite(SOLENOID, HIGH);
    delay(3000);
    digitalWrite(SOLENOID, LOW);
  }
  else {
    playTrack(M_Denied, B_Denied, sizeof(B_Denied) / sizeof(int));
    tft.setTextColor(ILI9341_RED);  tft.setTextSize(3);
    tft.print("ACCESS DENIED");
    delay(3000);
  }
}
//END: SOLENOID
/************************************************************/
//BEGIN: PN532
void superWireless() {
  int M_Scanned[] = { n_C5, n_B4, n_G4 };
  int B_Scanned[] = { 8, 8, 8 };

  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  //tft.println("Scanning...");
  success = pn532.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 100);

  if (success) {
    playTrack(M_Scanned, B_Scanned, sizeof(B_Scanned) / sizeof(int));
    tft.setTextColor(ILI9341_CYAN);  tft.setTextSize(2);
    tft.print("SCANNED ");
    delay(2000);
    for (int i = 0; i < 4; i++) {
      Serial.print(uid[i]);
      Serial.print(" ");
    }
    Serial.println("");
    unlock(authUID(uid, uidLength));
    delay(2000);
  }
}

bool authUID(uint8_t UID[], uint8_t UIDL) {
  bool match = false;
  int8_t j = 0;
  for (int8_t i = 0 ; i < USERCOUNT ; i++) {
    if (USERLIST[i].Tag[j] == UID[j]) {
      match = true;
      i--;
      if (j == UIDL - 1) {
        tft.setTextColor(ILI9341_YELLOW);  tft.setTextSize(2);
        tft.println(USERLIST[i + 1].Name);
        break;
      }
      else {
        j++;
        continue;
      }
    }
    else {
      match = false;
      j = 0;
      if (i == USERCOUNT - 1) {
        tft.setTextColor(ILI9341_MAGENTA);  tft.setTextSize(2);
        tft.println("UNRECOGNIZED");
      }
    }
  }
  return match;
}
//END: PN532
/************************************************************/
//START: BUZZER
void playTrack(int M[], int B[], int MAX_COUNT) {
  long tempo = 20000;
  int pause = 1000;
  for (int i = 0; i < MAX_COUNT; i++) {
    tone_ = M[i];
    beat = B[i];
    duration = beat * tempo; // Set up timing
    playTone();
    // A pause between notes...
    delayMicroseconds(pause);
  }
}

void playTone() {
  long elapsed_time = 0;
  int rest_count = 100;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(BUZZER, HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(BUZZER, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);
    }
  }
}
//END: BUZZER
/************************************************************/

void serialEvent() {
  unsigned char nextByte = ' ';
  int i;
  if (Serial.available()) {
    nextByte = (unsigned char)Serial.read();
  }
  if (nextByte == STARTx) {
    //Serial.println("Received start packet");
    //  Serial.write(END);
    i = 0;
    cmdBuffer[i++] = nextByte;
    do {
      if (Serial.available()) {
        nextByte = (unsigned char)Serial.read();
        cmdBuffer[i++] = nextByte;
        //Serial.println("Received: ");
        // Serial.write(nextByte);
         //Serial.write(END);
      }
    } while (nextByte != ENDxxx );
    //  Serial.println("Received end packet");
    cmdRdy = true;
  }
}

void scan() {
  int M_Scanned[] = { n_C6, n_C6, n_C6 };
  int B_Scanned[] = { 8, 8, 8 };

  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Scanning...");
  success = pn532.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    playTrack(M_Scanned, B_Scanned, sizeof(B_Scanned) / sizeof(int));
    tft.setTextColor(ILI9341_CYAN);  tft.setTextSize(2);
    tft.print("SCANNED ");
    for (int i = 0; i < uidLength; i++) {
      tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
      tft.print(uid[i]);
      tft.print(" ");
      Serial.write(uid[i]);
    }
    Serial.write(ENDxxx);
    delay(2000);
  }
}
