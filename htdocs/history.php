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
            <li><a id="history" href="history.html" style="display:none">History</a></li>
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
    	<div class="row" style="padding-top:100px">
				<table class="table">
					<thead>
						<tr>
							<!--<th style="font-size:20px">#</th>-->
							<th style="font-size:20px">Problem</th>
							<th style="font-size:20px">My answer</th>
							<th style="font-size:20px">Correct answer</th>
						</tr>
					</thead>
					<tbody>
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


							$result = mysqli_query($conn,"SELECT history FROM users WHERE id='" . $_COOKIE["id"] . "'");
							$hist = $result->fetch_object()->history;
							$entries = array_reverse(explode("|", $hist));
							$cnt = 1;
							foreach($entries as $prb)
							{
								$a = explode(":", $prb);
								if($a[0] != "")
								{
									if($a[1] == $a[2])
										$class = "success";
									else
										$class = "danger";
									echo "<tr class='$class'>";
									# echo<th style=\"font-size:20px; text-align:center; vertical-align:middle;\" scope=\"row\">$cnt</th>";
									echo "<td style=\"font-size:20px\">$a[0]</td>";
									echo "<td style=\"font-size:20px; vertical-align:middle;\">$a[1]</td>";
									echo "<td style=\"font-size:20px; vertical-align:middle;\"\">$a[2]</td>";
									echo "</tr>";
									$cnt += 1;
								}
							}
						?>
					</tbody>
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

