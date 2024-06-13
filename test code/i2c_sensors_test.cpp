#include "common/SHAGEE_config.h"
#include <Arduino.h>
#include "i2c_sensors.cpp"


BMP581 bmp;
Adafruit_BNO055 bno;
Bmi088 bmi(Wire,0x18,0x68);
i2c_data sensorData;

void setup()
{
    SHAGEE_setup();
    pinMode(LED1_PIN, OUTPUT);
    Serial.println("Beginning...");

    Wire.begin();
    delay(10);
    bmp_setup(Wire, bmp);
    bmi_setup(bmi);
    bno_setup(Wire, bno);
}

int i = 0;
void loop()
{
    digitalWrite(LED1_PIN, HIGH);
    delay(250);
    digitalWrite(LED1_PIN, LOW);
    delay(250);

    sensorData = read_i2c_sensors(bmp, bno, bmi);

    print_i2c_data(sensorData);
    delay(500);
}