#include <Arduino.h>
#include <WiFi.h>
#include "credentials.h"
#include "display.h"
#include "debug.h"


void setup(){

  DEBUG_INIT;
  displaySetup();

}

void loop(){

  displayLoop();

  table.drawLines();
  // first line show mac address
  table.setText(0,0, "MAC" , true);
  table.setText(0,1, WiFi.macAddress(), true) ;

  // second line show seconds since start
  table.setText(1,0, "Secs" , true);
  table.setText(1,1, String((int) (millis()/1000)), true) ;

  // .. 
  table.refresh();
   

  
  
}