<div align="right">
  <a href="README.md"><img src="https://img.shields.io/badge/Dil-T%C3%BCrk%C3%A7e-red.svg?style=for-the-badge"></a>
  <a href="README_EN.md"><img src="https://img.shields.io/badge/Language-English-blue.svg?style=for-the-badge"></a>
</div>

# CarDIY Project

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)
[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![DIY](https://img.shields.io/badge/DIY-Robotics-red?style=for-the-badge)](https://www.instructables.com/)

## 📋 Contents
- [🔍 About the Project](#about-the-project)
- [🛠️ Hardware Requirements](#hardware-requirements)
- [🔌 Pin Connections](#pin-connections)
- [🚗 Control Functions](#control-functions)
- [📊 Parking Sensor System](#parking-sensor-system)
- [💡 LED Warning System](#led-warning-system)
- [🧪 Testing](#testing)
- [❓ Troubleshooting](#troubleshooting)
- [🚀 Development Suggestions](#development-suggestions)
- [🔄 Updates](#updates)
- [📄 License](#license)
- [✨ Conclusion](#conclusion)
- [📝 Note](#note)

## 🔍 About the Project
CarDIY is a DIY (Do It Yourself) robot car project that controls DC motors using an L293D motor driver module with Arduino. This project creates a parking sensor system using ultrasonic sensors and LEDs, allowing you to practice basic robotics and electronics concepts.

## 🛠️ Hardware Requirements
- Arduino UNO/Nano
- L293D Motor Driver IC or Motor Driver Shield
- 2 DC Motors
- Car chassis
- Power supply (battery pack, 6-12V)
- Jumper wires
- Breadboard (optional)

## 🔌 Pin Connections
| Arduino Pin | Connection    |
|-------------|---------------|
| D3 (PWM)    | EnA (Motor A Speed Control) |
| D11 (PWM)   | EnB (Motor B Speed Control) |
| D2          | In1 (Motor A Direction Control 1) |
| D4          | In2 (Motor A Direction Control 2) |
| D12         | In3 (Motor B Direction Control 1) |
| D10         | In4 (Motor B Direction Control 2) |
| D13         | Headlight (Front Lights) |
| D8          | Brake Light (Rear Lights) |
| D5          | Red LED |
| D6          | Yellow LED |
| D7          | Green LED |
| A0          | Ultrasonic Sensor Trig Pin |
| A1          | Ultrasonic Sensor Echo Pin |

## 🚗 Control Functions

The control functions in this project are:

### 🔄 Movement Functions
- `ileri()`: Moves the car forward (both motors forward)
- `geri()`: Moves the car backward (both motors backward)
- `dur()`: Stops the car (both motors stop)
- `Hafifsag()`: Slight right turn (right motor stops, left motor continues)
- `Tamsag()`: Full right turn (left motor forward, right motor backward)
- `Hafifsol()`: Slight left turn (left motor stops, right motor continues)
- `Tamsol()`: Full left turn (right motor forward, left motor backward)

### 💡 Light Control Functions
- `FarYak()`: Turns on the headlights
- `FarSon()`: Turns off the headlights
- `StopYak()`: Turns on the brake lights
- `StopSon()`: Turns off the brake lights

## 📊 Parking Sensor System

One of the most important features of this project is the parking sensor system created using an ultrasonic sensor. This system works as follows:

### 📏 Distance Measurement
The `mesafeOlc()` function measures the distance to an obstacle in front using the HC-SR04 ultrasonic sensor:

1. A 10-microsecond pulse is sent from the Trig pin
2. Measures the echo received from the Echo pin
3. Calculates the distance using the speed of sound (in cm)

### 🅿️ Parking Assistant
The `parkSensoru()` function adjusts the car's speed and illuminates LEDs appropriately according to the measured distance:

- **< 10 cm**: Dangerous proximity - Red LED lights up, car stops, brake lights turn on
- **10-20 cm**: Close distance - Yellow LED lights up, car slows down (speed: 100/255)
- **20-30 cm**: Medium distance - Green LED lights up, car moves at medium speed (speed: 150/255)
- **> 30 cm**: Safe distance - LEDs turn off, car moves at full speed (speed: 255/255)

## 💡 LED Warning System

Three different colored LEDs are used as a visual warning component of the parking sensor system:

- **🔴 Red LED (D5)**: Very close distance (< 10 cm) - Danger warning
- **🟡 Yellow LED (D6)**: Close distance (10-20 cm) - Caution warning
- **🟢 Green LED (D7)**: Safe distance (20-30 cm) - Safe to proceed

### 🎛️ LED Control Functions
- `ledleriSondur()`: Turns off all LEDs
- `kirmiziYak()`: Turns on only the red LED
- `sariYak()`: Turns on only the yellow LED
- `yesilYak()`: Turns on only the green LED

This system provides visual feedback to the driver to adjust approaching speed, similar to parking sensors in real cars.

## 🧪 Testing

Follow these steps to properly test your project:

### 🔄 Motor Test
- Uncomment the sections in the `loop()` function
- Connect the Arduino to your computer and upload the code
- Observe that the motors move forward, backward, and stop in sequence

### 📏 Sensor Test
- Slowly move your hand towards the ultrasonic sensor
- Open the serial monitor (9600 baud) and monitor the distance values
- Check if the LEDs light up correctly according to the distance

### 💡 Light Test
- Test the `FarYak()`, `FarSon()`, `StopYak()`, and `StopSon()` functions in the `loop()`
- Check if the lights turn on and off as expected

### 🔄 Turn Test
- Test the `Hafifsag()`, `Tamsag()`, `Hafifsol()`, and `Tamsol()` functions
- Verify that the car turns in the correct direction

## ❓ Troubleshooting

Common problems you might encounter in your project and their solutions:

| 🔧 Problem | 🔍 Possible Cause | ✅ Solution |
|-----------|-----------------|---------|
| 🚫 Motors not working | Connection error | Check pin connections |
| | Insufficient power | Check battery voltage (should be 6-12V) |
| | L293D failure | Replace motor driver IC |
| 📏 Ultrasonic sensor giving incorrect measurements | Connection error | Check Echo and Trig pin connections |
| | Sensor failure | Replace the sensor |
| | Noisy environment | Remove obstacles in front of the sensor |
| 💡 LEDs not lighting up | Connection error | Check LED connections and polarity |
| | Burnt LED | Replace LEDs |
| 🔄 Arduino not responding | Code error | Reload the code |
| | Hardware failure | Reset or replace Arduino |

## 🚀 Development Suggestions

Some suggestions to further enhance your project:

### 📱 Remote Control
- Add HC-05/HC-06 Bluetooth module for smartphone control
- Develop a custom mobile application

### 🔊 Audio Alert
- Add a buzzer for audio feedback
- Increasing frequency or rate of beeps as distance decreases

### 🧠 Smart Navigation
- Automatic route determination to avoid obstacles
- Use multiple ultrasonic sensors for 360° detection

### ⚡ Speed Control
- More precise adjustment of PWM values
- Gradual acceleration and deceleration functions

### 💾 Data Processing
- Save distance data with SD card module
- Computer interface for analyzing sensor data

## 🔄 Updates

The latest updates, changes, and fixes for the project can be found on the GitHub releases page. Detailed descriptions and new features are listed for each version.

### Latest Version (v1.0.0)
- First official release
- Added basic motor control functions
- Added ultrasonic sensor support
- Completed LED warning system

### Previous Versions
For complete details of previous versions and change history, please visit the [GitHub Releases](https://github.com/username/CarDIY/releases) page.

## 📄 License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## ✨ Conclusion
Thank you for following us.
And dear professor: We have completed this project with Çağdaş Özdemir.
See you soon 👋🚀

## 📝 Note
**This project is for educational purposes and does not meet safety standards for real vehicle systems. It should be used for hobby and learning purposes only.**
