# SIT210 Task 3.3D – Wave Detector with MQTT

This project demonstrates a simple IoT system using an Arduino Nano 33 IoT, an ultrasonic distance sensor, and MQTT communication to detect hand waves and publish messages to the cloud.

---

## 💡 What It Does

- Detects a wave (hand movement) using the HC-SR04 ultrasonic sensor.
- Blinks an LED as feedback when a wave is detected.
- Publishes a message to an MQTT topic: `SIT210/wave`
- Subscribes to the same topic to receive and respond to messages like `"wave"` or `"pat"`

---

## 🧰 Hardware Used

- Arduino Nano 33 IoT  
- HC-SR04 Ultrasonic Sensor  
- LED (with 220Ω resistor)  
- Jumper wires  
- Breadboard

---

## ⚙️ Pin Connections

| Component        | Arduino Pin |
|------------------|-------------|
| HC-SR04 VCC      | VIN         |
| HC-SR04 GND      | GND         |
| HC-SR04 TRIG     | D2          |
| HC-SR04 ECHO     | D3          |
| LED Anode (+)    | D5 (via 220Ω resistor) |
| LED Cathode (–)  | GND         |

---

## 🌐 MQTT Setup

- **Broker**: `test.mosquitto.org`  
- **Port**: `1883`  
- **Topic**: `SIT210/wave`  
- **Client Tool**: [MQTT Explorer](https://mqtt-explorer.com/)

---

## 🧪 How to Test

1. Upload the Arduino sketch to your Nano 33 IoT.
2. Open the Serial Monitor to confirm WiFi and MQTT connection.
3. Open **MQTT Explorer** and subscribe to the topic `SIT210/wave`.
4. Hover your hand 10–25 cm above the sensor.
5. Watch the LED blink and message appear in MQTT Explorer.
6. (Optional) Publish `"wave"` or `"pat"` to `SIT210/wave` to make the LED blink from MQTT.

---

## 📦 Libraries Required

- `WiFiNINA`  
- `PubSubClient`

Install via Arduino Library Manager if not already available.

---

## 📸 Screenshots

*Include screenshots showing:*
- Hardware setup
- Serial Monitor output
- MQTT Explorer displaying a received message

---

## 🎥 Demo Video

*Link to your short demonstration video here:*  
`[Watch the Demo](https://yourlink.com)`

---

## 🧠 What I Learned

- How to integrate ultrasonic sensors with an Arduino Nano 33 IoT.
- How to publish and subscribe to MQTT topics using WiFi.
- How to visualize real-time data using MQTT Explorer.
- How two-way MQTT communication enables responsive IoT systems.

---

## 📝 Author

**Kimsreng C.**  
SIT210 – Embedded Systems Development  
Deakin University
