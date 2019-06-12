<%@ page import="model.Move" %>
<%@ page import="model.Player" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="java.util.List" %>
<%@ page import="controller.MoveController" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<h2> Game started </h2>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>

<%


    if(request.getAttribute("ERROR") != null)
    {
        out.println("<h1>Error:"+request.getAttribute("ERROR").toString()+"</h1>");
    }

    if(request.getAttribute("finished") == null)
    {
        if(request.getAttribute("myhit") != null)
        {
            out.println("<h4>"+request.getAttribute("myhit")+"</h4>");
        }
        List<Move> moves = (List<Move>)request.getAttribute("moves");
        if(moves == null)
        {
            moves = new ArrayList<>();
        }
        List<Move> other = (List<Move>)request.getAttribute("other");
        if(other == null)
        {
            other = new ArrayList<>();
        }
        Player me = (Player)request.getAttribute("me");
%>

Hit here:
<table>
    <tr>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="1">
                <input type="hidden" name="y" value="1">
                <input <% if(moves.contains(new Move(null, 1, 1))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="1">
                <input type="hidden" name="y" value="2">
                <input <% if(moves.contains(new Move(null, 1, 2))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="1">
                <input type="hidden" name="y" value="3">
                <input <% if(moves.contains(new Move(null, 1, 3))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="1">
                <input type="hidden" name="y" value="4">
                <input <% if(moves.contains(new Move(null, 1, 4))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>

    </tr>
    <tr>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="2">
                <input type="hidden" name="y" value="1">
                <input <% if(moves.contains(new Move(null, 2, 1))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="2">
                <input type="hidden" name="y" value="2">
                <input <% if(moves.contains(new Move(null, 2, 2))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="2">
                <input type="hidden" name="y" value="3">
                <input <% if(moves.contains(new Move(null, 2, 3))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="2">
                <input type="hidden" name="y" value="4">
                <input <% if(moves.contains(new Move(null, 2, 4))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>

    </tr>
    <tr>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="3">
                <input type="hidden" name="y" value="1">
                <input <% if(moves.contains(new Move(null, 3, 1))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="3">
                <input type="hidden" name="y" value="2">
                <input <% if(moves.contains(new Move(null, 3, 2))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="3">
                <input type="hidden" name="y" value="3">
                <input <% if(moves.contains(new Move(null, 3, 3))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="3">
                <input type="hidden" name="y" value="4">
                <input <% if(moves.contains(new Move(null, 3, 4))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>

    </tr>
    <tr>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="4">
                <input type="hidden" name="y" value="1">
                <input <% if(moves.contains(new Move(null, 4, 1))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="4">
                <input type="hidden" name="y" value="2">
                <input <% if(moves.contains(new Move(null, 4, 2))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="4">
                <input type="hidden" name="y" value="3">
                <input <% if(moves.contains(new Move(null, 4, 3))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
        <td>
            <form action="/moves" method="GET">
                <input type="hidden" name="x" value="4">
                <input type="hidden" name="y" value="4">
                <input <% if(moves.contains(new Move(null, 4, 4))) { out.print("class=\"btn-danger\""); }%> type="submit" value="X"/>
            </form>
        </td>
    </tr>
</table>
You are hit here:
<table>
    <tr>
        <td>
            <span
                <%
                    out.print("class=\""+MoveController.verifyMyTable(me, other, 1, 1)+"\"");
                %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 1, 2)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 1, 3)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 1, 4)+"\"");
                    %>
            > X </span>
        </td>
    </tr>
    <tr>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 2, 1)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 2, 2)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 2, 3)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 2, 4)+"\"");
                    %>
            > X </span>
        </td>
    </tr>
    <tr>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 3, 1)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 3, 2)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 3, 3)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 3, 4)+"\"");
                    %>
            > X </span>
        </td>
    </tr>
    <tr>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 4, 1)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 4, 2)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 4, 3)+"\"");
                    %>
            > X </span>
        </td>
        <td>
            <span
                    <%
                        out.print("class=\""+MoveController.verifyMyTable(me, other, 4, 4)+"\"");
                    %>
            > X </span>
        </td>
    </tr>
</table>



<%
    }
    else
    {
    out.println("<h2>"+request.getAttribute("finished").toString()+"</h2>");

%>
    <form action="/finish" method="post">
        <input type="submit" value="Go back!"/>
    </form>
<%
    }
%>