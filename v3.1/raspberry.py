import serial
import mysql.connector
#Establish connection with DB
#Please enter here your DB parameters
db_connection = mysql.connector.connect(
  host="localhost",
  user="yourusername",
  passwd="yourpassword",
  database="yourdb"
  )

if __name__ == '__main__':
    #Establish connection with the serial communication with arduino.
    #You man need to replace "/dev/ttyUSB0" to establish connection
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.flush()
    ct = 0
    while True:
        if ser.in_waiting > 0: #Wait for the arduino print
            
            if ct == 0: #First reading will be "LoRa Begin", so we can´t split it
                Received = ser.readline()
                print("Starting...")
                ct = 1
            else: #After the first reading we will receive the station data
                db_cursor = db_connection.cursor()
                Received = ser.readline()
                #Splits the received string, creating a list
                ReceivedList = Received.split(",")
                #We'll use different vars for each element of the list
                Temp = ReceivedList[0]
                MaxT = ReceivedList[1]
                MinT = ReceivedList[2]
                Hum = ReceivedList[3]
                Wind = ReceivedList[4]
                Wd = ReceivedList[5]
                MaxV = ReceivedList[6]
                Atm = ReceivedList[7]
                Rain = ReceivedList[8]
                UV = ReceivedList[9]
                WindD = Wd.decode().strip()
                #The following two lines are used to msntain only one line on the DB
                sqlDelete = "DELETE FROM dados WHERE reset = '1'"
                db_cursor.execute(sqlDelete)
                #Insert the values on the DB
                sql = "INSERT INTO dados(Temp, MinT, MaxT, Wind, Maxv, Rain, Hum, Atm, UV, Dire, reset) VALUES(%s, %s, %s, %s, %s, %s, %s, %s, %s, '%s', %s)"% (Temp, MinT, MaxT, Wind, MaxV, Rain, Hum, Atm, UV, WindD, "1")
                db_cursor.execute(sql)
                db_connection.commit()
                
