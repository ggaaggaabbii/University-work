<?php
  require 'db_util.php';
  $db = new DBUtils();


  $name = $_POST['name'];
  $resultset = $db->delete($name);

  echo $resultset;

?>
