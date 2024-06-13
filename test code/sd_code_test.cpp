#include "common/SHAGEE_config.h"
#include "sd_code.cpp"

File sdFile;
int i = 0;
 
void setup()
{
    SHAGEE_setup();
    sd_card_setup(sdFile);
}

void loop()
{
    delay(500);
    char buf[16];
    ltoa(i,buf,10);
    String ehh = (String)buf;
    Serial.println(ehh);
    sdFile.println(ehh);
    i++;
    sdFile.flush();
}

// example code of how a csv file could be created. This should be added inside sd_code.cpp
void csv_line(long* numArray)
{
  File sdFile = SD.open("log.txt", FILE_WRITE);
  if (sdFile)
  {
    sdFile.seek(sdFile.size());
    for (int j = 0; j < sizeof(numArray); j++)
    {
      // make a big string of data then do sdFile.println() or somethin
    }
    sdFile.flush(); // this is what actually saves the data to the sd card
  }
  else
  {
    Serial.println("Error writing to sd card");
  }
}