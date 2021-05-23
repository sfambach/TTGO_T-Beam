/**
   Lora sender, receives gps location and sends the information to the receiver.

   LIBS
   https://github.com/mikalhart/TinyGPSPlus
   https://github.com/sandeepmistry/arduino-LoRa
   https://github.com/ThingPulse/esp8266-oled-ssd1306

   Created by S. Fambach visit http://www.fambach.net if you want.
   This sketch was created with help of the examples from the libraries. 
*/

#include <Arduino.h>
#include <Wire.h>
#include "credentials.h"
#include "debug.h"
#include "gps.h"
#include "display.h"
#include "mylora.h"

int packageCount = 0;

void setup() {

  // displaySetup();
  pinMode(25, OUTPUT);

  DEBUG_INIT;

  // setup display
  displaySetup();

  // init gps
  gpsSetup();

  // lora setup
  loraSetup();

}

void loop() {

  displayLoop();
  gpsLoop();
  loraLoop();
  gpsDisplayInfo();
  
  // display something
  table.clear();
  //table.setText(0, 0, "Lat/Lng" , true);
  table.setText(0, 0, gpsGetDate(), true);
  table.setText(0, 1, gpsGetTime(), true);
  //table.setText(1, 0, "Lat/Lng" , true);
  table.setText(1, 0, gpsGetLat(4) , true);
  table.setText(1, 1, gpsGetLng(4) , true);

  loraSend(gpsGetTime()+";"+gpsGetDate()+";"+gpsGetLat(4) +";"+gpsGetLng(4)+";");
  packageCount++;
  table.setText(2, 0, "Packets" , true);
  table.setText(2, 1, String(packageCount) , true);
  
  table.refresh();
  delay(1000); 
  

}
