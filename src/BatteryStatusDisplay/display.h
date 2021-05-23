#ifndef DISPLAY_H
#define DISPLAY_H

#include "credentials.h"
#include "debug.h"
#include "SSD1306.h" //https://github.com/ThingPulse/esp8266-oled-ssd1306
//#include "images.h"
#include "OledTable.h"
#include "fonts.h"

// Oled Settings:
//#define DISPLAY_SDA 4
//#define DISPLAY_SCL 15
//#define DISPLAY_RST 16
//#define SSD_ADDRESS 0x3c

SSD1306 display(SSD_ADDRESS, DISPLAY_SDA, DISPLAY_SCL);
OledTable table(&display,5,2);


void displaySetup(){
  // Init display 
  pinMode(DISPLAY_RST,OUTPUT);
  digitalWrite(DISPLAY_RST, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(DISPLAY_RST, HIGH); // while OLED is running, must set GPIO16 in high、
  display.init();
  display.flipScreenVertically();  
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  //display.setFont(F5X7); // 
  //display.setFont(ArialMT_Plain_10); 
  display.setFont(Open_Sans_Regular_7);

  // init table
  table.init();

  pinMode(25, OUTPUT);
}

void displayLoop(){


}


#endif // DISPLAY_H
