//writing to persistent memory for saving settings
#include <EEPROM.h>

#include "CommandLine.h"

char ssid[16];
char pwd[16];

bool appendCharToCharArray( char *array, int n, char c )
{
    int sz = strlen( array );
    if ( sz + 1 < n ) 
    {
        array[sz] = c;
        array[sz + 1] = '\0';
    }       
    return ( sz + 1 < n );
}

void readEEPROM()
{
   memset(ssid,0,strlen(ssid));
   memset(pwd,0,strlen(pwd));
  
  for (int i = 0; i < 16; ++i)
    {
       appendCharToCharArray(ssid,16,char(EEPROM.read(i)););
    }
  
  for (int i = 16; i < 32; ++i)
    {
       appendCharToCharArray(pwd,16,char(EEPROM.read(i)););
    }
  
  
}

void writeEEPROM(char* setting)
{
    for (int i = 0; i < strlen(setting); ++i)
    {
        EEPROM.write(i, setting[i]);
    }
   EEPROM.commit();
}


void
setup() {
  Serial.begin(115200);

   EEPROM.begin(512);

   readEEPROM();
}

void
loop() {
  bool received = getCommandLineFromSerialPort(CommandLine);      //global CommandLine is defined in CommandLine.h
  if (received) DoMyCommand(CommandLine);
}
