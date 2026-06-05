#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define POT_PIN      34
#define BUTTON_PIN   27

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Screen Management
int currentScreen = 0;
int lastScreen = -1;

unsigned long screenTimer = 0;
const unsigned long SCREEN_INTERVAL = 3000;

// Fault Handling
bool faultDetected = false;
String faultType = "NONE";
String lastFault = "";

// Voltage
float voltage = 0.0;

// Thresholds
const float UNDER_VOLTAGE = 1.0;
const float OVER_VOLTAGE  = 2.8;

// -----------------------------

float readVoltage() {
  int adc = analogRead(POT_PIN);
  return (adc / 4095.0) * 3.3;
}

// -----------------------------

void showBatteryScreen() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("BATTERY DATA");

  lcd.setCursor(0, 1);
  lcd.print("V:");
  lcd.print(voltage, 2);
  lcd.print("V");
}

// -----------------------------

void showAnalyticsScreen() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("ANALYTICS");

  lcd.setCursor(0, 1);

  if (voltage > 2.0)
    lcd.print("HEALTH: GOOD");

  else if (voltage > 1.0)
    lcd.print("HEALTH: FAIR");

  else
    lcd.print("HEALTH: POOR");
}

// -----------------------------

void showProtectionScreen() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("PROTECTION");

  lcd.setCursor(0, 1);

  if (faultDetected)
    lcd.print("STATUS: FAULT");
  else
    lcd.print("STATUS: SAFE ");
}

// -----------------------------

void showDiagnosticScreen() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("DIAGNOSTICS");

  lcd.setCursor(0, 1);

  if (faultDetected)
    lcd.print(faultType);
  else
    lcd.print("FAULT: NONE");
}

// -----------------------------

void showFaultScreen() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("***WARNING***");

  lcd.setCursor(0, 1);
  lcd.print(faultType);
}

// -----------------------------

void setup() {

  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Intelligent HMI");

  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  delay(1500);

  lcd.clear();
}

// -----------------------------

void loop() {

  voltage = readVoltage();

  // Fault Detection

  if (voltage < UNDER_VOLTAGE) {

    faultDetected = true;
    faultType = "LOW VOLTAGE";
  }

  else if (voltage > OVER_VOLTAGE) {

    faultDetected = true;
    faultType = "OVER VOLTAGE";
  }

  else if (digitalRead(BUTTON_PIN) == LOW) {

    faultDetected = true;
    faultType = "SENSOR ERROR";
  }

  else {

    faultDetected = false;
    faultType = "NONE";
  }

  // Screen Rotation

  if (!faultDetected) {

    if (millis() - screenTimer >= SCREEN_INTERVAL) {

      screenTimer = millis();

      currentScreen++;

      if (currentScreen > 3)
        currentScreen = 0;
    }
  }

  // Fault Priority Override

  if (faultDetected) {

    if (lastFault != faultType) {

      showFaultScreen();

      lastFault = faultType;
      lastScreen = -1;
    }
  }

  else {

    lastFault = "";

    if (currentScreen != lastScreen) {

      lastScreen = currentScreen;

      switch (currentScreen) {

        case 0:
          showBatteryScreen();
          break;

        case 1:
          showAnalyticsScreen();
          break;

        case 2:
          showProtectionScreen();
          break;

        case 3:
          showDiagnosticScreen();
          break;
      }
    }
  }
}