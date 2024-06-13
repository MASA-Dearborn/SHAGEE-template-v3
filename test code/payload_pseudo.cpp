#include "common/SHAGEE_config.h"

// make sure that this is at the top of setup: SHAGEE_setup();

#include <STM32SD.h>
#include "XBee.h"

#include "i2c_sensors.cpp"

// intervals in milliseconds based on frequency
constexpr uint16_t interval100Hz = 10; // 100 Hz
constexpr uint16_t interval18Hz = 56;  // roughly 18 Hz but sets priority nonetheless
constexpr uint16_t interval1Hz = 1000; // 1 Hz

// Last time sensors were read
unsigned long last100Hz = 0;
unsigned long last18Hz = 0;
unsigned long last1Hz = 0;

BMP581 bmp;

// Sensor data variables
float time, stmTemp, batteryTemp1, batteryTemp2, ambientTemp;


void setup() {
    SHAGEE_setup(); // Setup GPIO, Clock, the rest...
    // i2c sensor intialization
    BMP581 bmp = bmp_setup(Wire);
    Adafruit_BNO055 bno = bno_setup(Wire);
    Bmi088Accel bmi = bmi_setup(Wire);

    // SD Card intialization
    SD.begin(sdCardPin);

    // Xbee intialization
    xbee.begin(xbeeBaudRate);
}

void loop() {
    unsigned long currentMillis = millis();
    
    // 100 Hz tasks
    if (currentMillis - last100Hz >= interval100Hz) {
        last100Hz = currentMillis;
        readHighPrioritySensors(); // BNO055, BMI, BMP
        logDataSD(); // Log data to SD
    }

    // 18 Hz tasks
    if (currentMillis - last18Hz >= interval18Hz) {
        last18Hz = currentMillis;
        readMediumPrioritySensors(); // GPS, TMP, MAX
    }

    // 1 Hz tasks
    if (currentMillis - last1Hz >= interval1Hz) {
        last1Hz = currentMillis;
        readLowPrioritySensors(); // XBee
        printSensorData(); // Print all sensor data together
    }
}

void readHighPrioritySensors(BMP581 bmp) {
    i2c_data myData = read_i2c_sensors(&bmp, &bno, &bmi);

}

void readMediumPrioritySensors() {
    // Read GPS, TMP, MAX
    latitude = gps.getLatitude();
    longitude = gps.getLongitude();
    stmTemp = readMCUTemperature(); // Function to read STM32 temperature
    batteryTemp1 = max.readTemperature(1); // Assume channel or sensor specific function
    batteryTemp2 = max.readTemperature(2);
}

void readLowPrioritySensors() {
    // Read XBee or other less frequent data
    xbee.readData(); // Example function call
}

void logDataSD() {
    // Write sensor data to SD card
    String data = String(altitude) + "," + String(latitude) + "," + String(longitude);
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
        dataFile.println(data);
        dataFile.close();
    }
}

void printSensorData() {
    // Combine and print all relevant data
    Serial.print("Altitude: "); Serial.println(altitude);
    Serial.print("Latitude: "); Serial.println(latitude);
    Serial.print("Longitude: "); Serial.println(longitude);
    Serial.print("STM Temp: "); Serial.println(stmTemp);
    Serial.print("Battery Temp 1: "); Serial.println(batteryTemp1);
    Serial.print("Battery Temp 2: "); Serial.println(batteryTemp2);
    Serial.print("Ambient Temp: "); Serial.println(ambientTemp);
}