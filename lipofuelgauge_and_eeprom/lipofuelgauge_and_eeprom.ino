#define ESP8266_LED 5

String str;

void setup() 
{
  pinMode(ESP8266_LED, OUTPUT);

  Serial.begin(9600);
  
  while(!Serial)
    ;

  Serial.println("serial port ready");

    digitalWrite(ESP8266_LED, HIGH);
}

void loop() 
{


  if(Serial.available() > 0)
    {
        if(Serial.findUntil("ssid=","\n"))
        {
        
        str = Serial.readStringUntil('\n');
        str.replace("ssid=", "");
        str.replace("\n", "");
        Serial.print("rx: " +str);
        }
    }
}
