#ifndef MY_LORA_H
#define MY_LORA_H

#include <SPI.h>
#include <LoRa.h> // https://github.com/sandeepmistry/arduino-LoRa
#include "debug.h"
#include "credentials.h"

void loraSetup(){

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(BAND)) {
    DEBUG_PRINTLN("Starting LoRa failed!");
    while (1);
  }
  //LoRa.onReceive(cbk);
  //  LoRa.receive();
  DEBUG_PRINTLN("init ok");
  delay(1500);
  
}


void loraLoop(){
  // nothing todo maybe check the connection
}

void loraSend(String s){
  // send packet
  while (LoRa.beginPacket() == 0) {
    DEBUG_PRINTLN("waiting for radio ... ");
    delay(100);
  }
  
  LoRa.print(s);
  LoRa.endPacket();
}


#endif // MY_LORA_H
