<?php
  require 'db_util.php';
  $db = new DBUtils();


  alert("hello");
  //alert(json_encode($_GET));
  //$type = $_GET["type"];
  //alert($type)
  //$resultset = $db->select(int($type));

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
