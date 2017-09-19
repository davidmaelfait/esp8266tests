//writing to persistent memory for saving settings
#include <EEPROM.h>

#include "CommandLine.h"

char* ssid;
char* pwd;

void readEEPROM()
{
  byte hiByte = EEPROM.read(diameterAddr);
  byte loByte = EEPROM.read(diameterAddr+1);
  
  diameter = word(hiByte,loByte);
  
  Serial.print("Reading EEPROM: Diameter = ");
  Serial.print(diameter);
  
  hiByte = EEPROM.read(heightAddr);
  loByte = EEPROM.read(heightAddr+1);
  
  height = word(hiByte,loByte);
  
  Serial.print(", height = ");
  Serial.print(height);
  
  hiByte = EEPROM.read(offsetAddr);
  loByte = EEPROM.read(offsetAddr+1);
  
  distanceOffset = word(hiByte,loByte);
  
  Serial.print(", offset = ");
  Serial.println(distanceOffset);
}

void writeEEPROM()
{
  Serial.print("Writing EEPROM: diameter = ");
  Serial.print(diameter);
 
  byte hiByte = highByte(diameter);
  byte loByte = lowByte(diameter);
  
  EEPROM.write(diameterAddr,hiByte);
  EEPROM.write(diameterAddr+1,loByte);
  
  hiByte = highByte(height);
  loByte = lowByte(height);
  
  Serial.print(", height = ");
  Serial.print(height);
  
  EEPROM.write(heightAddr,hiByte);
  EEPROM.write(heightAddr+1,loByte);
  
  Serial.print(", distanceOffset = ");
  Serial.println(distanceOffset);
  
  hiByte = highByte(distanceOffset);
  loByte = lowByte(distanceOffset);
  
  EEPROM.write(offsetAddr,hiByte);
  EEPROM.write(offsetAddr+1,loByte);
}


void
setup() {
  Serial.begin(115200);

   readEEPROM();
}

void
loop() {
  bool received = getCommandLineFromSerialPort(CommandLine);      //global CommandLine is defined in CommandLine.h
  if (received) DoMyCommand(CommandLine);
}
