#define DEBUG
#include "debug.h"
#include <Arduino.h>
#include "credentials.h"
#include "gps.h"

void setup(){

  Serial.begin(115200);
  gpsSetup();

}

void loop(){

 gpsLoop();
 #ifdef DEBUG
 gpsDisplayInfo();
 #endif
  
}