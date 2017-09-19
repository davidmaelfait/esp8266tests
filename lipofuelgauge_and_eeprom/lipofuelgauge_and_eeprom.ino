
#include <CLI.h>
#define ESP8266_LED 5

//String str;

CLI_COMMAND(ssidFunc) {
    if (argc != 1) {
        dev->println("Usage: ssid <ssid>");
        return 10;
    }

    dev->println(argv[1]);

    return 0;
}


CLI_COMMAND(connectFunc) {
    dev->println("Welcome to the crius alarm sensor.");
    dev->println();
    dev->printPrompt();
}


void setup() 
{
//  pinMode(ESP8266_LED, OUTPUT);
//
//  Serial.begin(9600);
//  
//  while(!Serial)
//    ;
//
//  Serial.println("serial port ready");
//
//    digitalWrite(ESP8266_LED, HIGH);
    Serial.begin(9600);
    
    CLI.setDefaultPrompt("> ");
    CLI.onConnect(connectFunc);
    
    CLI.addCommand("ssid", ssidFunc);

     CLI.addClient(Serial);
}

void loop() 
{
CLI.process();
//  if(Serial.available() > 0)
//    {
//        if(Serial.findUntil("ssid=","\n"))
//        {
//        
//        str = Serial.readStringUntil('\n');
//        str.replace("ssid=", "");
//        str.replace("\n", "");
//        Serial.print("rx: " +str);
//        }
//    }
}
