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

$add = str_replace("\\", "\\\\", $_POST["problem"].":".$_POST["user_answer"].":".$_POST["correct_answer"]."|");

$result = mysqli_query($conn,"UPDATE users SET history=CONCAT(history, '$add') WHERE id='" . $_COOKIE["id"] . "'");

?>
