<?php
//Please enter here your DB parameters
$servername = "localhost";
$username = "!!!yourusername";
$password = "!!!yourpassword";
$dbname = "!!!yourdb";

//Establish Connection
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

    
//Gets the data from the MySQL DB
$sql = "SELECT Temp, MaxT, MinT, Wind, Maxv, Dire, Rain, Hum, Atm, UV FROM dados";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
while($row = $result->fetch_assoc()) {

//Prints the page content
echo "<h1>Weather OS</h1>";
echo "Temperature:".$row["Temp"]."&nbsp Min:".$row["MinT"]."&nbsp Max:".$row[MaxT]."<br>";
echo "Humidity:".$row["Hum"]."<br>";
echo "Wind:".$row["Wind"]."&nbsp Dir:".$row["Dire"]."&nbsp Max:".$row["Maxv"]."<br>";
echo "Rain:".$row["Rain"]."<br>";
echo "Pressure:".$row[Atm]."<br>";
echo "UV:".$row[UV]."<br>";
}
  
} else {
    echo "0 results";
}
$conn->close();
?>
