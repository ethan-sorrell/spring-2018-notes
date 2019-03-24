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

$query = 'Select * from ' . $_POST["table"];
$result = $conn->query($query);
if(!$result) {die( 'Error in SQL: ' . mysqli_error($conn));}

$all_attributes = array();

echo '<table class = "data-table">
        <tr class = "data-heading">';
while ($attribute = $result->fetch_field()) {
  echo '<td>' . $attribute->name . '</td>';
  array_push($all_attributes, $attribute->name);
}

echo '</tr>';

while ($row = $result->fetch_array()) {
  echo '<tr>';
  foreach($all_attributes as $item) {
    echo '<td>' . $row[$item] . '</td>';
  }
  echo '</tr>';
}
echo '</table>';
?> 
