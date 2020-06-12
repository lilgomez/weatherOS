/*LoRa Connections
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
#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

int catavento = 0;
String dir;

//Receive Rain Gauge Data from secondary Arduino
#include <SoftwareSerial.h>
SoftwareSerial virtualPort(6, 7); //RX-6 / TX-7

//BMP280
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme;
int atm = 0;
#define SEALEVELPRESSURE_HPA (1013.25);

//Anemometer
const int m_time = 5;
int wind_ct = 0;
float wind = 0.0;
float maxv = 0;
unsigned long time = 0;
int val = 0;

//DHT11
#include "DHT.h"
#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float maxt = 0;
float mint = 100;
float t = 0;
float h = 0;
float UV_index;

//Timer
int anterior = 0;
float tempo;
int intervalo = 5;


void setup() {

  pinMode(8, INPUT); //Reset
  time = millis();
  Serial.begin(9600);

  dht.begin();


  //LoRa
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //BME280
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }


}
void loop() {
  //Starts serial to receive rain gauge measure
  virtualPort.begin(9600);


  //Reset values when a signal is received from Secundary Arduino
  if (digitalRead(8) == HIGH) {
    mint = 100;
    maxt = 0;
    maxv = 0;

  }







  vento();
  cata();

  if (wind > maxv) {
    maxv = wind;
  } //Max. Wind Speed



  //Read Pressure
  atm = bme.readPressure() / 100.0F;

  //Read DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (t > maxt) {
    maxt = t;
  } //Max Temp.
  if (t < mint) {
    mint = t;
  } //Min Temp

  //UV
  int sensor_value = analogRead(A0);
  float volts = sensor_value * 5.0 / 1024.0;
  float UV_index = volts * 10;

  val  = virtualPort.read() - '0'; //Receive Rain Gauge Measure


  //Timer
  unsigned long tempo_atual = millis();
  float tempo = tempo_atual / 1000;

  if ((tempo - anterior) >= intervalo) {
    anterior = tempo;

    //Serial Sending only for tests
    Serial.print("Vento: ");
    Serial.print(wind);
    Serial.print("Max: ");
    Serial.println(maxv);
    Serial.print("Direção: ");
    Serial.println(dir);
    Serial.print("Chuva (mm): ");
    Serial.println(((float)val * 0.2794), 4); //Rain Gauge pulse count to mm
    Serial. print("Temperatura: ");
    Serial.print(t);
    Serial.print("Max:");
    Serial.print(maxt);
    Serial.print("Min:");
    Serial.println(mint);
    Serial.print("Humidade: ");
    Serial.println(h);
    Serial.print("UV :");
    Serial.println(UV_index);
    Serial.print("Pressão: ");
    Serial.println(atm);

    //Send data by LoRa
    LoRa.beginPacket();
    LoRa.print(wind);
    LoRa.print(";");
    LoRa.print(maxv);
    LoRa.print(";");
    LoRa.print(dir);
    LoRa.print(";");
    LoRa.print(((float)val * 0.2794), 4);
    LoRa.print(";");
    LoRa.print(t);
    LoRa.print(";");
    LoRa.print(maxt);
    LoRa.print(";");
    LoRa.print(mint);
    LoRa.print(";");
    LoRa.print(h);
    LoRa.print(";");
    LoRa.print(UV_index);
    LoRa.print(";");
    LoRa.print(atm);
    LoRa.print(";");
    LoRa.endPacket();









  }



  //End Serial connection every Loop
  //It only worked that way, I don't know why
  virtualPort.end();


}



//Anemometer
void countWind() {
  wind_ct ++;
}

void vento() {
  wind_ct = 0;
  time = millis();
  attachInterrupt(1, countWind, RISING);
  delay(1000 * m_time);
  detachInterrupt(1);
  wind = (float)wind_ct / (float)m_time * 2, 4;
}


//Wind Vane
void cata() {
  catavento = analogRead(A3);
  if (catavento < 80 & catavento > 40) {
    dir = "W";
  } else if (catavento < 150 & catavento > 75) {
    dir = "NO";
  } else if (catavento < 240 & catavento > 180) {
    dir = "N";
  } else if (catavento < 300 & catavento > 250) {
    dir = "SE";
  } else if (catavento < 400 & catavento > 350) {
    dir = "SO";
  } else if (catavento < 520 & catavento > 470) {
    dir = "S";
  } else if (catavento < 595 & catavento > 535) {
    dir = "NE";
  } else if (catavento < 650 & catavento > 600) {
    dir = "E";
  } else if (catavento < 800 & catavento > 700) {
    dir = "S";
  } else if (catavento < 900 & catavento > 830) {
    dir = "SE";
  } else if (catavento < 1000 & catavento > 920) {
    dir = "E";
  }
}
