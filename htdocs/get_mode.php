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
$result = mysqli_query($conn,"SELECT mode FROM users WHERE id='" . $_COOKIE["id"] . "'");
echo $result->fetch_object()->mode;
?>