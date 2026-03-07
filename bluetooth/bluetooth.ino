#include <ArduinoBLE.h>

BLEService ledService("180A"); // BLE LED Service
int i;

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("2A57", BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
//  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT);
  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("Hasbulla");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characteristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");
}

void loop() {
  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);            // turn on the LED to indicate the connection

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control servo:
      if (switchCharacteristic.written()) {
        switch (switchCharacteristic.value()) {   // any value other than 0
          case 00:
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
            digitalWrite(LED_BUILTIN, LOW);
            delay(500);
             digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
            digitalWrite(LED_BUILTIN, LOW);
            delay(500);
            digitalWrite(LED_BUILTIN, HIGH);
            break;
          case 01:
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            break;
          case 02:
            digitalWrite(LED_BUILTIN, HIGH);
            delay(1000);
            digitalWrite(LED_BUILTIN, LOW);
            delay(1000);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(1000);
            digitalWrite(LED_BUILTIN, LOW);
            delay(1000);
            digitalWrite(LED_BUILTIN, HIGH);
            break;
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, LOW);         // when the central disconnects, turn off the LED
  }
}