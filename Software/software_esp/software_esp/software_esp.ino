#include "StateMashine.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "EEPROM.h"

#define REED_PIN 4


/* ##########################################
   ##               Globals                ##
   ##########################################
*/
bool isDrivingForward = true;


/* ##########################################
   ##          Wifi and MQTT Stuff         ##
   ##########################################
*/
const char* ssid = "Kimo-Lan";
const char* password = "DU!k0mmst_h13r-n1cht.r31n!";
const char* mqtt_server = "192.168.100.33";

WiFiClient espClient;
PubSubClient client(espClient);
StateMashine* handler = new StateMashine(&client);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  /*Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);*/

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }

  randomSeed(micros());

  //Serial.println("");
  //Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  /*Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();*/
  payload[length] = '\0';
  int msg = atoi((char*)payload);
  handler->handle(String(msg));
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("Train/driveToPosition");
    } else {
      //Serial.print("failed, rc=");
      //Serial.print(client.state());
      //Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/* ##########################################
   ##                ISR                   ##
   ##########################################
*/
/*void IRAM_ATTR ISR() {
    byte pos = EEPROM.read(0);
  if (isDrivingForward) {
    if (pos < 15) {
      pos++;
    }
  }
  else {
    if (pos != 0) {
      pos--;
    }
  }
    EEPROM.write(0, pos);
}*/

void setup() {
  Serial.begin(9600);
  //attachInterrupt(REED_PIN, ISR, RISING);
  //EEPROM.write(0, B00000011); //Fake position 3 for testing
  EEPROM.begin(128);
  pinMode(2, OUTPUT);


  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.subscribe("Train/driveToPosition");

}

void clearSerialBuffer() {
  char c;
  while (Serial.available() > 0) {
    c = Serial.read();
  }
}

void loop() {
    if (Serial.available() > 0) {
    handler->handle(Serial.read());
    clearSerialBuffer();
    }
  client.loop();
  if (!client.connected()) {
    reconnect();
  }
}
