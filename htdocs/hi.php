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
            <li class="dropdown"><a class="dropdown-toggle" id="assigns" data-toggle="dropdown" href="#" style="display:none">Assignments<span class="caret"></span></a>
            	<ul class="dropdown-menu">
					<?php
						$user = 'root';
						$password = 'password';
						$db = 'calc';
						$host = 'localhost';
						$port = 3306;

						$conn = new mysqli($host, $user, $password, $db, $port);
						// Check connection
						if ($conn->connect_error) {
							die("Connection failed: " . $conn->connect_error);
						}


						$result = mysqli_query($conn,"SELECT assign FROM users WHERE id='" . $_COOKIE["id"] . "'");
						$data = $result->fetch_object()->assign;
						$entries = explode("|", $data);
						array_pop($entries);
						$cnt = 0;
						foreach($entries as $prb)
						{
							$a = explode(":", $prb);
							$sz = sizeof($a);
							$cnt1 = $cnt + 1;
							echo "<li><a href=\"http://localhost:8888/assignment.php?num=$cnt\">Assignment $cnt1 </a></li>";
							$cnt += 1;
						}
					?>
				</ul>
            </li>
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

      <div class="starter-template">
        <p class="lead" style="font-size:40px">Select the topics you want to practice and the difficulty level.<br> Good luck!</p>
      </div>

    </div><!-- /.container -->

    <div class="container">

		<form>
			<div class="form-group">
			  <div class="col-10">
				<input id="hidd1" type="hidden" value="0" name="parts">
				<input id="hidd2" type="hidden" value="0" name="exp">
				<input id="hidd3" type="hidden" value="0" name="log">
				<input id="hidd4" type="hidden" value="0" name="trig">
				<input id="hidd5" type="hidden" value="0" name="invtrig">
				<input id="diff" type="hidden" value="1" name="diff">
			  </div>
			</div>
		</form>

    	<button type="button" id="button1" class="btn btn-primary">Integration by parts</button>
    	<button type="button" id="button2" class="btn btn-primary">Exponentiation</button>
    	<button type="button" id="button3" class="btn btn-primary">Logarithms</button>
    	<button type="button" id="button4" class="btn btn-primary">Trigonometry</button>
    	<button type="button" id="button5" class="btn btn-primary">Inverse triginometry</button>
		<button type="button" id="button_all" class="btn btn-primary">I want it all!</button>

    </div>

    <div class="container">
    	<div class="row">
			<div class="col-md-6">
				<div style="padding-top:20px"  class="dropdown">
				  <button id="down" class="btn btn-primary btn-lg" type="button" data-toggle="dropdown">Difficulty
				  <span class="caret"></span></button>
				  <ul class="dropdown-menu">
					<li><a id="diff1" href="#">1</a></li>
					<li><a id="diff2" href="#">2</a></li>
					<li><a id="diff3" href="#">3</a></li>
					<li><a id="diff4" href="#">4</a></li>
					<li><a id="diff5" href="#">5</a></li>
				  </ul>
				</div>
				<h1><button type="button" id="button_gen" class="btn btn-primary btn-lg">Generate a Problem!</button></h1>
				<div id="problem" style="padding-top:20px; font-size:30px; display:none;"></div>
					<ul id="steps" class="list-group" style="display:none">
						<li class="list-group-item">1. Go to wolframalpha.com</li>
						<li class="list-group-item">2. Plug in the integral we gave you.</li>
						<li class="list-group-item">3. Submit the answer.</li>
						<li class="list-group-item">4. Have some vodka.</li>
					</ul>
      			</div>
      		<div id="input_side" class="col-md-6" style="display:none">
				<h1> Input your solution:</h1>
				<h2>
					<form id="ans_form" onsubmit="return check_answer();">
						<div class="form-group">
							<input class="form-control" type="text" value="" id="answer">
						</div>
						<button type="submit" class="btn btn-primary">Submit</button>
					</form>
				</h2>
				<div id="good_ans" class="alert alert-success" role="alert" style="display:none">
  					<strong>Well done!</strong> You are an integral master.
				</div>
				<div id="bad_ans" class="alert alert-danger" role="alert" style="display:none">
  					<strong>Wrong</strong> Better luck next time.
				</div>
				<div id="solution" style="display:none">
  					<button type="button" class="btn btn-primary">Show the step-by-step solution</button>
				</div>
      		</div>
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
