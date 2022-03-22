#include "StateMashine.h"
//00#include "EspMQTTClient.h"
#include "EEPROM.h"

#define REED_PIN 4

bool isDrivingForward = true;

/*EspMQTTClient client(
  "WifiSSID",
  "WifiPassword",
  "192.168.1.100",  // MQTT Broker server ip
  "TestClient"      // Client name that uniquely identify your device
);*/

//EspMQTTClient* clientPtr = 0; //&client;
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
}



/*void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe("train/driveToPosition", [](const String & payload) {
    handler->handle(payload);
    isDrivingForward = (payload.toInt() > EEPROM.read(42));
  });

  // Publish a message to "mytopic/test"
  client.publish("train/position", "This is a message"); // You can activate the retain flag by setting the third parameter to true
}*/

void clearSerialBuffer() {
  char c;
  while (Serial.available() > 0) {
    c = Serial.read();
  }
}

long mils = 0;
void loop() {
  
  handler->handle("3");
  mils = millis();
  while(millis()-mils<20000){
  //client.loop(); testing
  if (Serial.available() > 0) {
    handler->handle(Serial.read());
    clearSerialBuffer();
  }
  }
}
