#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// define debug for debug output
// #define debug
#include "debug.h"

// WiFi
const char* mySSID = "NODES";
const char* myPW = "HappyNodes1234";

// Lora settings
#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    868E6  //433E6, 868E6, 915E6, 8E6


// WIRE
#define I2C_SDA         21
#define I2C_SCL         22


// Oled Settings:
#define DISPLAY_SDA I2C_SDA
#define DISPLAY_SCL I2C_SCL
#define DISPLAY_RST -1
#define SSD_ADDRESS 0x3c


//GPS 
// home ;)
static const double HOME_LAT = 50.1358;
static const double HOME_LON = 8.5210;
static const long GPS_CALIBRATION = -13;
// mqtt
const char* BROKER = "192.168.1.10";
uint16_t    BRPORT =  1883;
const char* BRUSER = "admin";
const char* BRPWD  = "admin";
const char* CLIENTID = "LoraGPSTracker";

#define JSON_TOPIC  "TEST/GPS_LORA" 
#define JSON_TOPIC_TEMPLATE  "[{\"TIME\": \"%s\",\"DATE\":\"%s\",\"LATITUDE\":%.4f,\"LONGITUDE\":%.4f,\"DISTANCE\":%i}]"

#endif // #define CREDENTIALS_H
