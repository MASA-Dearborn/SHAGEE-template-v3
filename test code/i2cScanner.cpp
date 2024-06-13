#include <Wire.h>
#include "common/SHAGEE_config.h"

#define SDA_PIN I2C1_SDA_PIN // default SDA_PIN
#define SCL_PIN I2C1_SCL_PIN // default SCL_PIN
#define SERIAL_PRINT_BAUD_RATE 9600 // default 9600
#define SERIAL_PRINT_TX DEBUG_UART3_TX_PIN
#define SERIAL_PRINT_RX DEBUG_UART3_RX_PIN

void setup()
{
  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.begin();

  Serial.setTx(SERIAL_PRINT_TX); // Xbee's UART on INS board
  Serial.setRx(SERIAL_PRINT_RX);
  Serial.begin(SERIAL_PRINT_BAUD_RATE);

  Serial.println("===== I2C SCANNER STM32 =====");
  delay(100);
}


void loop()
{ 
  uint8_t devices = 0;
  byte addr = 0x00, error = 0x00;

  Serial.println(" ");
  Serial.println("Scanning...");
  for(addr = 1; addr < 127; ++addr)
  {
    Wire.beginTransmission(addr);
    error = Wire.endTransmission();

    if(error == 0)
    {
      Serial.print("I2C Device: 0x");
      if(addr < 16) Serial.print("0");
      Serial.println(addr, HEX);

      ++devices;
    }
    else if(error == 4)
    {
      Serial.print("Unknow error address: ");
      if(addr < 16) Serial.print("0");
      Serial.println(addr, HEX);
    }
  }

  Serial.println(String("Devices Found: ") + String((int) devices));
  delay(1000);
}