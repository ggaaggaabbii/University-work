<?php
  session_start();
  require 'db_util.php';
  $db = new DBUtils();

  $_SESSION["name"] = $_POST['name'];


  $resultset = $db->selectFlights();

  echo "<table id=\"flights\" border='1'><tr><th>id</th><th>name</th><th>departure</th><th>destination</th><th>date</th><th>seats</th></tr>";
  	foreach ($resultset as $row) {
  		echo "<tr>";
  		echo "<td>" . $row['ID'] . "</td>";
  		echo "<td>" . $row['Name'] . "</td>";
  		echo "<td>" . $row['Departure'] . "</td>";
  		echo "<td>" . $row['Destination'] . "</td>";
      echo "<td>" . $row['Date'] . "</td>";
      echo "<td>" . $row['Seats'] . "</td>";
  		echo "</tr>";
  	}
  	echo "</table>";

?>
