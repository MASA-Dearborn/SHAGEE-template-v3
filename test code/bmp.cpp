#include <Wire.h>
#include "modifiedSparkfunBMP585.h"
#include "common/SHAGEE_config.h"


#define SERIAL_PRINT_BAUD_RATE 9600 // default 9600

// Create a new sensor object
BMP581 pressureSensor;
// TwoWire Wire(I2C1_SDA_PIN, I2C1_SCL_PIN);

// I2C address selection
uint8_t i2cAddress = 0x47; // BMP581_I2C_ADDRESS_DEFAULT; // 0x47
//uint8_t i2cAddress = BMP581_I2C_ADDRESS_SECONDARY; // 0x46


void errorCodePrint(int8_t rslt)
{
	if (rslt != BMP5_OK)
	{
    Serial.println("Checking error...");

		if (rslt == BMP5_E_NULL_PTR)
		{
      Serial.println("Error: Null Pointer");
    }
		else if (rslt == BMP5_E_COM_FAIL)
		{
      Serial.println("Error: Communication failure.");
		}
		else if (rslt == BMP5_E_DEV_NOT_FOUND)
		{
      Serial.println("Error: Device not found.");
		}
		else if (rslt == BMP5_E_INVALID_CHIP_ID)
		{
      Serial.println("Error: Invalid chip.");
		}
		else if (rslt == BMP5_E_POWER_UP)
		{
      Serial.println("Error: Power up failed.");
		}
		else if (rslt == BMP5_E_POR_SOFTRESET)
		{
      Serial.println("Error: Power-on reset/softreset failure.");
		}
		else if (rslt == BMP5_E_INVALID_POWERMODE)
		{
			Serial.println("Error: Invalid Powermode.");
		}
		else
		{
			/* For more error codes refer "*_defs.h" */
      Serial.print("Error: Unknown Error Code: \t");
      Serial.println(rslt);
		}
	}
}

int8_t debug_i2c_read(uint8_t bmpRegister, uint8_t length, uint8_t *buffer)
{
  int8_t status = 0;
  Wire.beginTransmission(i2cAddress);
  Wire.write(bmpRegister);
  Wire.endTransmission(i2cAddress);
  Wire.requestFrom(i2cAddress, length);
  int8_t available  = Wire.available();
  Serial.print("Contents:\t");
  for (int i = 0; i < available; i++)
  {
    buffer[i] = Wire.read();
    Serial.print("\t");
    Serial.print(buffer[i]);
  }
  Serial.println();

  return status;
}




void setup()
{
    SHAGEE_setup();

    Serial.println("BMP581 Example1 begin!");

    // Check if sensor is connected and initialize
    // Address is optional (defaults to 0x47)
    while(pressureSensor.beginI2C(i2cAddress, Wire) != BMP5_OK)
    {
        // Not connected, inform user
        errorCodePrint(pressureSensor.beginI2C(i2cAddress, Wire));

        // Wait a bit to see if connection is established
        delay(500);

        uint8_t configResult; 
        debug_i2c_read(BMP5_REG_INT_STATUS, 1, &configResult); // 0x50 or 0x51

        delay(500);
    }

    Serial.println("BMP581 connected!");
}

void loop()
{
    // Get measurements from the sensor
    bmp5_sensor_data data = {0,0};
    int8_t err = pressureSensor.getSensorData(&data);

    // Check whether data was acquired successfully
    if(err == BMP5_OK)
    {
        // Acquisistion succeeded, print temperature and pressure
        Serial.print("Temperature (C): ");
        Serial.print(data.temperature);
        Serial.print("\t\t");
        Serial.print("Pressure (Pa): ");
        Serial.println(data.pressure);
    }
    else
    {
        // Acquisition failed, most likely a communication error (code -2)
        Serial.print("Error getting data from sensor!");
        errorCodePrint(err);
    }

    // Only print every second
    delay(1000);
}