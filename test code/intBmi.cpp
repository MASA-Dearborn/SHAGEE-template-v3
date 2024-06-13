#include "BMI088.h"
#include "common/SHAGEE_config.h"

#define SERIAL_PRINT_BAUD_RATE 9600 // default 9600
#define SERIAL_PRINT_TX DEBUG_UART3_TX_PIN
#define SERIAL_PRINT_RX DEBUG_UART3_RX_PIN

TwoWire Wire2(I2C1_SDA_PIN, I2C1_SCL_PIN);

/* accel object */
Bmi088Accel accel(Wire2,0x18);
/* gyro object */
Bmi088Gyro gyro(Wire2,0x68);

volatile bool accel_flag, gyro_flag;

void accel_drdy()
{
  accel_flag = true;
}

void gyro_drdy()
{
  gyro_flag = true;
}

void setup() 
{
  int status;
  /* USB Serial to print data */
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED1_PIN, HIGH);
  delay(200);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED1_PIN, LOW);
  delay(500);
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED1_PIN, HIGH);
  delay(200);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED1_PIN, LOW);
  delay(500);


  Serial.setTx(SERIAL_PRINT_TX);
  Serial.setRx(SERIAL_PRINT_RX);
  Serial.begin(9600);

  Serial.println("Beginning...");
  
  
  /* start the sensors */
  status = accel.begin();
  if (status < 0) {
    Serial.println("Accel Initialization Error");
    Serial.println(status);
    errorBlinker();
  }
  status = accel.setOdr(Bmi088Accel::ODR_100HZ_BW_19HZ);
  status = accel.pinModeInt1(Bmi088Accel::PUSH_PULL,Bmi088Accel::ACTIVE_HIGH);
  status = accel.mapDrdyInt1(true);


  status = gyro.begin();
  if (status < 0) {
    Serial.println("Gyro Initialization Error");
    Serial.println(status);
    while (1) {}
  }
  status = gyro.setOdr(Bmi088Gyro::ODR_100HZ_BW_12HZ);
  status = gyro.pinModeInt3(Bmi088Gyro::PUSH_PULL,Bmi088Gyro::ACTIVE_HIGH);
  status = gyro.mapDrdyInt3(true);

  pinMode(BMI_ACC_INT_PIN,INPUT);
  attachInterrupt(BMI_ACC_INT_PIN,accel_drdy,RISING);
  pinMode(BMI_GYR_INT_PIN,INPUT);
  attachInterrupt(BMI_GYR_INT_PIN,gyro_drdy,RISING);  
}

void loop() 
{
  if (accel_flag && gyro_flag) {
    accel_flag = false;
    gyro_flag = false;
    /* read the accel */
    accel.readSensor();
    /* read the gyro */
    gyro.readSensor();
    /* print the data */
    Serial.print(accel.getAccelX_mss());
    Serial.print("\t");
    Serial.print(accel.getAccelY_mss());
    Serial.print("\t");
    Serial.print(accel.getAccelZ_mss());
    Serial.print("\t");
    Serial.print(gyro.getGyroX_rads());
    Serial.print("\t");
    Serial.print(gyro.getGyroY_rads());
    Serial.print("\t");
    Serial.print(gyro.getGyroZ_rads());
    Serial.print("\t");
    Serial.print(accel.getTemperature_C());
    Serial.print("\n");
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED1_PIN, HIGH);
    delay(200);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED1_PIN, LOW);
  }
}