WeatherOS V2.0

In this Version a secondary arduino has been added which obtains the hours from an RTC and gives reset to the main arduino, so it is possible to memorize variables such as maximum temperature or the strongest gust of wind and at the end of the day zero these variables.

With the RTC rain gauge readings can also be reset automatically.

This secondary arduino also memorizes the number of pulses of the rain gauge and sends this value per serial to the main arduino, thus avoiding the reading error caused by the delay that is used in reading the anemometer.

The data sent by LoRa are now treated in the receiver, facilitating the handling of the received data, which can be used for the desired purpose only with the use of the individual variables created for each specific value.
