/**
 * @file SHAGEE_config.h
 * @author MASA SHAGEE '23-'24 season
 * @brief Made to handle low-level setup. Also does non-board specific setup
 * @version 0.1
 * @date 2024-04-11
 */


/* ---------------- INCLUDES --------------------- */

// if you're using generic includes, you can add them to the 
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>


/* ---------------- GENERIC CONFIG -----------------*/
// setting up the pin definition depending on the value defined in platformio.ini build_flags
#if PCB_BOARD_SELECT == 0
    #define INSBOARDV1
    #include "SHAGEE_pinDefines.h"
#elif PCB_BOARD_SELECT == 1
    #define INSBOARDV2
    #include "SHAGEE_pinDefines.h"
#elif PCB_BOARD_SELECT == 2
    #define AIRBRAKES
    #include "SHAGEE_pinDefines.h"
#else
    // eventually we should replace this with an error handler, but this works for now
    // Flash the LED1 light since that's the only pin universal to all 3 boards
    #define LED1_PIN                    PA10
#endif

#ifdef SWO_PRINT
    #include "SHAGEE_print.h"
#endif


#ifndef SHAGEE_CONFIG
#define SHAGEE_CONFIG

/* --------------- MACROS AND STUFF ---------------- */
#ifndef SERIAL_PRINT_BAUD_RATE
    #define SERIAL_PRINT_BAUD_RATE      9600
#endif

// redefining UART to a universal serial macro
#ifdef INSBOARDV1
    #define SERIAL_PRINT_TX             XB_USART2_TX_PIN
    #define SERIAL_PRINT_RX             XB_USART2_RX_PIN
#endif
#ifdef INSBOARDV2
    #define SERIAL_PRINT_TX             DEBUG_UART3_TX_PIN
    #define SERIAL_PRINT_RX             DEBUG_UART3_RX_PIN
#endif
#ifdef AIRBRAKES
    #define SERIAL_PRINT_TX             DEBUG_UART3_TX_PIN
    #define SERIAL_PRINT_RX             DEBUG_UART3_RX_PIN
#endif




/* ---------------- FUNCTION DEFINITIONS ------------------ */

int SHAGEE_setup()
{
    pinMode(LED1_PIN, OUTPUT);
// if this isn't defined, no board was selected, so blink LED1 endlessly
#ifndef CUM
    for(;;)
    {
        digitalWrite(LED1_PIN, HIGH);
        delay(500);
        digitalWrite(LED1_PIN, LOW);
        delay(500);
    }
#endif
#ifdef CUM
    // 4x initialization bootup blinks and LED2 output mode
    pinMode(LED2_PIN, OUTPUT);

    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    delay(100);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    delay(100);
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    delay(100);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    delay(100);
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    delay(100);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    delay(100);
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    delay(100);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    delay(1000);
#endif

// enable high speed crystal if the platformio build flag is defined
#ifdef HSE_ENABLE
    SystemClock_Config();
    SystemCoreClockUpdate();
#endif

    // rebind default wire object pins & init
    Wire.setSCL(I2C1_SCL_PIN);
    Wire.setSDA(I2C1_SDA_PIN);
    Wire.begin();

    // rebind default Serial object & init
    Serial.setTx(SERIAL_PRINT_TX);
    Serial.setRx(SERIAL_PRINT_RX);
    Serial.begin(SERIAL_PRINT_BAUD_RATE);
    while(!Serial) {}
    
    return 0;
}

void errorBlinker()
{
    pinMode(LED1_PIN, OUTPUT);
    while(1 + 1 != 11)
    {
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED1_PIN, HIGH);
        delay(1000);
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED1_PIN, LOW);
        delay(1000);
    }
}
// This was autogenerated in cubeIDE and pasted here. This has yet to be tested
#ifdef HSE_ENABLE
  #define HSE_VALUE 24000000U
  void SystemClock_Config(void)
  {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 12;
    RCC_OscInitStruct.PLL.PLLN = 96;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
      Error_Handler();
    }
  }
#endif // end of HSE_ENABLE check

#endif // end of file header guard
