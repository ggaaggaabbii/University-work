
<div>
  <a href="/index.php">back</a>
</div>
<input id="delete_name" type="text"></input>
<input type="button" onclick="deleteRecipe()" value="delete"></input>
<p id="output"></p>
<script type="text/javascript">
var xmlhttp;
function deleteRecipe() {
  xmlhttp=GetXmlHttpObject();
  if (xmlhttp==null)  {
    alert ("Your browser does not support XMLHTTP!");
    return;
  }
  var url="deleteFromTable.php";
  //url=url+"?q="+str;
  //url=url+"&sid="+Math.random();
  xmlhttp.onreadystatechange=stateChanged;
  xmlhttp.open("POST",url,true);
  xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
  xmlhttp.send("name=" + document.getElementById("delete_name").value);
}
function stateChanged() {
  if (xmlhttp.readyState==4 && xmlhttp.status==200) {
        document.getElementById("output").innerHTML=xmlhttp.responseText;
  }
}
function GetXmlHttpObject() {
  if (window.XMLHttpRequest) {        // code for IE7+, Firefox, Chrome, Opera, Safari
    return new XMLHttpRequest();
  }
  return null;
}
</script>
