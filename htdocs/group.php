<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" href="../../favicon.ico">

    <title>Starter Template for Bootstrap</title>

    <!-- Bootstrap core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom styles for this template -->
    <link href="starter-template.css" rel="stylesheet">

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>

  <body>

    <nav class="navbar navbar-inverse navbar-fixed-top">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="hi.php">Classroom Of The Future</a>
        </div>
        <div id="navbar" class="collapse navbar-collapse">
          <ul class="nav navbar-nav">
            <li class="active"><a href="#">Home</a></li>
            <li><a href="#about">About</a></li>
            <li><a href="#contact">Contact</a></li>
            <li><a id="register" href="register_form.html">Register</a></li>
            <li><a id="history" href="history.php" style="display:none">History</a></li>
            <li><a id="group" href="group.php" style="display:none">Student group</a></li>
          </ul>
          <form id="login_form" class="navbar-form navbar-right" action="login.php" method="POST">
            <div class="form-group">
              <input type="text" placeholder="Email" name="email" class="form-control">
            </div>
            <div class="form-group">
              <input type="password" placeholder="Password" name="password" class="form-control">
            </div>
            <button type="submit" class="btn btn-success">Sign in</button>
          </form>
          <a id="logout" class="navbar-brand navbar-right" href="logout.php" style="display:none">Logout</a>
        </div><!--/.nav-collapse -->
      </div>
    </nav>

    <div class="container">
    	<div class="row" style="padding-top:50px">
    		<div class="col-md-3">
				<h2>Student group:</h2>
				<ul style="padding-top:20px" class="list-group">
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


							$result = mysqli_query($conn,"SELECT sgroup FROM users WHERE id='" . $_COOKIE["id"] . "'");
							$group = $result->fetch_object()->sgroup;
							$entries = explode("|", $group);
					
							foreach($entries as $prb)
							{
								if($prb != "")
								{
									$res = mysqli_query($conn,"SELECT * FROM users WHERE id='" . $prb . "'");
									$obj = $res->fetch_object(); 
									$first_name = $obj->first_name;
									$last_name = $obj->last_name;
									echo "<li style=\"font-size:20px\"> $first_name" . " $last_name </li>";
								}
							}

					?>
				</ul>
			</div>
			<div class="col-md-4">
				<h2>Configure assignment:</h2>
				<div style="padding-top:20px">
					<button type="button" id="button1" class="btn btn-primary">Integration by parts</button>
						<button type="button" id="button2" class="btn btn-primary">Exponentiation</button>
					<div style="padding-top:15px">
						<button type="button" id="button3" class="btn btn-primary">Logarithms</button>
						<button type="button" id="button4" class="btn btn-primary">Trigonometry</button>
					</div>
					<div style="padding-top:15px">
						<button type="button" id="button5" class="btn btn-primary">Inverse triginometry</button>
					</div>
				</div>
				<div style="padding-top:15px"  class="dropdown">
				  <button id="down" class="btn btn-primary" type="button" data-toggle="dropdown">Difficulty
				  <span class="caret"></span></button>
				  <ul class="dropdown-menu">
					<li><a id="diff1" href="#">1</a></li>
					<li><a id="diff2" href="#">2</a></li>
					<li><a id="diff3" href="#">3</a></li>
					<li><a id="diff4" href="#">4</a></li>
					<li><a id="diff5" href="#">5</a></li>
				  </ul>
				</div>
				<form style="padding-top:30px" action="add_assignment.php" method="POST">
					<div class="form-group">
					  <label class="col-2 col-form-label">Number of problems</label>
					  <div class="col-10">
						<input style="width:200px" class="form-control" type="number" value="" name="number">
						<input id="hidd1" type="hidden" value="0" name="parts">
						<input id="hidd2" type="hidden" value="0" name="exp">
						<input id="hidd3" type="hidden" value="0" name="log">
						<input id="hidd4" type="hidden" value="0" name="trig">
						<input id="hidd5" type="hidden" value="0" name="invtrig">
						<input id="diff" type="hidden" value="1" name="diff">
					  </div>
					</div>
					<button id="add" type="submit" class="btn btn-success">Submit</button>
				
				</form>
				<?
					if(isset($_GET["success"]))
					{
						if($_GET["success"] == 2)
							echo '
								<div style="padding-top:30px; padding-right:30px;">
									<div style="width:300px" class="alert alert-success" role="alert">
										Assignment added successfully!
									</div> 
								</div>	';

					}
				?>
			</div>
			<div class="col-md-4">
				<div class="container">
					<h2>Add student:</h2>
				</div>
				<div class="container">
					<form style="padding-top:20px" action="add_student.php" method="POST">

						<div class="form-group">
						  <label class="col-2 col-form-label">First Name</label>
						  <div class="col-10">
							<input style="width:400px" class="form-control" type="text" value="" name="first_name">
						  </div>
						</div>
						<div class="form-group">
						  <label class="col-2 col-form-label">Last Name</label>
						  <div class="col-10">
							<input style="width:400px" class="form-control" type="text" value="" name="last_name">
						  </div>
						</div>
						<div class="form-group">
						  <label class="col-2 col-form-label">Email</label>
						  <div class="col-10">
							<input style="width:400px" class="form-control" type="email" value="" name="email">
						  </div>
						</div>
						<button id="add" type="submit" class="btn btn-success">Submit</button>
					
					</form>
				</div>
				<?
					if(isset($_GET["success"]))
					{
						if($_GET["success"] == 1)
							echo '
								<div style="padding-top:30px" class="container">
									<div style="width:400px" class="alert alert-success" role="alert">
										Student added successfully!
									</div> 
								</div>	';
						if($_GET["success"] == 0)
							echo '
								<div style="padding-top:30px" class="container">
									<div style="width:400px" class="alert alert-danger" role="alert">
										Student not found :(
									</div> 
								</div>	';

					}
				?>
			</div>	
		</div>
		<div class="row" style="padding-top:50px">
			<table style="padding-top:20px; width:auto; font-size:20px;" class="table table-bordered">
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


					$result = mysqli_query($conn,"SELECT sgroup FROM users WHERE id='" . $_COOKIE["id"] . "'");
					$group = $result->fetch_object()->sgroup;
					$entries = explode("|", $group);
			
					$mx = 0;
					if(sizeof($entries) > 0) {
						$res = mysqli_query($conn, "SELECT * FROM users WHERE id='" . $entries[0] . "'");
						$mx = substr_count($res->fetch_object()->score, '|');
					}
			
					echo "<thead>";
						echo "<th> Name </th>";
						for($i = 1; $i <= $mx; $i += 1)
							echo "<th> Task $i </th>";
					echo "</thead>";
					$cnt = 1;
					foreach($entries as $prb)
					{
						if($prb != "")
						{
							$res = mysqli_query($conn, "SELECT * FROM users WHERE id='" . $prb . "'");
							$obj = $res->fetch_object();
							$str = $obj->score;
							$first_name = $obj->first_name;
							$last_name = $obj->last_name;
							$mx = substr_count($str, '|');
							$scores = explode("|", $str);
							array_pop($scores);
							echo "<tr>";
							$cnt += 1;
							$sss = $first_name . " " . $last_name;
							echo "<td> $sss </td>";
				#			foreach($scores as $num)
							for($i = 0; $i < $mx; $i += 1)
								if($scores[$i] != "")
									echo "<td style=\"text-align:center\"> $scores[$i] </td>";
								else
									echo "<td> </td>";
							echo "</tr>";
						}
					}

				?>
			</table>
		</div>
    </div>

    

    <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
    <script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}});</script>
    <script src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"> </script>
    <script src="js/my.js"></script>
    <script src="js/bootstrap.min.js"></script>
    <script src="//cdnjs.cloudflare.com/ajax/libs/jquery-cookie/1.4.1/jquery.cookie.min.js">
  </body>
</html>

