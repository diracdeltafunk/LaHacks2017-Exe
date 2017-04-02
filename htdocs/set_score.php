<?

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
$result = mysqli_query($conn,"SELECT score FROM users WHERE id='" . $_COOKIE["id"] . "'");
$old_str = $result->fetch_object()->score;
$old_arr = explode("|", $old_str);
$old_arr[$_POST["ind"]] = $_POST["score"];
$add = join('|', $old_arr);

$result = mysqli_query($conn,"UPDATE users SET score='$add' WHERE id='" . $_COOKIE["id"] . "'");

?>