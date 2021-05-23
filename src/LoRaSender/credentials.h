
// define debug for debug output
// #define debug
#include "debug.h"


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


// GPS 
#define RXD2 34 // 32
#define TXD2 12 //33
#define GPS_BOUD 9600 // 4800 // 9800
