#include <ESP8266WiFi.h>

WiFiServer server(8888);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  setupWiFi();                // создаем точку доступа
  server.begin();
  Serial.println();
}



void loop() {
 WiFiClient client = server.available();
  
  if (client) {   
    while(client.connected()){
      while(client.available()>0){
        // read data from the connected client
          Serial.write(client.read()); 
      }
      
      //Send Data to connected client
      while(Serial.available()>0)
      {
        client.print(Serial.readString());
      }
    }
    client.stop();
  }
}    

void setupWiFi() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("antenna", "192837465");
}
