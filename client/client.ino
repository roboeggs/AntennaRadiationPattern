#include <ESP8266WiFi.h>
#include <Servo.h> 

char* host = "192.168.4.1";

// количество шагов на 1 оборот
#define STEP_ROUND 200



// Пин для сервопривода
#define servoPin 4

// номер входа, подключенный к кнопке
#define buttonPin 5

// для остановки двигателя
#define stop_servo 400

#define rep 1

#define retention 2

// переменная хранения времени (unsigned long)
uint32_t myTimer1, myTimer2, term, original_time;

// Создаем объект
Servo Servo1;

/*установка в начало*/
void set_begin(){
   Servo1.write(0);
   delay(stop_servo);
   while(!digitalRead(buttonPin));
    delay(retention);
   while(digitalRead(buttonPin));
      delay(retention);
   Servo1.write(90);
   delay(stop_servo);            // для остановки двигателя
}

void get_time(){
  set_begin(); // установка в начальное положение
   Servo1.write(1560);
   // мы в зоне 0
   while(!digitalRead(buttonPin))
    delay(rep);
   // ждем выхода в зону 1
   while(digitalRead(buttonPin))
    delay(rep);
   // начнем отчет времени
   myTimer1 = micros();
   // ждем зону 1
   while(!digitalRead(buttonPin))
    delay(rep);
   // ждем зону 0
   while(digitalRead(buttonPin))
    delay(rep);
   // ждем зону 1
   while(!digitalRead(buttonPin))
    delay(rep);
   // ждем зону 0
   while(digitalRead(buttonPin))
    delay(rep);
   // считаем пройденное время
   original_time = micros() - myTimer1;
   Servo1.write(180);
   delay(stop_servo);            
   Servo1.write(90);
}

void setup() {
  Serial.begin(115200);
  Servo1.attach(servoPin);
  pinMode(buttonPin, INPUT);
  Serial.println();
  Serial.print("time: "); 
  get_time();
  Serial.println(original_time);
  term =  original_time / STEP_ROUND;
  Serial.print("term: ");
  Serial.println(term);
  WiFi.mode(WIFI_STA);
  WiFi.begin("antenna", "192837465");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
}

void loop() {
  String response = "";
  WiFiClient client;
  if (client.connect(host, 8888))
  {
  // we are connected to the host!
    Serial.print("Conneccted to host: ");
    Serial.println(host);
    //client.println(String(WiFi.RSSI()));

    //Serial.println("[Response:]");
  }
  
  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {

  }
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()){
    char ch = static_cast<char>(client.read());
    response += ch;
  }
  client.flush();
  if(response == "auto\n"){
    set_begin();
    Servo1.write(1560);
    for(int i = 0; i < STEP_ROUND; i++){
      Serial.print("i = ");
      Serial.println(i);
      myTimer2 = micros();
      client.print(String(WiFi.RSSI()));
      while(micros() - myTimer2 < term)
         delay(rep);
    }
    Servo1.write(180);
    delay(stop_servo);            
    Servo1.write(90);
    client.print("\n");
  }else{
    client.println(String(WiFi.RSSI()));
  }
  Serial.println("[Response:]");
  Serial.println(response);

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  delay(500);
}
