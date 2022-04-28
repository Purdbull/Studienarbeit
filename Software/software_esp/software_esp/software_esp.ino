#include "StateMashine.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "EEPROM.h"

#define REED_PIN 4

bool isDrivingForward = true;


//################################################
//##           Wifi and MQTT Stuff              ##
//################################################
const char* ssid = "........";
const char* password = "........";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


StateMashine* handler = new StateMashine();

void IRAM_ATTR ISR() {
  if (isDrivingForward) {
    byte pos = EEPROM.read(42);
    if (pos < 15) {
      pos++;
    }
    EEPROM.write(42, pos);
  }
  else {
    byte pos = EEPROM.read(42);
    if (pos != 0) {
      pos--;
    }
    EEPROM.write(42, pos);
  }
}

void setup() {
  Serial.begin(9600);
  //attachInterrupt(REED_PIN, ISR, RISING);
  EEPROM.write(42, B00000011); //Fake position 3 for testing
  pinMode(2, OUTPUT);

  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void clearSerialBuffer() {
  char c;
  while (Serial.available() > 0) {
    c = Serial.read();
  }
}

long mils = 0;

void loop() {
  
  handler->handle("3");
  client.loop();
  if (Serial.available() > 0) {
    handler->handle(Serial.read());
    clearSerialBuffer();
  }
  
}
