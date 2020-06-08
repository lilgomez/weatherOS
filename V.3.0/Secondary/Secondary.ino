
#include <Wire.h>
#include <virtuabotixRTC.h>
//RTC Pins
//CLK -> 6 , DAT -> 7, Reset -> 8
virtuabotixRTC myRTC(6, 7, 8);

//Reset main arduino
int minutes = 0;
int hours = 0;


int chuva = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT); //Pin to reset main arduino
  digitalWrite(2, LOW);

  // seconds, minutes, hours, day of the week, day of the month, month, year
  //Uncomment for set correct time.
  //myRTC.setDS1302Time(55, 6, 18, 2, 8, 6, 2020);

  Wire.begin(2);
  Wire.onRequest(sendrain);

}

void loop() {


  attachInterrupt(1, count, RISING); //If rain gauge is accionated it runs the counter.
  detachInterrupt(1);

  //RTC Readings
  myRTC.updateTime();

  hours = myRTC.hours;
  minutes = myRTC.minutes;

  //Main Arduino Reset
  if (hours == 23 & minutes == 59) {
    digitalWrite(2, HIGH);
    chuva = 0;
  } else {
    digitalWrite(2, LOW);
  }


}


//Counter
void count() {
  chuva++;
  delay(10); //Evita que conte mais que um pulso
}

//Send rain gauge data by I2C
void sendrain() {
  uint8_t Buffer[1];
  Buffer[0] = chuva;
  Wire.write(Buffer, 1);
}
