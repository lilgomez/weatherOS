WeatherOS v3.0

In this version the serial communication between the main arduino and the secondary arduino was abandoned, as it caused many errors. Now I2C is used.

Interrupt Pin Method to read Rai Gauge pulses caused false readings, now it uses a renewed system to read Rain Gauge Pulses.

The timer used to send the data caused unexpected stops in LoRa, now the delay used in wind calculation has been increased to 5 seconds, allowing the data to continue to be sent every 5 seconds.
This change has also increased the readability of the anemometer, as speeds below 2.4Km/h are now detected.

The way the UV index is obtained has been temporarily changed for testing purposes only.

Some minor bugs have been fixed as well.
