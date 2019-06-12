<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<html>
<br>
<%
    if(request.getAttribute("ERROR") != null)
    {
        out.println("<h1>Error: "+request.getAttribute("ERROR").toString()+"</h1>");
    }
%>
Select your second battleship:
<form action="/phase2" method="post">
    Select first battleship x: <input type="text" name="x" /><br/>
    Select first battleship y: <input type="text" name="y" /><br/>
    <input type="submit" value="Choose"/> <br/>
    <i>Note: the first battleship will be between (x, y) and (x, y+2)<br/>
        Note 2: if invalid parameters are given, an error will occur
        so please choose x between 1 and 4 and y between 1 and 2
    </i>
</form>

</html>