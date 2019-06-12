<?php
  require 'db_util.php';
  $db = new DBUtils();

  $author = $_POST['author'];
  $name = $_POST['name'];
  $type = $_POST['type'];
  $recipe = $_POST['recipe'];
  $resultset = $db->insert($author, $name, $type, $recipe);

  echo $resultset;

?>
