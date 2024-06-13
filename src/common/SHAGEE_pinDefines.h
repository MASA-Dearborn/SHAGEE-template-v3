/**
* @brief Pin definitions for MASA's 2023-2024 SHAGEE Payload and Airbrakes PCBs
*
* @details
* Designed for the payload v1/v2 and airbrakes v1 PCBs. Both boards use an STM32F722RETx as their MCU
* Code developed on an STM32duino platform through PlatformIO and Arduino IDE. Flashed to the chip using SWD over a ST-Link V3
* 
* This was written to make the lives of the CS majors a little easier. Just switch which macro you have 
* defined to change which PIN definitions you're using
* 
* @file SHAGEE_pinDefines.h
* @author MASA SHAGEE '23-'24 season
* @date 2024-4-10
* @version 0.1
*/


// Is this needed?
// #pragma once

// Header guard macro
#ifndef USER_DEFINED_PINS
#define USER_DEFINED_PINS

// CPP Guard
#ifdef __cplusplus
extern "C" {
#endif


// This is the only common pin definition for all boards we're developing on
// If this is blinking, there is an error
#define LED1_PIN                    PA10

// Begin checking which board is selected. 
#ifdef INSBOARDV1

    // Xbee SX 900 RS232, SPI, and GPIO controls
    #define XB_USART2_CTS_PIN           PA0
    #define XB_USART2_RTS_PIN           PA1
    #define XB_USART2_TX_PIN            PA2
    #define XB_USART2_RX_PIN            PA3
    #define XB_GP_O_RST_PIN             PA4

    // rebind for cross-compatibility. Not accurate
    #define DEBUG_UART3_TX_PIN          XB_USART2_TX_PIN
    #define DEBUG_UART3_RX_PIN          XB_USART2_RX_PIN


    // SD Card 4 bit interface
    #define SD_CK_PIN                   PC12
    #define SD_CMD_PIN                  PD2
    #define SD_D0_PIN                   PC8
    #define SD_D1_PIN                   PC9
    #define SD_D2_PIN                   PC10
    #define SD_D3_PIN                   PC11


    // Ublox SAM-M10Q GPS sensor
    #define GPS_USART1_TX_PIN           PB10
    #define GPS_USART1_RX_PIN           PB11


    // Bosch sensors (BNO, BMI, BMP) i2c bus
    #define I2C1_SCL_PIN                PB8 // I2C for bosch sensors
    #define I2C1_SDA_PIN                PB9 // I2C for bosch sensors


    // TMP235 Temperature Sensor ADCs
    #define TMP1_PIN                    PB0
    #define TMP2_PIN                    PB1


    // Thermocouple MAX31855 SPI Recieve only master
    #define TC_SPI2_SCK_PIN             PC4
    #define TC_SPI2_MISO_PIN            PC2
    #define TC_CS1_PIN                  PC0
    #define TC_CS2_PIN                  PC1


    // Debugging and other misc connections
    #define LED2_PIN                    PA11 // Indicator 5 or R11

    #define BUZZER_PIN              PB14

#endif // ends INS Board v1 definitions

#ifdef INSBOARDV2

    // Xbee SX 900 RS232, SPI, and GPIO controls
    #define XB_USART2_CTS_PIN           PA0
    #define XB_USART2_RTS_PIN           PA1
    #define XB_USART2_TX_PIN            PA2
    #define XB_USART2_RX_PIN            PA3
    #define XB_SPI1_NCS1_PIN            PA4
    #define XB_SPI1_SCK_PIN             PA5
    #define XB_SPI1_MISO_PIN            PA6
    #define XB_SPI1_MOSI_PIN            PA7
    #define XB_GP_O_RST_PIN             PC3
    #define XB_GP_O_SLP_PIN             PC4


    // SD Card 4 bit interface
    #define SD_CK_PIN                   PC12
    #define SD_CMD_PIN                  PD2
    #define SD_D0_PIN                   PC8
    #define SD_D1_PIN                   PC9
    #define SD_D2_PIN                   PC10
    #define SD_D3_PIN                   PC11


    // USB PINs idk what else to say
    #define USB_VBUS_SENS_PIN           PA9
    #define USB_FS_DM_PIN               PA11
    #define USB_FS_DP_PIN               PA12


    // Ublox SAM-M10Q GPS sensor
    #define GPS_GP_O_PPS_PIN            PB5
    #define GPS_USART1_TX_PIN           PB6
    #define GPS_USART1_RX_PIN           PB7


    // Bosch sensors (BNO, BMI, BMP) i2c fast mode bus 
    #define I2C1_SCL_PIN                PB8
    #define I2C1_SDA_PIN                PB9


    // Bosch sensors (BNO, BMI, BMP) hardware interrupt PINs
    #define BMP_INT_PIN                 PB15
    #define BMI_ACC_INT_PIN             PC6
    #define BMI_GYR_INT_PIN             PC7
    #define BNO_INT_PIN                 PA8


    // TMP235 Temperature Sensor ADCs
    #define TMP1_PIN                    PB0 // ADC1_IN8
    #define TMP2_PIN                    PB1 // ADC1_IN9


    // Thermocouple MAX31855 SPI Recieve only master
    #define TC_SPI2_SCK_PIN             PB13
    #define TC_SPI2_MISO_PIN            PC2
    #define TC_CS1_PIN                  PB12 // this definition is the actual chip select for SPI2
    #define TC_CS2_PIN                  PC1


    // Debugging and other misc connections
    #define LED2_PIN                    PB2

    #define TESTPOINT_GPIO_2_PIN        PC13
    #define TESTPOINT_GPIO_1_PIN        PC0

    #define DEBUG_UART3_TX_PIN          PB10
    #define DEBUG_UART3_RX_PIN          PB11

    #define BUZZER_PIN              PB14

#endif // ends INS Board v2 definitions

#ifdef AIRBRAKES

    // USB pins
    #define USB_VBUS_SENS_PIN           PA9
    #define USB_FS_DM_PIN               PA11
    #define USB_FS_DP_PIN               PA12

    // Motor driver pins
    #define MD_DIR                      PA0
    #define MD_STEP                     PA1
    
    #define MD_M0                       PA5
    #define MD_M1                       PA2

    #define MD_nSLP                     PC2
    #define MD_EN                       PC3
    #define MD_TRQ_ST                   PA3
    #define MD_STL_REP                  PA4
    #define MD_nFAULT                   PA6

    // SD Card 4 bit interface
    #define SD_CK_PIN                   PC12
    #define SD_CMD_PIN                  PD2
    #define SD_D0_PIN                   PC8
    #define SD_D1_PIN                   PC9
    #define SD_D2_PIN                   PC10
    #define SD_D3_PIN                   PC11


    // Bosch sensors (BNO, BMI, BMP) i2c fast mode bus 
    #define I2C1_SCL_PIN                PB8
    #define I2C1_SDA_PIN                PB9

    #define BMP_INT_PIN                 PB8
    #define BNO_INT_PIN                 PB5
    #define BMI_GYR_INT_PIN             PB6
    #define BMI_ACC_INT_PIN             PB7

    // Debugging and other misc connections
    #define DEBUG_UART3_TX_PIN          PB10
    #define DEBUG_UART3_RX_PIN          PB11

    #define BUZZER_PIN                  PA7

    #define TMP1_PIN                    PC4

    #define LED2_PIN                    PB0

#endif // ends airbrakes board v1 definitions

#define CUM 69 // pls ignore

/*! CPP guard */
#ifdef __cplusplus
}
#endif // end of CPP guard


#endif // end of header guard