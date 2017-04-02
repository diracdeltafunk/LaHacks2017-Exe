<?phpphp

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

	$result = mysqli_query($conn,"SELECT sgroup FROM users WHERE id='" . $_COOKIE["id"] . "'");
	$group = $result->fetch_object()->sgroup;
	$entries = explode("|", $group);

	foreach($entries as $prb)
	{
		if($prb != "")
		{
			$add = $_POST["parts"].":".$_POST["exp"].":".$_POST["log"].":".$_POST["trig"].":".$_POST["invtrig"].":".$_POST["number"].":".$_POST["diff"]."|";
			$result = mysqli_query($conn,"UPDATE users SET assign=CONCAT(assign, '$add') WHERE id='" . $prb . "'");
			$result = mysqli_query($conn,"UPDATE users SET score=CONCAT(score, '|') WHERE id='" . $prb . "'");
		}
	}
	echo '<script>window.location.href = "http://localhost:8888/group.php?success=2";</script>';
	die();
?>