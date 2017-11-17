/*
Sistema de sensor de temperatura embarcado.

------------------------------------------------

Autor: Weldisson da Silva Araujo.
Email: weldisson.araujo@icloud.com
Tecnologias utilizadas: NodeMCU ESP-12e, DHT-22, App Blynk e API Thingspeak, Arduino IDE.

Objetivo: Enviar a temperatura e humidade para o thingspeak Server e E-mail utilizando o Blynk.

instalar Arduino IDE.
instalar a placa NODEMCU: http://arduino.esp8266.com/stable/package_esp8266com_index.json
Incluir biblioteca DHT, Time, Blynk e esp8266WiFi.

*/

#define BLYNK_PRINT Serial
// Bibliotecas do arduino IDE
#include <DHT.h>  
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <Time.h>
#include <TimeAlarms.h>
// chave do thingspeak
String apiKey = "";  // a chave se encontra no site www.thingspeak.com
// chave do Blynk   
char auth[] = ""; // a chave se encontra no APP Blynk mais informações www.blynk.io
// conecta ao wifi
const char *ssid =  "ssid";     //caso precise alterar a rede coloque aqui o nome da rede SSID
const char *pass =  "password";    //caso precise alterar a rede coloque aqui a senha da rede
// conecta ao servidor thingspeak
const char* server = "api.thingspeak.com";
// define o pino do sensor DHT
#define DHTPIN 2       
 
DHT dht(DHTPIN, DHT22);
BlynkTimer timer;
WiFiClient client;


void setup() 
{
    // inicia as portas serial1 e serial
       Serial1.begin(9200);
       Serial.begin(115200);
       delay(50);
       dht.begin(); //inicia o sensor
       Serial.println("Connecting to "); // conecta a rede wifi  na porta serial
       Serial.println(ssid); 
     
         Blynk.begin(auth ,ssid, pass); // conecta o blynk a rede wifi 
      Serial.println("Connecting to blynk");
      Serial.println("");
      Serial.println("WiFi connected");
}
void contador(){

    Serial.println("iniciando contador");
      delay(1200000); // contador de 20 minutos em ms
     Serial.println("aguardou 20 minuto "); 
     setup();
   }
void sends(){
      
      Blynk.run();// inicia o blynk
      timer.run(); // inicia o timer
      float h = dht.readHumidity(); // leitura da humidade
      float t = dht.readTemperature(); // leitura da temperatura 
      float maxtemp = 25;                     // temperatura maxima      
              delay(50);
                if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed toy read from DHT sensor!");
                      return;
                 }
                         if (client.connect(server,80))                                                  
                      {  
              // envia a temperatura e humidade para o thingspeak...
                             delay(50);
                             String postStr = apiKey;
                             postStr +="&field1="; 
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                             Blynk.virtualWrite(V1, dht.readTemperature()); // envia a temperatura para o app blynk...
               // envia a temperatura para porta serial ...
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                          
                           if(t >= maxtemp){ // envia a temperatura para o thingspeak e email caso a temperatura for acima de 25 graus
                               delay(50);
                                  client.connect(server,80);
                                  String postStr = apiKey;
                                    postStr +="&field1="; 
                                    postStr += String(t);
                                    postStr +="&field2=";
                                    postStr += String(h);
                                    postStr += "\r\n\r\n";
                                  client.print("POST /update HTTP/1.1\n");
                                  client.print("Host: api.thingspeak.com\n");
                                  client.print("Connection: close\n");
                                  client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                                  client.print("Content-Type: application/x-www-form-urlencoded\n");
                                  client.print("Content-Length: ");
                                  client.print(postStr.length());
                                  client.print("\n\n");
                                  client.print(postStr);
                                  Serial.println("%. Send to email.");  
                                  Blynk.email("seuemail@mail.com", "Alerta! SALA DE SERVIDOR  - TEMPERATURA ALTA! ", "Favor alertar aos gestores que a temperatura da sala chegou a 25 Graus Celcius.");
                               //   timer.setInterval(120000L, contador);
                                  contador();
                                   delay(50);}
                             }//endif            
}//endsend
void loop() 
{
  sends();
  delay(1000);
}
