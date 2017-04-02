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

$res = mysqli_query($conn,"SELECT id FROM users WHERE first_name='" . $_POST["first_name"] . "' AND last_name='" . $_POST["last_name"] . "' AND email='" . $_POST["email"] . "'");
$count  = mysqli_num_rows($res);
if($count > 0) {
	$add = $res->fetch_object()->id."|";
	$result = mysqli_query($conn,"UPDATE users SET sgroup=CONCAT(sgroup, '$add') WHERE id='" . $_COOKIE["id"] . "'");
	echo '<script>window.location.href = "http://localhost:8888/group.php?success=1";</script>';
	die();
} else {
	echo '<script>window.location.href = "http://localhost:8888/group.php?success=0";</script>';
	die();
}
?>
