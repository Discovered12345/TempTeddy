# TempTeddy

# Website: tempteddy.xyz

# Prototype 1

<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

# Link: https://wokwi.com/projects/432161273389620225

![image](https://github.com/user-attachments/assets/4a693a36-070b-4a63-824f-9966bf323f8e)


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


# Prototype 2

| Component        | Pin Label on Component | Connect to Arduino Pin |
| ---------------- | ---------------------- | ---------------------- |
| **MLX90614**     | VCC                    | 5V                     |
|                  | GND                    | GND                    |
|                  | SDA                    | A4                     |
|                  | SCL                    | A5                     |
| **OLED Display** | VCC                    | 5V                     |
|                  | GND                    | GND                    |
|                  | SDA                    | A4                     |
|                  | SCL                    | A5                     |
| **Piezo Buzzer** | +                      | Pin 8                  |
|                  | -                      | GND                    |
| **LED**          | Anode (+)              | Pin 9                  |
|                  | Cathode (–)            | GND (via resistor)     |
| **Button**       | One pin                | Pin 7                  |
|                  | Other pin              | GND                    |


<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">
