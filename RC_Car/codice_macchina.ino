#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <printf.h>
#include <stdint.h>

RF24 radio(9, 10);
const byte address[6] = "00001";

int enA = 3;
int in1 = 2;
int in2 = 4;
int enB = 6;
int in3 = 7;
int in4 = 8;

struct __attribute__((packed)) Dati{
  int32_t yApp;
  int32_t xApp;
  int32_t velocitaX;
  int32_t velocitaY;
};

Dati macchina;

void setup() {
  radio.begin();
  radio.setChannel(10);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.openReadingPipe(0, address);
  radio.startListening();
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  if(radio.available()){
    radio.read(&macchina, sizeof(macchina));
    if(macchina.yApp<500){
      if(macchina.xApp<500){  //Gira Sx avanti
        giraSxAvanti(macchina.xApp, macchina.yApp, macchina.velocitaX, macchina.velocitaY);
      }
      else if(macchina.xApp>510){  //Gira Dx avanti
        giraDxAvanti(macchina.xApp, macchina.yApp, macchina.velocitaX, macchina.velocitaY);
      }
      else{  //avanti
        avanti(macchina.xApp, macchina.yApp, macchina.velocitaY);
      }
    }else if((macchina.yApp>500 && macchina.yApp<516) && macchina.xApp<500){  //Gira Sx da fermo
      giraSxFermo(macchina.xApp, macchina.yApp, macchina.velocitaX);
    }else if((macchina.yApp>500 && macchina.yApp<516) && macchina.xApp>510){  //Gira Dx da fermo
      giraDxFermo(macchina.xApp, macchina.yApp, macchina.velocitaX);
    }else if(macchina.yApp>516){
      if(macchina.xApp<500){  //Gira Sx indietro
        giraSxIndietro(macchina.xApp, macchina.yApp, macchina.velocitaX, macchina.velocitaY);
      }
      else if(macchina.xApp>510){  //Gira Dx indietro
        giraDxIndietro(macchina.xApp, macchina.yApp, macchina.velocitaX, macchina.velocitaY);
      }
      else{  //indietro
        indietro(macchina.xApp, macchina.yApp, macchina.velocitaY);
      }
    }
    else{  //stop
      stop();
    }
  }
  else{  //se non riceve dati
    stop();
  }
  
  delay(100);
}

void avanti(int x2, int y2, int velocitaY){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, velocitaY);
  analogWrite(enB, velocitaY);
}

void giraDxAvanti(int x2, int y2, int velocitaX, int velocitaY){
  if(y2>x2){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, velocitaY);
    analogWrite(enB, velocitaX);
  }else if(y2<x2){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, velocitaX);
    analogWrite(enB, velocitaY);
  }
  else{
    velocitaY/= 2;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, velocitaX);
    analogWrite(enB, velocitaY);
  }
}

void giraSxAvanti(int x2, int y2, int velocitaX, int velocitaY){
  if(y2>x2){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, velocitaX);
    analogWrite(enB, velocitaY);
  }else if(y2<x2){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, velocitaY);
    analogWrite(enB, velocitaX);
  }
  else{
    velocitaY/= 2;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, velocitaY);
    analogWrite(enB, velocitaX);
  }
}

void giraDxFermo(int x2, int y2, int velocitaX){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, velocitaX);
  analogWrite(enB, velocitaX);
}

void giraSxFermo(int x2, int y2, int velocitaX){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, velocitaX);
  analogWrite(enB, velocitaX);
}

void indietro(int x2, int y2, int velocitaY){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, velocitaY);
  analogWrite(enB, velocitaY);
}

void giraDxIndietro(int x2, int y2, int velocitaX, int velocitaY){
  if(y2>x2){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, velocitaY);
    analogWrite(enB, velocitaX);
  }else if(y2<x2){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, velocitaX);
    analogWrite(enB, velocitaY);
  }
  else{
    velocitaY/= 2;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, velocitaX);
    analogWrite(enB, velocitaY);
  }
}

void giraSxIndietro(int x2, int y2, int velocitaX, int velocitaY){
  if(y2>x2){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, velocitaX);
    analogWrite(enB, velocitaY);
  }else if(y2<x2){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, velocitaY);
    analogWrite(enB, velocitaX);
  }
  else{
    velocitaY/= 2;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, velocitaY);
    analogWrite(enB, velocitaX);
  }
}

void stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
