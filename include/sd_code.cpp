#include <STM32SD.h>
#include <string>
#include "common/SHAGEE_config.h"

// Use sdFile.println or sdFile.print to save to the SD card

void sd_card_setup(File &sdFile)
{
  SD.setDx(SD_D0_PIN, SD_D1_PIN, SD_D2_PIN, SD_D3_PIN);
  SD.setCK(SD_CK_PIN);
  SD.setCMD(SD_CMD_PIN);
  
  Serial.print("Initializing SD card...");
  while (!SD.begin(SD_DETECT_NONE)){}
  Serial.println("Initialization done.");
  
  // open the file
  sdFile = SD.open("outputFile.txt", FILE_WRITE);

  // delete this if you're getting weird sd card behavior
  // seek to the end of the file to avoid overriding existing data
  Serial.println("Seeking to the end of file");
  if (sdFile) {
    sdFile.seek(sdFile.size());
    Serial.println("Seeking complete");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("Error opening outputFile.txt");
  }
 
  // if the file opened okay, write to it:
  if (sdFile) {
    Serial.print("Performing self test. Writing to outputFile.txt...");
    sdFile.println("This line is reserved for SD Card self test");
    sdFile.flush();
    Serial.println("Done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("Error opening outputFile.txt");
  }
  Serial.println("SD setup concluded");
}