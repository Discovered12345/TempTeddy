#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUZZER_PIN 8
#define LED_PIN 9
#define BUTTON_PIN 7

const float TEMP_THRESHOLD_C = 38.0;
bool displayOn = false;
bool lastButtonState = HIGH;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  mlx.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for (;;);
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
  float tempC = mlx.readObjectTempC();
  float tempF = mlx.readObjectTempF();
  if (isnan(tempC) || isnan(tempF)) {
    return;
  }

  if (tempC >= TEMP_THRESHOLD_C) {
    alert(tempC, tempF);
    displayOn = true;
  }

  bool currentButtonState = digitalRead(BUTTON_PIN);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    displayOn = !displayOn;
    if (!displayOn) display.clearDisplay();
  }
  lastButtonState = currentButtonState;

  if (displayOn) {
    showTemperature(tempC, tempF);
  }

  delay(100);
}

void alert(float celsius, float fahrenheit) {
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    tone(BUZZER_PIN, 800);
    delay(200);
  }
  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN, LOW);
  showTemperature(celsius, fahrenheit);
}

void showTemperature(float celsius, float fahrenheit) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Temp:");
  display.setCursor(0, 15);
  display.setTextSize(2);
  display.print(celsius, 1);
  display.print(" C");
  display.setCursor(0, 40);
  display.print(fahrenheit, 1);
  display.print(" F");
  display.display();
}
