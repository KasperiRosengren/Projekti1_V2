<?php
$servername = "localhost";
$dbname = "RFID";
$username = "admin";
$password = "adminsalasana";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT Tila FROM Tila WHERE LAITE_idLAITE = 2 ORDER BY idTila DESC LIMIT 1;";

if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $tila = $row["Tila"];

    echo $tila;
    }
    $result->free();
}

$conn->close();
?> 
