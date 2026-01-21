#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#define PIR_PIN D2   // PIR sensor
#define LED_PIN LED_BUILTIN   // Built-in LED (active LOW)


// WiFi credentials
const char* ssid = "";
const char* password = "";

// HiveMQ Cloud credentials
const char* mqtt_server = "3585e2dbfcd948449aec8ccf1eb8912d.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "";  // HiveMQ Cloud username
const char* mqtt_pass = "";  // HiveMQ Cloud password

WiFiClientSecure espClient;
PubSubClient client(espClient);

// State flags
bool motionDetected = false;
bool ackReceived = false;

// ================= MQTT CALLBACK =================
void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0'; // Null-terminate payload
  String message = String((char*)payload);

  Serial.print("MQTT [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  if (String(topic) == "home/presence/ack" && message == "OK") {
    ackReceived = true;
    digitalWrite(LED_PIN, LOW); // LED ON
    Serial.println("ACK received → LED ON");
  }
}
// ================= WIFI =================
void setup_wifi() {
  if (WiFi.status() == WL_CONNECTED) return; // Already connected

  Serial.print("Connecting to WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ================= MQTT RECONNECT =================
void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("esp8266Client", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      // client.publish("outTopic", "Hello from ESP8266 TLS!");
      // client.subscribe("inTopic");
      Serial.println("connected");
      client.subscribe("home/presence/ack");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Setup pins and LED
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // LED off

  setup_wifi();

  // Skip certificate verification
  espClient.setInsecure(); // Required for HiveMQ TLS
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}


// ================= LOOP =================
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_PIN, HIGH);
    setup_wifi();
  }
  if (!client.connected()) {
    digitalWrite(LED_PIN, HIGH);
    reconnect_mqtt();
  }

  client.loop();

  // PIR logic
  int pirState = digitalRead(PIR_PIN);

  // Motion detected
  if (pirState == HIGH && !motionDetected) {
    motionDetected = true;
    ackReceived = false;

    Serial.println("Motion detected → publishing");
    client.publish("home/presence", "I am home!", true);
  }

  // ACK controls LED
  if (motionDetected && ackReceived) {
    digitalWrite(LED_PIN, LOW);  // LED ON
  }

  // Motion ended
  if (pirState == LOW && motionDetected) {
    motionDetected = false;
    ackReceived = false;

    digitalWrite(LED_PIN, HIGH); // LED OFF
    Serial.println("Motion ended → LED OFF");
  }

  delay(50);
}