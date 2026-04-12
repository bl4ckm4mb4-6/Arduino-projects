#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <printf.h>
#include <stdint.h>

#define x A1
#define y A3

struct __attribute__((packed)) Dati{
  int32_t yApp;
  int32_t xApp;
  int32_t velocitaX;
  int32_t velocitaY;
};

Dati macchina;

RF24 radio(9, 10);
const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.setChannel(10);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  macchina.yApp= analogRead(y);
  macchina.xApp= analogRead(x);
  macchina.velocitaY = map(macchina.yApp, 508, 1023, 0, 254);
  macchina.velocitaX = map(macchina.xApp, 505, 1023, 0, 254);
  macchina.velocitaX= abs(macchina.velocitaX);
  macchina.velocitaY= abs(macchina.velocitaY);
  radio.write(&macchina, sizeof(macchina));

  delay(100);
}
