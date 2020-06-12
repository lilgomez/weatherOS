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

//Wind vane var.
int catavento = 0;
String dir;

//Raing Gauge Vars.
int rain = 0;

//BMP280
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme;
int atm = 0;
#define SEALEVELPRESSURE_HPA (1013.25);

//Anemometer
int wind_ct = 0;
float wind = 0.0;
unsigned long time = 0;
float maxv = 0;

//DHT11
#include "DHT.h"
#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float t = 0;
float h = 0;

//UV
float UV_index;

//Timer to send data
int anterior = 0;
float tempo;
int intervalo = 5;


void setup() {
  time = millis();
  Serial.begin(9600);
  pinMode(8, INPUT); //Rain Gauge Pin
  dht.begin();


  //Starting Lora
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //Starting BME280
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }


}

void loop() {

  vento(); //Anemometer
  cata();  //Wind Vane
  chuva(); //Rain Gauge

  //Pressure reading
  atm = bme.readPressure() / 100.0F;

  //DHT11 Reading
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //UV Reading
  int sensor_value = analogRead(A0);
  float volts = sensor_value * 5.0 / 1024.0;
  float UV_index = volts * 10;

  //Timer to send data
  unsigned long tempo_atual = millis();
  float tempo = tempo_atual / 1000;
  if ((tempo - anterior) >= intervalo) {
    anterior = tempo;


    //Send data by LoRa
    LoRa.beginPacket();


    LoRa.print("Vento: ");
    LoRa.print(wind);
    LoRa.print("Direção: ");
    LoRa.println(dir);
    LoRa.print("Chuva (mm): ");
    LoRa.println(((float)rain * 0.2794), 4);//Convert raingauge pulse count to mm
    LoRa. print("Temperatura: ");
    LoRa.print(t);
    LoRa.print("Humidade: ");
    LoRa.println(h);
    LoRa.print("UV :");
    LoRa.println(UV_index);
    LoRa.print("Pressão: ");
    LoRa.println(atm);
    LoRa.endPacket();

  }

}


//Anemometer reading
void countWind() {
  wind_ct ++;
}

void vento() {
  wind_ct = 0;
  time = millis();
  attachInterrupt(1, countWind, RISING);
  delay(1000);
  detachInterrupt(1);
  wind = (float)wind_ct / 1000 * 2, 4;
}

//Rain Gauge Reading

void chuva() {
  if (digitalRead(8) == HIGH) {
    rain++;
  }

}

//Reads wind direction
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
