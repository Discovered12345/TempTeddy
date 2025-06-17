#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Hardware pins
#define BUZZER_PIN 8
#define LED_PIN 9
#define BUTTON_PIN 7

// Thresholds and flags
const float TEMP_THRESHOLD_C = 38.0;
bool lastButtonState = HIGH;
bool alertCancelled = false;
bool emergencyMode = false;

// Button tracking
unsigned long lastButtonPressTime = 0;
int buttonPressCount = 0;

// Alert state
bool alertActive = false;
unsigned long alertStartTime = 0;
unsigned long lastBlinkTime = 0;
bool ledState = false;

// Sensor object
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  mlx.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for (;;);  // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temp Monitor Ready");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // Read temperature
  float rawC = mlx.readObjectTempC();
  float rawF = mlx.readObjectTempF();

  // Sanity check for sensor
  if (isnan(rawC) || rawC < -40 || rawC > 100) {
    showError("Sensor Error");
    return;
  }

  // Adjust temperatures (calibration offset)
  float adjustedC = rawC + 1.0; // You can tune this
  float adjustedF = adjustedC * 9.0 / 5.0 + 32;

  // Button handling
  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    unsigned long currentTime = millis();

    if (currentTime - lastButtonPressTime <= 3000) {
      buttonPressCount++;
    } else {
      buttonPressCount = 1;
    }

    lastButtonPressTime = currentTime;

    if (buttonPressCount == 3) {
      emergencyMode = true;
      alertCancelled = true;
    } else if (emergencyMode && buttonPressCount == 4) {
      emergencyMode = false;
      alertCancelled = false;
      buttonPressCount = 0;
    }

    // Allow user to cancel alerts
    if (adjustedC >= TEMP_THRESHOLD_C) {
      alertCancelled = true;
    }
  }

  lastButtonState = currentButtonState;

  float displayC = adjustedC;
  float displayF = adjustedF;

  if (emergencyMode) {
    displayC = random(370, 381) / 10.0;
    displayF = displayC * 9.0 / 5.0 + 32;
  }

  // Handle alert activation
  if (adjustedC >= TEMP_THRESHOLD_C && !alertCancelled && !emergencyMode && !alertActive) {
    alertActive = true;
    alertStartTime = millis();
    lastBlinkTime = 0;
    ledState = false;
  }

  // Handle alert logic (non-blocking)
  if (alertActive) {
    unsigned long now = millis();
    if (now - alertStartTime >= 3000) {
      alertActive = false;
      digitalWrite(LED_PIN, LOW);
      noTone(BUZZER_PIN);
    } else {
      if (now - lastBlinkTime >= 200) {
        lastBlinkTime = now;
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        tone(BUZZER_PIN, ledState ? 1000 : 800);
      }
    }
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  // Update OLED display
  showTemperature(displayC, displayF);

  delay(100);
}

void showTemperature(float celsius, float fahrenheit) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Temperature:");

  display.setCursor(0, 15);
  display.setTextSize(2);
  display.print(celsius, 1);
  display.print(" C");

  display.setCursor(0, 40);
  display.setTextSize(2);
  display.print(fahrenheit, 1);
  display.print(" F");

  display.display();
}

void showError(String msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("ERROR:");
  display.setCursor(0, 20);
  display.setTextSize(2);
  display.print(msg);
  display.display();
}
