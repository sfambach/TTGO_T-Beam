#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// WIRE
#define I2C_SDA         21
#define I2C_SCL         22



// Oled Settings:
#define DISPLAY_SDA I2C_SDA
#define DISPLAY_SCL I2C_SCL
#define DISPLAY_RST -1
#define SSD_ADDRESS 0x3c

// AXP192
#define AXP192_ADDRESS  0x34
#define AXP_IRQ_PIN 35
#define AXP_GPS_POWER_CTRL_CH     3
#define AXP_LORA_POWER_CTRL_CH    2


#endif // CREDENTIALS_H
