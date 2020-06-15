WeatherOS v3.1

In this version, a possible way to treat the data received by the weather station is demonstrated.

The receiver code has been changed to send the data to a raspberry pi where it is then managed.

The Arduino sends the data to the raspberry pi via Usb by a Serial communication.

In "raspberry.py" the data is received and sent to a MySQL database, which can be hosted in the raspberry pi itself.

In this version a very simple php page was also included to show the database data.