#include <Servo.h>
#include <ArduinoBLE.h>

Servo servo1;
Servo servo2;
BLEService ledService("180A"); // BLE LED Service
int i;

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("2A57", BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
//  while (!Serial);

  // set servo pin to output mode
  pinMode(LED_BUILTIN, OUTPUT);
  servo1.attach(D2);
  servo2.attach(D4);
  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("I DISTRUTTORI");
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
            servo1.write(180);
            servo2.write(30);
            break;
          case 01:
            servo1.write(150);
            servo2.write(60);
            break;
          case 02:
            servo1.write(120);
            servo2.write(90);
            break;
          case 03:
            servo1.write(90);
            servo2.write(120);
            break;
          case 04:
            servo1.write(60);
            servo2.write(150);
            break;
          case 05:
            servo1.write(30);
            servo2.write(180);
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