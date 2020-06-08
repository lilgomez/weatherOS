# weatherOS
This project aims to facilitate the construction of weather stations based in Arduino and LoRa.
With this code you can read the values of an anemometer, a weather vane, a rain gauge, a BME280, a DHT11 and an ultraviolet sensor. These values can then be sent via a LoRa module and received at a station, where the data can be processed as desired.
The project is divided into two arduinos to read the values, this system is still able to reset the values through a RTC.
The reception of the data is very simple, being one of the possible ways to receive the data the use of another arduino.
