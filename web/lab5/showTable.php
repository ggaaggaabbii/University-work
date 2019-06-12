<?php
  require 'db_util.php';
  $db = new DBUtils();

  $type = $_GET['type'];
  $resultset = $db->select($type);

  echo "<table border='1'><tr><th>author</th><th>name</th><th>type</th><th>recipe</th></tr>";
  	foreach ($resultset as $row) {
  		echo "<tr>";
  		echo "<td>" . $row['author'] . "</td>";
  		echo "<td>" . $row['name'] . "</td>";
  		echo "<td>" . $row['type'] . "</td>";
  		echo "<td>" . $row['recipe'] . "</td>";
  		echo "</tr>";
  	}
  	echo "</table>";

?>
