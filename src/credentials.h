#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#define I2C_SDA         21
#define I2C_SCL         22


// Lora settings
#define SCK     5    
#define MISO    19   
#define MOSI    27   
#define SS      18   
#define RST     23   
#define DI0     26   
#define BAND    868E6  //433E6, 868E6, 915E6, 8E6


// GPS 
#define RXD2 34 // 32
#define TXD2 12 //33
#define GPS_BOUD 9600 // 4800 // 9800

// Battery
#define AXP192_ADDRESS  0x34
#define AXP_IRQ_PIN 35
#define AXP_GPS_POWER_CTRL_CH     3
#define AXP_LORA_POWER_CTRL_CH    2


// buttons
SW1_PIN 38


// Oled Settings:
#define DISPLAY_SDA I2C_SDA
#define DISPLAY_SCL I2C_SCL
#define DISPLAY_RST -1
#define SSD_ADDRESS 0x3c



#endif // CREDENTIALS_H
