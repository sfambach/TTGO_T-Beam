#include <Arduino.h>
#include "credentials.h"


void setup(){

  Serial.begin(115200);
  pinMode(PIN_SW1, INPUT_PULLDOWN); 

}

void loop(){

  if(digitalRead(PIN_SW1) == LOW){
    Serial.println("PRESSED!");
  }
  else {
      Serial.println("NOT PRESSED!");

  }
  
}