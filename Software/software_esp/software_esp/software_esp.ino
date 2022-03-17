#include "StateMashine.h"
#include "EspMQTTClient.h"
#include "EEPROM.h"

#define REED_PIN 4

int eepromPositionAddr = 42;
bool isDrivingForward = true;

EspMQTTClient client(
  "WifiSSID",
  "WifiPassword",
  "192.168.1.100",  // MQTT Broker server ip
  "TestClient"      // Client name that uniquely identify your device
);

EspMQTTClient* clientPtr = &client;

StateMashine handler(clientPtr);

void IRAM_ATTR ISR() {
 if(isDrivingForward){
  byte pos = EEPROM.read(42);
  if(pos<15){pos++;}
  EEPROM.write(42, pos);
 }
 else {
  byte pos = EEPROM.read(42);
  if (pos!=0){pos--;}
  EEPROM.write(42, pos);
 }
}

void setup() {
  Serial.begin(9600);
  attachInterrupt(REED_PIN, ISR, RISING);
}



void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe("train/driveToPosition", [](const String & payload) {
    handler.handle(payload);
    if(payload.toInt() > EEPROM.read(42)){
      isDrivingForward = true;
    }
  });

  // Publish a message to "mytopic/test"
  client.publish("train/position", "This is a message"); // You can activate the retain flag by setting the third parameter to true
}

void clearSerialBuffer() {
  char c;
  while (Serial.available() > 0) {
    c = Serial.read();
  }
}


void loop() {
  client.loop();
  if (Serial.available() > 0) {
    handler.handle((byte)Serial.read());
    clearSerialBuffer();
  }
}
