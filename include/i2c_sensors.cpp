/**
 * @file i2c_sensors.cpp
 * @author MASA SHAGEE 23-24
 * @brief 
 * @version 0.1
 * @date 2024-05-13
 */

#include "common/SHAGEE_config.h"

#include <modifiedSparkfunBMP585.h>

#include <Adafruit_Sensor.h> 
#include <Adafruit_BNO055.h> 
#include <utility/imumaths.h> 

#include <BMI088.h>

/* ---------------- BMI CODE ---------------- */

/**
 * @brief Error code debugger for the BMP setup function
 * 
 * @param rslt is the error code to be deciphered 
 */
void bmpErrorCodePrint(int8_t rslt)
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

/**
 * @brief Setup for the BMP barometric pressure sensor
 * 
 * @param i2cPort required to initialize the sensor to the correct bus
 * @return BMP581 
 */
void bmp_setup(TwoWire &i2cPort, BMP581 &pressureSensor)
{
    // I2C address selection
    uint8_t i2cAddress = 0x47; // BMP581_I2C_ADDRESS_DEFAULT; // 0x47
    //uint8_t i2cAddress = BMP581_I2C_ADDRESS_SECONDARY; // 0x46

    // Check if sensor is connected and initialize
    // Address is optional (defaults to 0x47)
    while(pressureSensor.beginI2C(i2cAddress, i2cPort) != BMP5_OK)
    {
        // Not connected, inform user
        bmpErrorCodePrint(pressureSensor.beginI2C(i2cAddress, i2cPort));
        // Wait a bit to see if connection is established
        delay(2000);
    }
    Serial.println("BMP581 connected!");
}


/* --------------- BNO CODE ----------------- */

/**
 * @brief 
 * 
 * @return Adafruit_BNO055 
 */
void bno_setup(TwoWire &i2cPort, Adafruit_BNO055 &bno)
{
	bno = Adafruit_BNO055(55, 0x28, &i2cPort);

	Serial.println("Initializing BNO");
	if (!bno.begin()) 
    { 
    	/* There was a problem detecting the BNO055 ... check your connections */ 
		while (1)
		{
			Serial.println("No BNO055 detected. Check your wiring or I2C ADDR!"); 
			delay(2000);
		}
    } 
}

void getBNOEvents(Adafruit_BNO055 &bno, sensors_event_t &orientationData, sensors_event_t &angVelocityData, sensors_event_t &linearAccelData, sensors_event_t &magnetometerData, sensors_event_t &accelerometerData, sensors_event_t &gravityData) {
    bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER); 
    bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE); 
    bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL); 
    bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER); 
    bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER); 
    bno.getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY); 
}

/* --------------- BMI CODE ----------------- */

/**
 * @brief 
 * 
 * @param Wire 
 * @return Bmi088Accel 
 */
void bmi_setup(Bmi088 &bmiObject){
	// bmiObject.setRange(Bmi088::AccelRange::ACCEL_RANGE_24G,Bmi088::GyroRange::GYRO_RANGE_2000DPS);
	int status;
	status = bmiObject.begin();
	if (status < 0){
		Serial.print("Error in BMI088 begin() \t");
		Serial.print(status);
		Serial.println("");
		delay(100);
	}
}


/* ---------------- SHARED SENSOR CODE -------------- */
struct i2c_data {
	
	//Adafruit uses x y z for axis of rotation instead of yaw pitch roll
	float BNOorientX,  BNOorientY, BNOorientZ;
	float BNOangvelY, BNOangvelP, BNOangvelR;
	float BNOaccelX, BNOaccelY, BNOaccelZ;
	float BNOlinaccelX, BNOlinaccelY, BNOlinaccelZ;
	float BNOgyroY, BNOgyroP, BNOgyroR;
	float BNOmagX, BNOmagY, BNOmagZ;
	float BNOgravX, BNOgravY, BNOgravZ;

	float BMIaccelX, BMIaccelY, BMIaccelZ;
	float BMIgyroY, BMIgyroP, BMIgyroR;
	float BMItempC;

	float BMPaltitude, BMPtemperature;
};

