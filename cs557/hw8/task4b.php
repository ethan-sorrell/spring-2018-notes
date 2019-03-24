<?php
$servername = "cs-sql2014.ua-net.ua.edu";
$username = "esorrell";
$password = "11610311";

// Create connection
$conn = new mysqli($servername, $username, $password);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
mysqli_select_db($conn, 'esorrell');

$query = 'insert into library values("';
$query .= $_GET['address'];
$query .= '", "';
$query .= $_GET["city"];
$query .= '", "';
$query .= $_GET["state"];
$query .= '", ';
$query .= $_GET["zip"];
$query .= ', "';
$query .= $_GET["name"];
$query .= '", ';
$query .= $_GET["capacity"];
$query .= ', ';
$query .= $_GET["labID"];
$query .= ');';

$result = $conn->query($query);
if(!$result) {die( 'Error in SQL: ' . mysqli_error($conn));}
else {echo 'table inserted';}
?> 
