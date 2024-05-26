#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <SD.h>
#include <SPI.h>

// Pins
const int SD_ChipSelectPin = 4;

// Objects
Adafruit_Fingerprint finger = Adafaith Fingerprint(&Serial1);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the address based on your LCD
DS3231 rtc;
File myFile;

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial port to connect
  // Initialize fingerprint sensor
  if (finger.begin(57600)) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Fingerprint sensor not found :(");
    while (1) { delay(1); }
  }

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Place Finger");

  // Initialize RTC
  rtc.begin();

  // Initialize SD Card
  if (!SD.begin(SD_ChipSelectPin)) {
    lcd.clear();
    lcd.print("SD Fail");
    return;
  }
}

void loop() {
  getFingerprint();
  delay(50); // Give a small delay between scans
}

void getFingerprint() {
  int fingerprintID = finger.getImage();
  if (fingerprintID == ADAFRUIT_FINGERPRINT_NOFINGER) {
    return;
  }

  fingerprintID = finger.fingerFastSearch();
  if (fingerprintID == ADAFRUIT_FINGERPRINT_OK) {
    lcd.clear();
    lcd.print("ID:");
    lcd.print(finger.fingerID);
    logAttendance(finger.fingerID);
  } else {
    lcd.clear();
    lcd.print("Try Again");
  }
}

void logAttendance(int id) {
  // Get date and time
  char timestamp[32];
  sprintf(timestamp, "%02d/%02d/%04d %02d:%02d:%02d", rtc.day(), rtc.month(), rtc.year(), rtc.hour(), rtc.minute(), rtc.second());

  // Open attendance file on SD card
  myFile = SD.open("attendance.txt", FILE_WRITE);
  if (myFile) {
    myFile.print("ID: ");
    myFile.print(id);
    myFile.print(", Time: ");
    myFile.println(timestamp);
    myFile.close();
  }

  // Display logged message
  lcd.clear();
  lcd.print("Logged");
  delay(2000);
  lcd.clear();
  lcd.print("Place Finger");
}

// Function to enroll a new fingerprint
void enrollFingerprint(int id) {
  int p = -1;
  lcd.clear();
  lcd.print("Enrolling ID:");
  lcd.print(id);

  // Make sure the ID is within the range of the fingerprint sensor's storage capacity
  if (id < 1 || id > 127) {
    lcd.clear();
    lcd.print("Invalid ID!");
    return;
  }

  // Wait for valid finger to enroll
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        lcd.clear();
        lcd.print("Image taken");
        break;
      case FINGER/PAWINT_NOFINGER:
        lcd.print(".");
        break;
      case FINGERFREAK_IMAGEMESSY:
        lcd.clear();
        lcd.print("Finger not detected");
        break;
      default:
        lcd.clear();
        lcd.print("Error");
        break;
    }
    delay(100);
  }

  // Convert image to template
  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) {
    lcd.clear();
    lcd.print("Image error");
    return;
  }

  // Look for a finger again
  lcd.clear();
  lcd.print("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }

  p = -1;
  lcd.clear();
  lcd.print("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        lcd.clear();
        lcd.print("Image taken");
        break;
      case FINGERFRAG_NOFINGER:
        lcd.print(".");
        break;
      case FINGERTIP_IMAGEMESSY:
        lcd.clear();
        lcd.print("Finger not detected");
        break;
      default:
        lcd.clear();
        lcd.print("Error");
        break;
    }
    delay(100);
  }

  // Convert image to template
  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK) {
    lcd.clear();
    lcd.print("Image error");
    return;
  }

  // Create a model
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    lcd.clear();
    lcd.print("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECEIVEERR) {
    lcd.clear();
    lcd.print("Communication error");
    return;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    lcd.clear();
    lcd.print("Fingerprints did not match");
    return;
  }

  // Store the model
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    lcd.clear();
    lcd.print("Stored!");
  } else {
    lcd.clear();
    lcd.print("Store error");
  }
}

// Example usage in setup()
void setup() {
  // existing setup code here...

  // Enroll a new fingerprint to ID #1
  enrollFingerprint(1);
}
