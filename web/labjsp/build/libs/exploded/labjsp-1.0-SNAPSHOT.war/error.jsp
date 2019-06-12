<%--
  Created by IntelliJ IDEA.
  User: Nicu
  Date: 04-Jun-17
  Time: 6:14 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Error</title>
</head>
<body>
<h1><% out.println(request.getAttribute("ERROR")); %></h1>
<a href="index.jsp"> GO BACK TO INDEX</a>
</body>
</html>
