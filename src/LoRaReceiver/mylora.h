#ifndef MY_LORA_H
#define MY_LORA_H

#include <Arduino.h>
#include "debug.h"
#include <SPI.h>
#include <LoRa.h>

static int loraPacketSize = 0;

static void loraSetup(){
   
  DEBUG_PRINTLN("LoRa Receiver Callback");
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);  
  if (!LoRa.begin(BAND)) {
    DEBUG_PRINTLN("Starting LoRa failed!");
    while (1);
  }
  //LoRa.onReceive(cbk);
  LoRa.receive();
  DEBUG_PRINTLN("init ok");
}


static void loraLoop(){
  loraPacketSize = LoRa.parsePacket();
}




#endif // #ifndef MY_LORA_H