i2c_data read_i2c_sensors(BMP581 &bmp, Adafruit_BNO055 &bno, Bmi088 &bmi)
{
	i2c_data returnData;

	// bmp stuff
	bmp5_sensor_data bmp_data = {0,0};
    int8_t err = bmp.getSensorData(&bmp_data);
	if(err == BMP5_OK)
    {
		returnData.BMPtemperature = bmp_data.temperature;
		returnData.BMPaltitude = bmp_data.pressure;
	}
	else
	{
		// Acquisition failed, most likely a communication error (code -2)
        Serial.print("Error getting data from BMP!");
        bmpErrorCodePrint(err);
	}

	// implement getting/setting BNO data here
   	sensors_event_t orientationData, angVelocityData, linearAccelData, magnetometerData, accelerometerData, gravityData;
	getBNOEvents(bno, orientationData, angVelocityData, linearAccelData, magnetometerData, accelerometerData, gravityData);
	
	// Orientation data
	returnData.BNOgyroY = orientationData.orientation.x;
	returnData.BNOgyroP = orientationData.orientation.y;
	returnData.BNOgyroR = orientationData.orientation.z;

	// Angular velocity data
	returnData.BNOangvelY = angVelocityData.gyro.x;
	returnData.BNOangvelP = angVelocityData.gyro.y;
	returnData.BNOangvelR = angVelocityData.gyro.z;

	// Linear acceleration data
	returnData.BNOlinaccelX = linearAccelData.acceleration.x;
	returnData.BNOlinaccelY = linearAccelData.acceleration.y;
	returnData.BNOlinaccelZ = linearAccelData.acceleration.z;

	// Magnetometer data
	returnData.BNOmagX = magnetometerData.magnetic.x;
	returnData.BNOmagY = magnetometerData.magnetic.y;
	returnData.BNOmagZ = magnetometerData.magnetic.z;

	// Accelerometer data
	returnData.BNOaccelX = accelerometerData.acceleration.x;
	returnData.BNOaccelY = accelerometerData.acceleration.y;
	returnData.BNOaccelZ = accelerometerData.acceleration.z;

	// Gravity data
	returnData.BNOgravX = gravityData.acceleration.x;
	returnData.BNOgravY = gravityData.acceleration.y;
	returnData.BNOgravZ = gravityData.acceleration.z;
   


	// BMI acceleration
	returnData.BMIaccelX = bmi.getAccelX_mss();
	returnData.BMIaccelY = bmi.getAccelY_mss();
	returnData.BMIaccelZ = bmi.getAccelZ_mss();
	// adjust the struct values
	returnData.BMIgyroY = bmi.getGyroX_rads(); 
	returnData.BMIgyroP = bmi.getGyroY_rads();
	returnData.BMIgyroR = bmi.getGyroZ_rads();
	
	returnData.BMItempC = bmi.getTemperature_C();

	return returnData;
}

void print_i2c_data(i2c_data &sensorData)
{
	Serial.println("Printing BMP");
    Serial.print("Alt: ");
    Serial.print(sensorData.BMPaltitude);
    Serial.print("\tTemp: ");
    Serial.print(sensorData.BMPtemperature);
    Serial.print("\n\n");
    
    Serial.println("Printing BNO");
    Serial.print("Gyro: ");
    Serial.print(sensorData.BNOgyroY);
    Serial.print("\t");
    Serial.print(sensorData.BNOgyroP);
    Serial.print("\t");
    Serial.print(sensorData.BNOgyroR);
    Serial.print("\n");
    Serial.print("Accel: ");
    Serial.print(sensorData.BNOaccelX);
    Serial.print("\t");
    Serial.print(sensorData.BNOaccelY);
    Serial.print("\t");
    Serial.print(sensorData.BNOaccelZ);
    Serial.print("\n\n");

    Serial.println("Printing BMI");
    Serial.print("Gyro: ");
    Serial.print(sensorData.BMIgyroY);
    Serial.print("\t");
    Serial.print(sensorData.BMIgyroP);
    Serial.print("\t");
    Serial.print(sensorData.BMIgyroR);
    Serial.print("\n");
    Serial.print("Accel: ");
    Serial.print(sensorData.BMIaccelX);
    Serial.print("\t");
    Serial.print(sensorData.BMIaccelY);
    Serial.print("\t");
    Serial.print(sensorData.BMIaccelZ);
    Serial.print("\n\n");
}
