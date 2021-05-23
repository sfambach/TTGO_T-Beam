#include <Arduino.h>
#include <Wire.h>
#include <axp20x.h>
#include "credentials.h"
#include "display.h"


AXP20X_Class axp;
bool  axpIrq = 0;
uint8_t second = 0;
uint32_t timer = 0;
bool pmu_irq_triggered = false;

void scanI2Cdevice(void)
{
    byte err, addr;
    int nDevices = 0;
    for (addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        err = Wire.endTransmission();
        if (err == 0) {
            Serial.print("I2C device found at address 0x");
            if (addr < 16)
                Serial.print("0");
            Serial.print(addr, HEX);
            Serial.println(" !");
            nDevices++;

            if (addr == SSD_ADDRESS) {
               // ssd1306_found = true;
                Serial.println("ssd1306 display found");
            }
            if (addr == AXP192_ADDRESS) {
                // axp192_found = true;
                Serial.println("axp192 PMU found");
            }
        } else if (err == 4) {
            Serial.print("Unknow error at address 0x");
            if (addr < 16)
                Serial.print("0");
            Serial.println(addr, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
}

void setup(){


  DEBUG_INIT;
  displaySetup();

  Serial.begin(115200);
  Wire.begin(SDA, SCL);

  while( axp.begin(Wire,AXP192_SLAVE_ADDRESS) == AXP_FAIL ){
      Serial.println(F("AXP Power begin FAILED"));
      delay(1000);
  }

  axp.setPowerOutPut(AXP192_LDO2, AXP202_ON); // LORA radio
  axp.setPowerOutPut(AXP192_LDO3, AXP202_ON); // GPS main power
  axp.setDCDC1Voltage(3300); // for the OLED power

  axp.adc1Enable(AXP202_BATT_CUR_ADC1, 1);
  axp.enableIRQ(AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_BATT_REMOVED_IRQ | AXP202_BATT_CONNECT_IRQ, 1);
  axp.clearIRQ();

    pinMode(AXP_IRQ_PIN, INPUT_PULLUP);
        attachInterrupt(AXP_IRQ_PIN, [] {
            pmu_irq_triggered = true;
        }, FALLING);


  Serial.println(F("AXP Power begin SUCCESS"));
  

}

void loop(){

  scanI2Cdevice();
   if (millis() - timer > 1000) {
        second++;
        Serial.printf("%u second\n", second);
        timer = millis();
    }
     #ifdef AXP_IRQ_PIN  
        int axpIrq = 0;
        axp.readIRQ();
        if (axp.isPEKShortPressIRQ()) {
            Serial.printf("AXP202 PEK key Click\n");
        }
        if (axp.isTimerTimeoutIRQ()) {
            Serial.printf("AXP202 timer timeout\n");
            axp.clearTimerStatus();
            while (1) {
                delay(100);
            }
        }
        axp.clearIRQ();
    #endif AXP_IRQ_PIN// 


  displayLoop();

  table.drawLines();

  table.setText(0,0, "Charing" , true);
  table.setText(0,1, axp.isChargeing()?F("YES"):F("NO"), true) ;
  table.setText(1,0, "Battery" , true);
  table.setText(1,1, axp.isBatteryConnect()?F("YES"):F("NO"), true) ;
  table.setText(2,0, "Voltage" , true);
  table.setText(2,1, axp.getBattVoltage()/1000, true) ;
  table.setText(3,0, "Current" , true);
  table.setText(3,1, axp.getBattChargeCurrent(), true) ;

  table.refresh();

    delay(4000);
  
}