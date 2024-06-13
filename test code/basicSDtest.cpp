#include <STM32SD.h>
#include "common/SHAGEE_config.h"

#ifndef SD_DETECT_PIN
#define SD_DETECT_PIN SD_DETECT_NONE
#endif

File sdFile;
 
void setup()
{
    SHAGEE_setup();

    SD.setDx(SD_D0_PIN, SD_D1_PIN, SD_D2_PIN, SD_D3_PIN);
    SD.setCK(SD_CK_PIN);
    SD.setCMD(SD_CMD_PIN);
    
    Serial.print("Initializing SD card...");
    while (!SD.begin(SD_DETECT_PIN))
    {
        // blink the LED if it isnt initializing
        digitalWrite(LED1_PIN, HIGH);
        delay(100);
        digitalWrite(LED1_PIN, LOW);
        delay(100);
    }
    Serial.println("initialization done.");
    
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    sdFile = SD.open("test.txt", FILE_WRITE);
    
    // if the file opened okay, write to it:
    if (sdFile) 
    {
        Serial.print("Writing to test.txt...");
        sdFile.println("testing 1, 2, 3.");
        // close the file:
        sdFile.close();
        Serial.println("done.");
    } 
    else 
    {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
    }
    
    // re-open the file for reading:
    sdFile = SD.open("test.txt");
    if (sdFile) 
    {
        Serial.println("test.txt:");
    
        // read from the file until there's nothing else in it:
        while (sdFile.available()) {
        Serial.write(sdFile.read());
        }
        // close the file:
        sdFile.close();
    } 
    else 
    {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
    }
    Serial.println("###### End of the SD tests ######");
}