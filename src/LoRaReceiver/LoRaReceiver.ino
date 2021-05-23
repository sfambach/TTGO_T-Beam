/**
  LoRa Receiver, receives packackages with gps data and sends them to an mqtt server.

  LIBS
  https://github.com/sandeepmistry/arduino-LoRa
  https://github.com/ThingPulse/esp8266-oled-ssd1306
  https://github.com/mikalhart/TinyGPSPlus (only for the distance)
  https://github.com/knolleary/pubsubclient

  Created by S.Fambach visit https://www.fambach.net
  With help of the examples in the libs
*/

#include<Arduino.h>
#include <Wire.h>
#include "display.h"
#include "mymqtt.h"
#include "mylora.h"
#include "mywifi.h"
#include "TinyGPS++.h"


String rssi = "--";
String packSize = "--";
String packet ;



void parseSendMessage(String message) {
  String _time;
  String _date;
  String _lat;
  String _lng;
  String buf = "";
  int index = 0;
  DEBUG_PRINT("RAW: ");
  DEBUG_PRINTLN(message);

  for ( int i = 0 ; i < message.length(); i++) {

    if (message.charAt(i) == ';') {

      switch (index) {
        case 0 : _time = String(buf); break;
        case 1 : _date = String(buf); break;
        case 2 : _lat = String(buf); break;
        case 3 : _lng = String(buf); break;
      }
      buf = "";

      if (index == 3) {
        break;
      }
      
      index ++;

    } else {
      buf += message.charAt(i);
    }
  }
  char buf2[255];

  long distance = (long)TinyGPSPlus::distanceBetween(
      _lat.toFloat(),
      _lng.toFloat(),
      HOME_LAT, 
      HOME_LON);
  distance += GPS_CALIBRATION;
  
  // send mqtt message
  sprintf(buf2, JSON_TOPIC_TEMPLATE, _time, _date, _lat.toFloat(), _lng.toFloat(), distance);
  DEBUG_PRINTLN(buf2);
  mqttPublish(JSON_TOPIC, buf2);
}

void displayData() {

  table.clear();
  table.setText(0, 0, "Rssi");
  table.setText(0, 1, String(rssi));

  table.setText(1, 0 , "Received ");
  table.setText(1, 1 , String(packSize) + "[bytes]");

  table.setText(2, 0 , "Content");
  table.setText(2, 1 , packet);

  table.refresh();
}

void cbk(int packetSize) {
  packet = "";
  packet.reserve(50);
  packSize = String(packetSize, DEC);
  for (int i = 0; i < packetSize; i++) {
    packet += (char) LoRa.read();
  }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) ;
  displayData();
  parseSendMessage(packet);
}

void setup() {

  Serial.begin(115200);
  while (!Serial);
  wifiConnect();

  displaySetup();
  loraSetup();

  mqttSetup();
}

void loop() {
  mqttLoop();
  displayLoop();
  loraLoop();

  if (loraPacketSize) {
    cbk(loraPacketSize);
  }
  //  delay(10);
}
