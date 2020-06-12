
//LoRa Libraries
#include <SPI.h>
#include <LoRa.h>

//Strings
String t;
String mint;
String maxt;
String h;
String wind;
String maxv;
String dir;
String atm;
String UV;
String chuva;

void setup() {

  Serial.begin(9600);



  //Starting LoRa
  while (!Serial);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);



  }
}

void loop() {

  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    // read packet
    while (LoRa.available()) {

      //Here we have the data that can be processed as desired
      wind = LoRa.readStringUntil(';');

      maxv = LoRa.readStringUntil(';');

      dir = LoRa.readStringUntil(';');

      chuva = LoRa.readStringUntil(';');

      t = LoRa.readStringUntil(';');

      maxt = LoRa.readStringUntil(';');

      mint = LoRa.readStringUntil(';');

      h = LoRa.readStringUntil(';');

      UV = LoRa.readStringUntil(';');

      atm = LoRa.readStringUntil(';');


      Serial.println("--------------");
      Serial.print("Temperatura: ");
      Serial.print(t);
      Serial.print(" Max: ");
      Serial.print(maxt);
      Serial.print(" Min: ");
      Serial.println(mint);
      Serial.print("Humidade(%): ");
      Serial.println(h);
      Serial.print("Vento(Km/h): ");
      Serial.print(wind);
      Serial.print(" ");
      Serial.print(dir);
      Serial.print(" Max: ");
      Serial.println(maxv);
      Serial.print("Pressao(hPa): ");
      Serial.println(atm);
      Serial.print("Chuva(mm): ");
      Serial.println(chuva);
      Serial.print("Indice UV: ");
      Serial.println(UV);
      Serial.println("--------------");

    }
  }
}
