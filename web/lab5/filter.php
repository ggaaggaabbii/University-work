<?php

require 'db_util.php';
$db = new DBUtils();

$name = $_GET['name'];
$resultset = $db->filter($name);

foreach ($resultset as $row) {
  echo $row['author'] . ",";
  echo $row['name'] . ",";
  echo $row['type'] . ",";
  echo $row['recipe']. ",";
}
echo " , , , ";

?>
