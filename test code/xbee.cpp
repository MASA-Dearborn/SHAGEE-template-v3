#include <stdio.h>
#include "common/SHAGEE_config.h"

//***** In stm32f4xx_it.c file ******//
//Note: There should be a similar file for the stm32f722, it should be "stm32f7xx_it.c" - this file contains all the interrupt service routines

/* External variables --------------------------------------------------------*/
// this will throw an error if BOARD_SELECT is not set to 1 in pio config file
HardwareSerial XBSerial(XB_USART2_RX_PIN, XB_USART2_TX_PIN);

UART_HandleTypeDef huart2;

uint8_t XBeeATResponse[3];


//Enter AT Command Mode
uint8_t ATCommandModeMsg[] = "+++";

//Save configuration parameters to non-volatile memory command
uint8_t ATWR[] = "ATWR\r";

//Exit AT Command Mode command
uint8_t ATCN[] = "ATCN\r";

/** Mandatory Parameters **/

//MAC/PHY Parameters
uint8_t ATHP[] = "ATHP 0\r";
uint8_t ATID[] = "ATID 2015\r";

//Addressing Parameters
uint8_t ATDL[] = "ATDL 423F572D\r";
uint8_t ATDH[] = "ATDH 13A200\r";//MAC Destination Address of XBee Dev Kit 0x0013A200423F572D

//Serial Interfacing Parameters
uint8_t ATBD[] = "ATBD 3\r";//9600 Baud
uint8_t ATNB[] = "ATNB 0\r";
uint8_t ATSB[] = "ATSB 0\r";
uint8_t ATAP[] = "ATAP 0\r";

//MAC/PHY Parameters
uint8_t ATBR[] = "ATBR 1\r";
uint8_t ATPL[] = "ATPL 2\r";
uint8_t ATRR[] = "ATRR ";

//Network Parameters
uint8_t ATCE[] = "ATCE ";
uint8_t ATBH[] = "ATBH ";
uint8_t ATNH[] = "ATNH ";
uint8_t ATMR[] = "ATMR ";

//Addressing Parameters
uint8_t ATTO[] = "ATTO ";
uint8_t ATNI[] = "ATNI ";
uint8_t ATNT[] = "ATNT ";
uint8_t ATNO[] = "ATNO ";
uint8_t ATCI[] = "ATCI ";

//Security Parameters
uint8_t ATEE[] = "ATEE ";
uint8_t ATC8[] = "ATC8 ";
uint8_t ATKY[] = "ATKY ";

//Serial Interfacing Parameters
uint8_t ATRO[] = "ATRO ";
uint8_t ATFT[] = "ATFT ";
uint8_t ATAO[] = "ATAO ";

//Input Output Setting Parameters
uint8_t ATD0[] = "ATD0 ";
uint8_t ATD1[] = "ATD1 ";
uint8_t ATD2[] = "ATD2 ";
uint8_t ATD3[] = "ATD3 ";
uint8_t ATD4[] = "ATD4 ";
uint8_t ATD5[] = "ATD5 ";
uint8_t ATD6[] = "ATD6 ";
uint8_t ATD7[] = "ATD7 ";
uint8_t ATD8[] = "ATD8 ";
uint8_t ATD9[] = "ATD9 ";

uint8_t ATP0[] = "ATP0 ";
uint8_t ATP1[] = "ATP1 ";
uint8_t ATP2[] = "ATP2 ";
uint8_t ATP3[] = "ATP3 ";
uint8_t ATP4[] = "ATP4 ";
uint8_t ATP5[] = "ATP5 ";
uint8_t ATP6[] = "ATP6 ";
uint8_t ATP7[] = "ATP7 ";
uint8_t ATP8[] = "ATP8 ";
uint8_t ATP9[] = "ATP9 ";
uint8_t ATPD[] = "ATPD ";
uint8_t ATPR[] = "ATPR ";

uint8_t ATM0[] = "ATM0 ";
uint8_t ATM1[] = "ATM1 ";
uint8_t ATLT[] = "ATLT ";
uint8_t ATRP[] = "ATRP ";

//Input Output Sampling Parameters
uint8_t ATAV[] = "ATAV ";
uint8_t ATIC[] = "ATIC ";
uint8_t ATIF[] = "ATIF ";
uint8_t ATIR[] = "ATIR ";

