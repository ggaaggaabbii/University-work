<?php
  session_start();
?>
<!DOCTYPE html>
<html lang="en" dir="ltr">

<head>
  <meta charset="utf-8">
  <title></title>
  <script type="text/javascript">
    var xmlhttp;

    function getFlights() {
      xmlhttp = GetXmlHttpObject();
      if (xmlhttp == null) {
        alert("Your browser does not support XMLHTTP!");
        return;
      }
      var url = "getFlights.php";
      //url=url+"?q="+str;
      //url=url+"&sid="+Math.random();
      xmlhttp.onreadystatechange = stateChanged;
      xmlhttp.open("POST", url, true);
      xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
      xmlhttp.send("name=" + document.getElementById("name").value);
    }

    function stateChanged() {
      if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
        document.getElementById("maindiv").innerHTML = xmlhttp.responseText;
        var table = document.getElementById("flights");
        for (var i = 0, row; row = table.rows[i]; i++) {
          //iterate through rows
          //rows would be accessed using the "row" variable assigned in the for loop
          if (row.cells[0].innerText != "id"){
            row.cells[0].setAttribute('onclick', 'reserveFlight(' + row.cells[0].innerText + ');');
          }
        }
      }
    }

    function stateChanged2() {
      if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
        document.getElementById("maindiv").innerHTML = xmlhttp.responseText;
      }
    }

    function reserveFlight(flightId) {
      xmlhttp = GetXmlHttpObject();
      if (xmlhttp == null) {
        alert("Your browser does not support XMLHTTP!");
        return;
      }
      var url = "reserveFlight.php";
      //url=url+"?q="+str;
      //url=url+"&sid="+Math.random();
      xmlhttp.onreadystatechange = stateChanged2;
      xmlhttp.open("POST", url, true);
      xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
      xmlhttp.send("flightId=" + flightId);
    }

    function GetXmlHttpObject() {
      if (window.XMLHttpRequest) { // code for IE7+, Firefox, Chrome, Opera, Safari
        return new XMLHttpRequest();
      }
      return null;
    }
  </script>

</head>

<body>
  <input id="name" type="text" name="name"></input>
  <input id="submit" type="button" value="Submit" name="submit" onclick="getFlights()"></input>
  <div id="maindiv"></div>
</body>

</html>
