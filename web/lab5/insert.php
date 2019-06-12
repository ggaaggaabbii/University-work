<div>
  <a href="/index.php">back</a>
</div>
<div>
  <input id="author" type="text" placeholder="author"></input>
</div>
<div>
  <input id="name" type="text" placeholder="name"></input>
</div>
<div>
  <input id="type" type="text" placeholder="type"></input>
</div>
<div>
  <input id="recipe" type="text" placeholder="recipe"></input>
</div>
<div>
  <input id="submit" type="button" value="submit" onclick="insertRecipe()"></input>
</div>
<p id="output"></p>
<script>

function insertRecipe() {
  xmlhttp=GetXmlHttpObject();
  if (xmlhttp==null)  {
    alert ("Your browser does not support XMLHTTP!");
    return;
  }
  var url="insertInTable.php";
  //url=url+"?q="+str;
  //url=url+"&sid="+Math.random();
  xmlhttp.onreadystatechange=stateChanged;
  xmlhttp.open("POST",url,true);
  xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
  xmlhttp.send("author=" + document.getElementById("author").value +
               "&name=" + document.getElementById("name").value +
               "&type=" + document.getElementById("type").value +
               "&recipe=" + document.getElementById("recipe").value);
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
<?php



?>