//Input Output Line Passing
uint8_t ATIU[] = "ATIU ";
uint8_t ATIA[] = "ATIA ";

uint8_t ATT0[] = "ATT0 ";
uint8_t ATT1[] = "ATT1 ";
uint8_t ATT2[] = "ATT2 ";
uint8_t ATT3[] = "ATT3 ";
uint8_t ATT4[] = "ATT4 ";
uint8_t ATT5[] = "ATT5 ";
uint8_t ATT6[] = "ATT6 ";
uint8_t ATT7[] = "ATT7 ";
uint8_t ATT8[] = "ATT8 ";
uint8_t ATT9[] = "ATT9 ";

uint8_t ATQ0[] = "ATQ0 ";
uint8_t ATQ1[] = "ATQ1 ";
uint8_t ATQ2[] = "ATQ2 ";
uint8_t ATQ3[] = "ATQ3 ";
uint8_t ATQ4[] = "ATQ4 ";

uint8_t ATPT[] = "ATPT ";

//Sleep Commands Parameters
uint8_t ATSM[] = "ATSM ";
uint8_t ATSO[] = "ATSO ";
uint8_t ATSN[] = "ATSN ";
uint8_t ATSP[] = "ATSP ";
uint8_t ATST[] = "ATST ";
uint8_t ATWH[] = "ATWH ";

//AT Command Options Parameters
uint8_t ATCC[] = "ATCC ";
uint8_t ATCT[] = "ATCT ";
uint8_t ATGT[] = "ATGT ";

//Firmware Version/Information Parameter
uint8_t ATDD[] = "ATDD ";

//XBee Flag Variables
uint8_t RxDataPinFlag = 0;

/* USER CODE END PFP */
void XBeeInit(HardwareSerial fruitLoops) {

    /***** XBee Configuration Code Section *****/

	//Enter into AT Command Mode
	//HAL_UART_Transmit(&huart2, ATCommandModeMsg, strlen((char*)ATCommandModeMsg), HAL_MAX_DELAY);
  XBSerial.print("+++");
  
	//keep polling RX line until receive OK response from XBee Transceiver

  Serial.println("Waiting for XB response...");
	while(!fruitLoops.available());
  Serial.println("XB responded!");

	//Setup Pan ID for XBee Transceiver
	HAL_UART_Transmit(&huart2, ATID, strlen((char*)ATID), HAL_MAX_DELAY);


	//Setup RF Data Rate to 110 kbps
	HAL_UART_Transmit(&huart2, ATBR, strlen((char*)ATBR), HAL_MAX_DELAY);

	//Setup Power Level for XBee Transceiver
	HAL_UART_Transmit(&huart2, ATPL, strlen((char*)ATPL), HAL_MAX_DELAY);

	//Setup Destination Address Low (DL) Parameter for XBee Transceiver
	HAL_UART_Transmit(&huart2, ATDL, strlen((char*)ATDL), HAL_MAX_DELAY);

	//Setup Destination Address High (DH) Parameeter for XBee Transceiver
	HAL_UART_Transmit(&huart2, ATDH, strlen((char*)ATDH), HAL_MAX_DELAY);

	//Setup Baud Rate (BD) parameter for XBee transceiver
	HAL_UART_Transmit(&huart2, ATBD, strlen((char*)ATBD), HAL_MAX_DELAY);

	//Setup Parity (NB) parameter for XBee transceiver
	HAL_UART_Transmit(&huart2, ATNB, strlen((char*)ATNB), HAL_MAX_DELAY);

	//Setup Stop Bits (SB) parameter for XBee transceiver
	HAL_UART_Transmit(&huart2, ATSB, strlen((char*)ATSB), HAL_MAX_DELAY);

	//Set AP parameter to transparent mode for the XBee transceiver

	/*** Optional Parameters to set ***/

	//Verify configuration parameters

    //Save Configuration Parameters to non-volatile memory
    HAL_UART_Transmit(&huart2, ATWR, strlen((char*)ATWR), 100);

    //Exit AT Command Mode
    HAL_UART_Transmit(&huart2, ATCN, strlen((char*)ATWR), 100);
}

void setup()
{
  SHAGEE_setup();
  XBSerial.begin(9600);
  XBeeInit(XBSerial);
}

void loop()
{
  XBSerial.println("Hello World!"); 
}