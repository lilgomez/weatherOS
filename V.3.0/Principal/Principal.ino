/*Ligações LoRa
/* Module SX1278 // Arduino UNO/NANO    
    GND         ->   GND
    Vcc         ->   3.3V
    MISO        ->   D12
    MOSI        ->   D11     
    SLCK        ->   D13
    Nss         ->   D10
    Di00        ->   D2
    RST         ->   D9  
*/
//Bibliotecas LoRa
#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

//Variáveis direção
int catavento = 0;
String dir;

//Pluviómetro
int chuva = 0;

//UV
#include <GUVA-S12SD.h>
GUVAS12SD uv(A0);

//BME280
#include <Adafruit_Sensor.h> 
#include <Adafruit_BME280.h> 
Adafruit_BME280 bme;
int atm = 0;
#define SEALEVELPRESSURE_HPA (1013.25);

//Variáveis anemometro
//m_time define também o intervalo entre os envios LoRa
const int m_time = 5; //Duração da amostra para calcular a velocidade
int wind_ct = 0;
float wind = 0.0;
unsigned long time = 0;
float maxv = 0;

//DHT11
#include "DHT.h"
#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float maxt = 0;
float mint = 100;
float t = 0;
float h = 0;

//Var. gerais
int ct = 0;

void setup() {
  pinMode(8, INPUT); //Reset valores
  time = millis();
  Serial.begin(9600); //Inicia Serial
  dht.begin(); //Inicia DHT11
  //Inicia LoRa
  if (!LoRa.begin(433E6)) {
     Serial.println("Erro LoRa");
     while (1);
  }
  //Inicia BME280
  if (!bme.begin(0x76)) {
     Serial.println("Erro BME280");
     while (1);
  }
 
}

void loop() {

  //Leitura pluviometro
  Wire.requestFrom(2, 1);
  chuva = Wire.read();
  
  //Verifica quando tem de zerar os valores
  if(digitalRead(8) == HIGH){
    if(ct == 0){ //Reset apenas uma vez
      mint = 100;
      maxt = 0;
      maxv = 0;
      ct = 1;
    }
  } else {
    ct = 0;
  }
  
  vento(); //Leitura do anemometro
  cata(); //Leitura do catavento
  
  //Define vento máximo
  if(wind > maxv){
    maxv = wind;
  } 

  //Leitura UV
  float mV = uv.read();
  float uv_index = uv.index(mV);
  
  atm = bme.readPressure() / 100.0F;  //Leitura pressão
  //Leitura DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //Temperatura maxima
  if(t > maxt){
   maxt = t;
  } 
  //Temperatura mínima
  if(t < mint) {
    mint = t;
  } 


//Envio dos valores por Serial
//(Usado apenas durente os testes)
/*
Serial.println(wind); //Vento
Serial.println(maxv); //V. Max
Serial.println(dir); //Direcao
Serial.println(((float)chuva * 0.2794), 4); //Chuva
Serial.println(t); //Temperatura
Serial.println(maxt);
Serial.println(mint);
Serial.println(h); //Humidade
Serial.println(uv_index); //UV
Serial.println(atm); //Pressao
*/

//Envia os valores por LoRa
LoRa.beginPacket();
LoRa.print(wind);
LoRa.print(";");
LoRa.print(maxv);
LoRa.print(";");
LoRa.print(dir);
LoRa.print(";");
LoRa.print(((float)chuva * 0.2794), 4);
LoRa.print(";");
LoRa.print(t);
LoRa.print(";");
LoRa.print(maxt);
LoRa.print(";");
LoRa.print(mint);
LoRa.print(";");
LoRa.print(h);
LoRa.print(";");
LoRa.print(uv_index);
LoRa.print(";");
LoRa.print(atm);
LoRa.print(";");
LoRa.endPacket();

}

//Leitura do anemometro
void countWind() {
  wind_ct ++;
}
void vento() {
  wind_ct = 0;
  time = millis();
  attachInterrupt(1, countWind, RISING);
  delay(1000 * m_time);
  detachInterrupt(1);
  wind = (float)wind_ct / (float)m_time * 2,4;
}

//Leitura do catavento
void cata() { 
 catavento = analogRead(A3);
 if (catavento < 80 & catavento > 40){
  dir = "W";
 } else if (catavento < 150 & catavento > 75) {
  dir = "NO";
 } else if (catavento < 240 & catavento > 180) {
  dir = "N";
 } else if (catavento < 300 & catavento > 250) {
  dir = "SE";
 } else if (catavento < 400 & catavento > 350) {
 dir = "SO";
 } else if (catavento < 520 & catavento > 470){
  dir = "S";
 } else if (catavento < 595 & catavento > 535){
  dir = "NE";
 } else if(catavento < 650 & catavento > 600){
  dir = "E";
 } else if(catavento < 800 & catavento > 700){
  dir = "S";
 } else if(catavento < 900 & catavento > 830){
  dir = "SE";
 } else if(catavento < 1000 & catavento > 920){
  dir = "E";
 }
}
