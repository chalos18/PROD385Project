#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup_wifi() {
  if (WiFi.status() == WL_CONNECTED) return; // Already connected

  Serial.print("Connecting to WiFi ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection... ");
    if (client.connect("esp8266Client", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      client.publish("outTopic", "Hello from ESP8266 TLS!");
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // // Optional: skip certificate verification
  // espClient.setInsecure(); // Only for testing
}

void loop() {
  // Retry WiFi connection if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    setup_wifi();
  }

  // Retry MQTT connection only if WiFi is connected
  if (WiFi.status() == WL_CONNECTED && !client.connected()) {
    reconnect_mqtt();
  }

  client.loop();
}
