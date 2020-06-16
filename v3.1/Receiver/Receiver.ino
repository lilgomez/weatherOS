
//LoRa Libraries
#include <SPI.h>
#include <LoRa.h>

//String for received data
String a;
String b;
String dir;
String d;
String e;
String f;
String g;
String h;
String i;
String j;
String direcao;

//Received data will be converted to float to prevent
//the sending of bad receptions, bacause it may crash the raspberry software. 
float wind;
float maxv;
float mint;
float temp;
float hum;
float Uv;
float atm;
float maxt;
float rain;
float rn;


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
      a = LoRa.readStringUntil(';');

      b = LoRa.readStringUntil(';');

      dir = LoRa.readStringUntil(';');

      d = LoRa.readStringUntil(';');

      e = LoRa.readStringUntil(';');

      f = LoRa.readStringUntil(';');

      g = LoRa.readStringUntil(';');

      h = LoRa.readStringUntil(';');

      i = LoRa.readStringUntil(';');

      j = LoRa.readStringUntil(';');

      
      direc(); //Security method to avoid errors in Raspberry
      
      wind = a.toFloat();
      maxv = b.toFloat();
      temp = e.toFloat();
      maxt = f.toFloat();
      mint = g.toFloat();
      hum = h.toFloat();
      rain = d.toFloat();
      rn = rain / 0.2794;
      atm = j.toFloat();
      
      //Prints the data separated with a "," so we can Split it later 
      Serial.print(temp);
      Serial.print(",");
      Serial.print(maxt);
      Serial.print(",");
      Serial.print(mint);
      Serial.print(",");
      Serial.print(h);
      Serial.print(",");
      Serial.print(wind);
      Serial.print(",");
      Serial.print(direcao);
      Serial.print(",");
      Serial.print(maxv);
      Serial.print(",");
      Serial.print(atm);
      Serial.print(",");
      Serial.print(((float)rn * 0.2794), 4);
      Serial.print(",");
      Serial.print(Uv);
        }
    }
  }



void direc() {
if(dir == "N"){
  direcao = "N";
} else if(dir == "NE"){
  direcao = "NE";  
} else if(dir == "NO"){
  direcao = "NO";
} else if(dir == "O"){
  direcao = "W";
} else if(dir == "E"){
  direcao = "E";
} else if(dir == "SE"){
  direcao = "SE";
} else if(dir == "SO"){
  direcao = "SO";
} else if(dir == "S"){
  direcao = "S";
} else {
  direcao = "Er";
}
}
