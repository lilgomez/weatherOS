
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

      //Prints the data separated with a "," so we can Split it later 
      Serial.print(t);
      Serial.print(",");
      Serial.print(maxt);
      Serial.print(",");
      Serial.print(mint);
      Serial.print(",");
      Serial.print(h);
      Serial.print(",");
      Serial.print(wind);
      Serial.print(",");
      Serial.print(dir);
      Serial.print(",");
      Serial.print(maxv);
      Serial.print(",");
      Serial.print(atm);
      Serial.print(",");
      Serial.print(chuva);
      Serial.print(",");
      Serial.print(UV);

    }
  }
}
