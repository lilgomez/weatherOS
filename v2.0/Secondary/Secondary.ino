


// RTC
//CLK -> 6 , DAT -> 7, Reset -> 8
#include <virtuabotixRTC.h>

virtuabotixRTC myRTC(6, 7, 8);

//Serial to send Rain Gaude Count
#include <SoftwareSerial.h>
SoftwareSerial virtualPort(10, 11);

//RTC var.
int minutes = 0;
int hours = 0;
int pres = 0;

//Rain Gauce Var.
int chuva = 0;
int chuva_ct = 0;


void setup() {



  pinMode(2, OUTPUT); //Pin to Reset Main Arduino
  digitalWrite(2, LOW);

  //Uncomment to set current time
  // seconds, minutes, hours, day of the week, day of the month, month, year

  //myRTC.setDS1302Time(55, 10, 16, 5, 19, 3, 2020);

}

void loop() {
  virtualPort.begin(9600);
  //Rain Gauge counter
  attachInterrupt(1, count, RISING); //Caso tenha sido ativado ativa o contador
  detachInterrupt(1);

  //RTC Reading
  myRTC.updateTime();

  hours = myRTC.hours;
  minutes = myRTC.minutes;

  //Resets Main Arduino and Rain Gauge Count.
  if (hours == 23 & minutes == 59) {
    digitalWrite(2, HIGH);
    chuva = 0;
  } else {
    digitalWrite(2, LOW);
  }


  virtualPort.print(chuva) + '0'; //Sends the reading


  virtualPort.end();



}

//Rain Gauge Counter
void count() {
  chuva_ct = chuva;
  chuva = chuva_ct + 1;
  delay(10);
}
