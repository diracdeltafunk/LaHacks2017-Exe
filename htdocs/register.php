<?php

$user = 'root';
$password = 'root';
$db = 'calc';
$host = 'localhost';
$port = 3306;

$conn = new mysqli($host, $user, $password, $db, $port);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$first_name = $_POST["first_name"];
$last_name = $_POST["last_name"];
$email = $_POST["email"];
$password = $_POST["password"];
$mode = intval($_POST["mode"]);

$sql = "INSERT INTO users (first_name, last_name, email, password, mode)
VALUES ('$first_name', '$last_name', '$email', '$password', '$mode')";

if ($conn->query($sql) === TRUE) {
	$conn->close();
   	echo '<script>window.location.href = "http://localhost:8888/registration_success.html";</script>';
	die();
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
    $conn->close();
}

?>