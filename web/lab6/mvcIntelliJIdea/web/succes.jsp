<%@ page import="static java.lang.Math.min" %>
<%@ page import="static java.lang.Math.max" %><%--
  Created by IntelliJ IDEA.
  User: forest
  Date: 16.12.2014
  Time: 10:47
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Insert title here</title>
    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.4.1.js" integrity="sha256-WpOohJOqMqqyKL9FccASB9O0KwACQJpFTUBLTYOVvVU=" crossorigin="anonymous"></script>
</head>

<body>
<style>
    table, th, td {
        border: 1px solid black;
        border-collapse: collapse;
        float: left;
        margin: 5px;
    }

    .board {
        float: left;
        padding: 15px;
    }

</style>
<script>
    $(document).ready(function() {
        $("#submit_position").click(function() {
            var x = $("#x_position").val();
            var y = $("#y_position").val();
            var orientation = $("#orientation").val();
            $.post("/PlayController?x=" + x + "&y=" + y + "&orientation=" + orientation, function (response) {
                if (response["response"] == "success") {
                    var nextX = [-1, 0, 1, 0];
                    var nextY = [0, -1, 0, 1];
                    var or = parseInt(orientation);
                    var currentX = parseInt(x);
                    var currentY = parseInt(y);

                    for (var i = 0; i < 3; ++i) {
                        $("#id_" + (currentX * 6 + currentY)).css("background-color", "green");
                        currentX += nextX[or];
                        currentY += nextY[or];
                    }
                } else {
                    alert(response["response"]);
                }
            });
        });
        $("#submit_attack").click(function() {
            var x = $("#x_attack").val();
            var y = $("#y_attack").val();
            $.post("/PlayController?x=" + x + "&y=" + y, function (response) {
                if (response["response"] == "success") {

                } else {
                    alert(response["response"]);
                }
            });
        });

        var myFunction = function() {
            $.get("/PlayController", function (response) {
                if (response["response"] == "success") {
                    //alert(JSON.stringify(response))
                    var opponentBoard = response["opponent"];
                    for (var i = 0; i < 6; ++i) {
                        for (var j = 0; j < 6; ++j) {
                            if (opponentBoard[i][j] == 3) {
                                $("#id2_" + (i * 6 + j)).css("background-color", "red");
                            }
                            if (opponentBoard[i][j] == 2) {
                                $("#id2_" + (i * 6 + j)).css("background-color", "yellow");
                            }
                        }
                    }

                    var opponentBoard = response["board"];
                    for (var i = 0; i < 6; ++i) {
                        for (var j = 0; j < 6; ++j) {
                            if (opponentBoard[i][j] == 3) {
                                $("#id_" + (i * 6 + j)).css("background-color", "red");
                            }
                            if (opponentBoard[i][j] == 2) {
                                $("#id_" + (i * 6 + j)).css("background-color", "yellow");
                            }
                        }
                    }
                }
            });
        };
        setInterval(myFunction, 1000);
    });
</script>
<%
    out.print("<div class=\"container\">");
    out.print("<div class=\"board\">");
    out.print("<p>Your Board</p>");
    out.print("<table>");
    for (int i = 0; i < 7; ++i) {
        out.print("<tr>");
        for (int j = 0; j < 7; ++j) {
            if (i != 0 && j != 0) {
                out.print("<td id=\"id_" + ((i - 1) * 6 + (j - 1)) + "\">&nbspo&nbsp</td>");
            }else {
                out.print("<td>&nbsp" + max(max(i - 1, j - 1), 0) + "&nbsp</td>");
            }
        }
        out.print("</tr>");
    }
    out.print("</table>");
    out.print("</div>");

    out.print("<div class=\"board\">");
    out.print("<p>Opponent Board</p>");
    out.print("<table>");
    for (int i = 0; i < 7; ++i) {
        out.print("<tr>");
        for (int j = 0; j < 7; ++j) {
            if (i != 0 && j != 0) {
                out.print("<td id=\"id2_" + ((i - 1) * 6 + (j - 1)) + "\">&nbspo&nbsp</td>");
            }else {
                out.print("<td>&nbsp" + max(max(i - 1, j - 1), 0) + "&nbsp</td>");
            }
        }
        out.print("</tr>");
    }
    out.print("</table>");
    out.print("</div>");
    out.print("</div>");
    for (int i = 0; i < 15; ++i) {
        out.print("<br>");
    }

%>

<div class="container">
    <div class="board">
        <p>Add Ship</p>
            x:<br>
            <input type="text" name="x" id="x_position"><br>
            y:<br>
            <input type="text" name="y" id="y_position"><br>
            orientation:<br>
            <input type="text" name="orientation" id="orientation"><br>
            <button id="submit_position">submit</button>
    </div>
    <div class="board">
        <p>Attack Ship</p>
            x:<br>
            <input type="text" name="x" id="x_attack"><br>
            y:<br>
            <input type="text" name="y" id="y_attack"><br>
            <button id="submit_attack">submit</button>
    </div>
</div>
</body>
</html>