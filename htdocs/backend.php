<?php

$h = $_POST["diff"];
$str = $_POST["q"].$_POST["pi"].$_POST["e"].$_POST["id"].$_POST["add"].$_POST["parts"].$_POST["neg"].$_POST["inv"].$_POST["exp"].$_POST["log"].$_POST["sine"].$_POST["cosine"].$_POST["asine"].$_POST["atan"];
#echo $str;
echo system("./hacks_test $h $str ");

?>
