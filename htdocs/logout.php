<?

unset($_COOKIE['id']);
setcookie('id', '', time() - 3600, '/');
echo '<script>window.location.href = "http://localhost:8888/hi.php";</script>';
die();
?>