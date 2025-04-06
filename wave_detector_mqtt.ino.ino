#include <WiFiNINA.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "OPTUS_26D2A0N";
const char* password = "sarod24929tx";

// MQTT config
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic = "SIT210/wave";

// Pins
const int trigPin = 2;
const int echoPin = 3;
const int ledPin = 5;

// Globals
WiFiClient wifiClient;
PubSubClient client(wifiClient);
long duration;
int distance;
int consecutiveClose = 0;

// Connect to WiFi
void setup_wifi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected");
}

// Reconnect to MQTT
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    String clientId = "arduinoClient-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected.");
      client.subscribe(mqtt_topic); // For receiving messages
    } else {
      Serial.print(" failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 2s");
      delay(2000);
    }
  }
}

// MQTT message handler
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("📩 Message received on topic: ");
  Serial.println(topic);

  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Payload: ");
  Serial.println(message);

  if (message == "wave" || message == "pat") {
    Serial.println("🔁 Triggered by MQTT message!");
    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
    Serial.println("⚠️ No echo received");
    consecutiveClose = 0;
  } else {
    distance = duration * 0.034 / 2;
    Serial.print("📏 Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 5 && distance < 30) {
      consecutiveClose++;
    } else {
      consecutiveClose = 0;
    }

    if (consecutiveClose >= 2) {
      Serial.println("👋 Wave detected!");

      // Blink LED
      for (int i = 0; i < 3; i++) {
        digitalWrite(ledPin, HIGH);
        delay(200);
        digitalWrite(ledPin, LOW);
        delay(200);
      }

      // Send MQTT message
      client.publish(mqtt_topic, "Wave detected by kimsrengc!");

      delay(2000); // Cooldown
      consecutiveClose = 0;
    }
  }

  delay(500); // loop pacing
}
