#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

// OLED display config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Sensor
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Pins
#define BUZZER_PIN 8
#define LED_PIN 9
#define BUTTON_PIN 7

// Temperature threshold
const float TEMP_THRESHOLD_C = 38.0;

// Alarm control
bool alarmActive = false;
bool alarmCancelled = false;
unsigned long alarmStartTime = 0;
unsigned long lastBlinkTime = 0;
bool ledState = false;

void setup() {
  Serial.begin(9600);

  // Initialize devices
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!mlx.begin()) {
    while (1) {
      Serial.println("MLX90614 not found!");
      delay(2000);
    }
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    while (1) {
      Serial.println("OLED not found!");
      delay(2000);
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Temp Monitor Starting...");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // Read raw temps
  float tempC = mlx.readObjectTempC();
  float tempF = mlx.readObjectTempF();

  // Basic sanity check
  if (isnan(tempC) || tempC < -40 || tempC > 150) {
    showError("Sensor Error");
    delay(1000);
    return;
  }

  // Adjusted values
  float adjustedC = tempC + 5.0;
  float adjustedF = tempF + 10.0;

  // Start alarm if needed
  if (adjustedC > TEMP_THRESHOLD_C && !alarmActive && !alarmCancelled) {
    alarmActive = true;
    alarmStartTime = millis();
    lastBlinkTime = 0;
    ledState = false;
  }

  // Handle alarm
  if (alarmActive) {
    unsigned long currentMillis = millis();

    // Cancel if button pressed
    if (digitalRead(BUTTON_PIN) == LOW) {
      alarmCancelled = true;
      alarmActive = false;
      noTone(BUZZER_PIN);
      digitalWrite(LED_PIN, LOW);
    }

    // Flash and buzz
    if (currentMillis - lastBlinkTime >= 200) {
      lastBlinkTime = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      tone(BUZZER_PIN, ledState ? 1000 : 800);
    }

    // Stop alarm after 3 seconds
    if (currentMillis - alarmStartTime >= 3000) {
      alarmActive = false;
      noTone(BUZZER_PIN);
      digitalWrite(LED_PIN, LOW);
    }
  } else {
    // Just to be sure buzzer is off
    noTone(BUZZER_PIN);
    digitalWrite(LED_PIN, LOW);
  }

  // Display temperature
  showTemperature(adjustedC, adjustedF);
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
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print(msg);
  display.display();
}
