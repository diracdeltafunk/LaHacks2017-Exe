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

$result = mysqli_query($conn,"SELECT * FROM users WHERE email='" . $_POST["email"] . "' and password = '". $_POST["password"]."'");
$count  = mysqli_num_rows($result);
if($count == 0) {
	$conn->close();
   	echo '<script>window.location.href = "http://localhost:8888/login_fail.html";</script>';
	die();
} else {
	$conn->close();
	setcookie("id", $result->fetch_object()->id, time() + (86400 * 30), "/");
   	echo '<script>window.location.href = "http://localhost:8888/hi.php";</script>';
	die();
}

?>