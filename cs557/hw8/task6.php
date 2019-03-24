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

$query = 'delete from library where lname="';
$query .= $_GET["lname"];
$query .= '"';

$result = $conn->query($query);
if(!$result) {die( 'Error in SQL: ' . mysqli_error($conn));}
else {echo 'delete successful';}
/*
*/
?> 
