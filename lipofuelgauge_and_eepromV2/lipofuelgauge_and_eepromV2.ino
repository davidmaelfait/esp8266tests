//writing to persistent memory for saving settings
#include <EEPROM.h>
#include "MAX17043.h"
#include "Wire.h"
#include "CommandLine.h"

const char* ssidCommandToken = "ssid";
const char* pwdCommandToken = "pwd";
const char* battCommandToken = "batt";

char ssid[16];
char pwd[16];



MAX17043 batteryMonitor;

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

  char c;
  for (int i = 0; i < 16; ++i)
    {
      c = char(EEPROM.read(i));
        
        if(c=='\0')
          break;
      
        appendCharToCharArray(ssid,16,c);
    }
  
  for (int i = 0; i < 16; ++i)
    {
        c = char(EEPROM.read(i+16));
        
        if(c=='\0')
          break;
      
       appendCharToCharArray(pwd,16,c);
    }
  
  
}

void writeSSID(char* new_ssid)
{
    for (int i = 0; i <= strlen(new_ssid); ++i)
    {
        //print2("\nssid ", new_ssid[i]);
        EEPROM.write(i, new_ssid[i]);
    }
   EEPROM.commit();
}

void writePWD(char* new_pwd)
{
    for (int i = 0; i <= strlen(new_pwd); ++i)
    {
      //print2("\nssid ", new_pwd[i]);
        EEPROM.write(16+i, new_pwd[i]);
    }
   EEPROM.commit();
}


char* ssidCommand()
{
  char* arg = readWord();
  
  if(arg!=NULL) //ssid arg given => now save new ssid
  {
    writeSSID(arg);
     return arg;
  }
   else
    return ssid;  
}

char* pwdCommand()
{
char* arg = readWord();
  
  if(arg!=NULL) //ssid arg given => now save new ssid
  {
    writePWD(arg);
     return arg;
  }
  else 
   return pwd;
 
}

void battCommand(char* reply)
{

  float cellVoltage = batteryMonitor.getVCell();
   strcat(reply, "Voltage: ");

  char cv[10];
  dtostrf(cellVoltage, 4,1,cv);  
  
   strcat(reply,cv);
   strcat(reply, "V , ");

  float stateOfCharge = batteryMonitor.getSoC();
   strcat(reply, "State of charge: ");

   char soc[10];
    dtostrf(stateOfCharge, 4,1,soc);  
   strcat(reply, soc);
   strcat(reply, "%"); 
}


bool DoMyCommand(char * commandLine) 
{
  char* result;

  char * ptrToCommandName = strtok(commandLine, delimiters);

  if (strcmp(ptrToCommandName, ssidCommandToken) == 0) 
  {                   
    result = ssidCommand();
  } 
  else if (strcmp(ptrToCommandName, pwdCommandToken) == 0) 
  {           
      result = pwdCommand();                                     
   } 
   else if (strcmp(ptrToCommandName, battCommandToken) == 0) 
  {   
       result = new char[50]; 
      battCommand(result);                                     
   } 
    else 
    {
      result = new char[50]; 
      ucCommand(ptrToCommandName,result);
    } 

     print2("\r\n>", result);
     // delete[] result;
}

void setup() {
  Wire.begin(); 
  
  Serial.begin(115200);

   EEPROM.begin(512);

   readEEPROM();

  batteryMonitor.reset();
  batteryMonitor.quickStart();
  delay(1000);

    Serial.println("hello");
    Serial.print(">");
}

void loop() {
  bool received = getCommandLineFromSerialPort(CommandLine);      //global CommandLine is defined in CommandLine.h
  if (received)
  {
      DoMyCommand(CommandLine);
      Serial.print(">");
  }
}
