
#include <Wire.h>
#include <virtuabotixRTC.h>
//Define pinos RTC
//CLK -> 6 , DAT -> 7, Reset -> 8
virtuabotixRTC myRTC(6, 7, 8);

//Reset arduino principal
int minutes = 0;
int hours = 0;

//Variaveis leitura pluviometro
int chuva = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT); //Pino para dar reset ao outro arduino
  digitalWrite(2, LOW);
  
  //Define o tempo atua (comentar em caso de as horas estarem certas);
  // seconds, minutes, hours, day of the week, day of the month, month, year

  //myRTC.setDS1302Time(55, 6, 18, 2, 8, 6, 2020);

  Wire.begin(2);
  Wire.onRequest(sendrain);
  
}

void loop() {
  
  //Verififica se o pluviometro foi acionado
  attachInterrupt(1, count, RISING); //Caso tenha sido ativado ativa o contador
  detachInterrupt(1);

   //Lê o RTC
   myRTC.updateTime();

   //Obtem o tempo atual
   hours = myRTC.hours;
   minutes = myRTC.minutes;

  //Verifica quando tem de dar reset
  if(hours == 23 & minutes == 59){
    digitalWrite(2, HIGH);
    chuva = 0;
  } else {
    digitalWrite(2, LOW);
  }


}


//Contador do pluviometro
void count(){
  chuva++;
  delay(10); //Evita que conte mais que um pulso
  }

void sendrain(){
 uint8_t Buffer[1]; 
 Buffer[0]=chuva;
 Wire.write(Buffer, 1);
}
