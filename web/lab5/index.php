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
				var url="showTable.php";
				//url=url+"?q="+str;
				//url=url+"&sid="+Math.random();
				xmlhttp.onreadystatechange=stateChanged;
				xmlhttp.open("GET",url,true);
				xmlhttp.send(null);
			}
			function stateChanged() {
				if (xmlhttp.readyState==4) {
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
<input id="type" type="text" name="type"></input>
<input type="button" name="recipes" value="Get recipes" onclick="getRecipes()"></input>
<div id="maindiv"></div>

  </body>
</html>
