<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>Hello World</title>
  </head>
  <script type="text/javascript">
			var xmlhttp;
			function getRecipes() {
				xmlhttp=GetXmlHttpObject();
				if (xmlhttp==null)  {
					alert ("Your browser does not support XMLHTTP!");
					return;
				}
				var url="showTable.php?type=" + document.getElementById("type").value;
				//url=url+"?q="+str;
				//url=url+"&sid="+Math.random();
				xmlhttp.onreadystatechange=stateChanged;
				xmlhttp.open("GET",url,true);
				xmlhttp.send();
			}
			function stateChanged() {
				if (xmlhttp.readyState==4 && xmlhttp.status==200) {
				      document.getElementById("maindiv").innerHTML=xmlhttp.responseText;
				}
			}
			function GetXmlHttpObject() {
				if (window.XMLHttpRequest) {        // code for IE7+, Firefox, Chrome, Opera, Safari
					return new XMLHttpRequest();
				}
				return null;
			}
		</script>
  <body>
    <div>
      <a href="/update.php">update</a>
      <a href="/delete.php">delete</a>
      <a href="/insert.php">insert</a>
    </div>
    <input id="type" type="text" name="type" onkeyup="getRecipes()"></input>
    <div id="maindiv"></div>

  </body>
</html>
