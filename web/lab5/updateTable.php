<?php
  require 'db_util.php';
  $db = new DBUtils();

  $id = $_POST['id'];
  $author = $_POST['author'];
  $name = $_POST['name'];
  $type = $_POST['type'];
  $recipe = $_POST['recipe'];
  $resultset = $db->update($id, $author, $name, $type, $recipe);

  echo $resultset;

?>
