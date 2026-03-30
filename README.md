# sugoi-rc-lights-v1

# ESP32-S2 Mini RC-Controlled LED System

## 📖 Overview

This project uses an **ESP32-S2 Mini** to control two WS2812 LED strips based on input from an RC receiver.
It is designed for RC vehicles (e.g., cars, drones) where lighting effects can be triggered remotely via transmitter switches.

The system is built with **clear electrical separation** between:

* Microcontroller (logic)
* LED power supply
* RC receiver

---

## ⚙️ Hardware Setup

### 🔌 Microcontroller

* ESP32-S2 Mini

### 💡 LEDs

* 2x WS2812 LED strips
* 16 LEDs per strip
* Controlled independently

### 🎮 RC Receiver

* Standard PWM receiver
* Channels used:

  * CH3 → GPIO7 : Turn ON LEDs 1
  * CH4 → GPIO9 : Turn ON LEDs 2
  * CH5 → GPIO11 : Change Mode LEDs 1
  * CH6 → GPIO12 : Change Mode LEDs 2

---

## 🔧 Pin Configuration

| Function         | ESP32 Pin |
| ---------------- | --------- |
| LED Strip 1 Data | GPIO3     |
| LED Strip 2 Data | GPIO5     |
| RC Channel 3     | GPIO7     |
| RC Channel 4     | GPIO9     |
| RC Channel 5     | GPIO11    |
| RC Channel 6     | GPIO12    |

---

## ⚡ Power Architecture

The system uses **three isolated domains**:

### 1. ESP32 (Logic)

* Powered by RC Receiver
* Handles signal processing only

### 2. LED Power

* Powered by RC Receiver

### 3. RC Receiver

* Powered via BEC (from ESC)

> ⚠️ **Important:**
> All grounds must be connected together to ensure proper signal reference.

---

## 🎛️ LED Modes

The system supports **three lighting modes**:

### 1. 🔆 Regular ON

* All LEDs are turned on with a constant color
* Used for visibility or standard lighting

---

### 2. 🚗 Knight Rider Effect

* Classic moving light animation (left ↔ right)
* Smooth sweeping effect across the strip
* Speed can be adjusted in code

---

### 3. ⚡ Blink Mode

* All LEDs blink on/off at a fixed interval
* Useful for signaling or alerts

---

## 🎮 Control Logic

### 🔘 Power Control (CH3 & CH4)

* Channels **3 and 4** are used to **turn LEDs ON or OFF**
* Either channel can be mapped to a switch on the transmitter

Example:

| PWM Value | State |
| --------- | ----- |
| < 1300 µs | OFF   |
| ≥ 1300 µs | ON    |

---

### 🎚️ Mode Selection (CH5 & CH6)

* Channels **5 and 6** are used to **select LED modes**

Example mapping:

| PWM Value    | Mode         |
| ------------ | ------------ |
| < 1300 µs    | Regular ON   |
| 1300–1700 µs | Knight Rider |
| > 1700 µs    | Blink        |

---

## 🧠 Software Notes

* Designed for use with **FastLED**
* Non-blocking loops recommended for smooth animations
* Debounce RC input to avoid flickering between modes
* Ensure LEDs are forced OFF when power channels (CH3/CH4) indicate OFF

---

## 🚀 Possible Improvements

* Replace PWM with SBUS/iBUS for cleaner input
* Add brightness control via an extra RC channel
* Add more LED effects (rainbow, brake lights, turn signals)
* Use interrupts or RMT for more accurate signal reading

---

## ⚠️ Safety Notes

* Do NOT power LED strips from ESP32 directly
* Ensure correct voltage levels (3.3V vs 5V logic)
* Double-check polarity before powering

---

## 📦 Use Cases

* RC car lighting system
* FPV drone LED effects
* Custom embedded lighting projects

---

## 📄 License

Free to use and modify for personal projects.

---

## 🤝 Contributions

Feel free to extend with new effects, better input handling, or improved hardware designs.
