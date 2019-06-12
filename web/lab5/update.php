<div>
  <a href="/index.php">back</a>
</div>
<div>
  <input id="id" type="text" placeholder="name" onkeyup="getRecipes()"></input>
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
  <input id="submit" type="button" value="submit" onclick="updateRecipe()"></input>
</div>
<p id="output"></p>

<script type="text/javascript">
    var xmlhttp;
    function getRecipes() {
      xmlhttp=GetXmlHttpObject();
      if (xmlhttp==null)  {
        alert ("Your browser does not support XMLHTTP!");
        return;
      }
      var url="filter.php?name=" + document.getElementById("id").value;
      //url=url+"?q="+str;
      //url=url+"&sid="+Math.random();
      xmlhttp.onreadystatechange=stateChanged;
      xmlhttp.open("GET",url,true);
      xmlhttp.send();
    }
    function stateChanged() {
      if (xmlhttp.readyState==4 && xmlhttp.status==200) {
            var result = xmlhttp.responseText;
            //alert(result);
            var array = result.split(",");
            document.getElementById("author").value = array[0];
            document.getElementById("name").value = array[1];
            document.getElementById("type").value = array[2];
            document.getElementById("recipe").value = array[3];
      }
    }
    function GetXmlHttpObject() {
      if (window.XMLHttpRequest) {        // code for IE7+, Firefox, Chrome, Opera, Safari
        return new XMLHttpRequest();
      }
      return null;
    }

    function updateRecipe() {
      xmlhttp=GetXmlHttpObject2();
      if (xmlhttp==null) {
        alert ("Your browser does not support XMLHTTP!");
        return;
      }
      var url="updateTable.php";
      //url=url+"?q="+str;
      //url=url+"&sid="+Math.random();
      xmlhttp.onreadystatechange=stateChanged2;
      xmlhttp.open("POST",url,true);
      xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
      xmlhttp.send("id=" + document.getElementById("id").value +
                   "&author=" + document.getElementById("author").value +
                   "&name=" + document.getElementById("name").value +
                   "&type=" + document.getElementById("type").value +
                   "&recipe=" + document.getElementById("recipe").value);
    }
    function stateChanged2() {
      if (xmlhttp.readyState==4 && xmlhttp.status==200) {
            document.getElementById("output").innerHTML=xmlhttp.responseText;
      }
    }
    function GetXmlHttpObject2() {
      if (window.XMLHttpRequest) {        // code for IE7+, Firefox, Chrome, Opera, Safari
        return new XMLHttpRequest();
      }
      return null;
    }
  </script>

<?php

?>
