# TempTeddy

# Prototype 1

<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

# Link: https://wokwi.com/projects/432161273389620225

![image](https://github.com/user-attachments/assets/4a693a36-070b-4a63-824f-9966bf323f8e)

<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

# DHT11 Sensor
VCC → 5V
SDA → D2
NC → (leave unconnected)
GND → GND

<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

# Piezo Buzzer
BZ1:1 → D8
BZ1:2 → GND
Red LED
LED1:A → D9
LED1:C → GND

<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

# Push Button (4 pins)

BTN1:1.L → D7
BTN1:2.L → GND
BTN1:1.R → (no connection)
BTN1:2.R → (no connection)

<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

# OLED Display (SSD1306 I2C)

VCC → 5V
GND → GND
SDA → A4
SCL → A5


<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">


# Non-Simulator (At-School) Wiring:

# DHT11 Sensor
VCC → 5V
DATA → D2
NC → (leave unconnected)
GND → GND

# OLED Display

GND → GND
VCC → 5V
SCL → A5
SDA → A4

# Piezo Buzzer

Positive → D8
Negative → GND

# Red LED
Anode (Positive) → D9 (with 220Ω resistor in series)
Cathode (Negative) → GND

# Button

One leg → D7
Other leg → GND
(use INPUT_PULLUP in code)

<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">
