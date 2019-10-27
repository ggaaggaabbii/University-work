<?php
  session_start();
  require 'db_util.php';
  $db = new DBUtils();

  $flightId = $_POST['flightId'];
  $name = $_SESSION["name"];
  echo $flightId;
  echo $_SESSION["name"];
  $resultset = $db->reserveFlight($name, $flightId);

  echo "<table id=\"hotels\" border='1'><tr><th>id</th><th>name</th><th>city</th><th>date</th><th>rooms</th></tr>";
  	foreach ($resultset as $row) {
  		echo "<tr>";
  		echo "<td>" . $row['ID'] . "</td>";
  		echo "<td>" . $row['Name'] . "</td>";
  		echo "<td>" . $row['City'] . "</td>";
  		echo "<td>" . $row['Date'] . "</td>";
      echo "<td>" . $row['Rooms'] . "</td>";
  		echo "</tr>";
  	}
  	echo "</table>";

?>
