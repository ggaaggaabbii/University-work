package mvcIntelliJIdea.controller;

import mvcIntelliJIdea.model.Board;
import mvcIntelliJIdea.model.PlayData;
import mvcIntelliJIdea.model.User;

import javax.jws.soap.SOAPBinding;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.*;

public class PlayController extends HttpServlet {

    private User player1 = null;
    private User player2 = null;
    private Boolean isFirstPlayer;
    private Connection con = null;

    public PlayController() {
        super();
        isFirstPlayer = true;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            this.con = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/Batterfield","Gabriel","dQo4tj0DLatcrKn5");

        }catch(Exception e){ System.out.println(e);}
    }


    private void addToDb(User user) {
        try {

            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 6; ++j) {

                    String query = "INSERT INTO Board (playerId, x, y, val) VALUES (?, ?, ?, ?)";
                    PreparedStatement stmt = con.prepareStatement(query);
                    stmt.setDouble(1, user.getUserId());
                    stmt.setInt(2, i);
                    stmt.setInt(3, j);
                    stmt.setInt(4, 0);

                    stmt.execute();

                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void updateDb(User user) {
        try {

            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 6; ++j) {

                    String query = "UPDATE Board SET val = ? WHERE playerId = ? AND x = ? AND y = ?";
                    PreparedStatement stmt = con.prepareStatement(query);
                    stmt.setInt(1, user.board.getForPosition(i, j));
                    stmt.setDouble(2, user.getUserId());
                    stmt.setInt(3, i);
                    stmt.setInt(4, j);

                    stmt.execute();

                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void flushForUser(User user, HttpServletResponse response) throws IOException {

        response.getWriter().print("[");
        for (int i = 0; i < 5; ++i) {
            response.getWriter().print("[");
            for (int j = 0; j < 5; ++j) {
                response.getWriter().print(user.board.getForPosition(i, j) + ",");
            }
            response.getWriter().print(user.board.getForPosition(i, 5) + "],");
        }
        response.getWriter().print("[");
        for (int j = 0; j < 5; ++j) {
            response.getWriter().print(user.board.getForPosition(5, j) + ",");
        }
        response.getWriter().print(user.board.getForPosition(5, 5) + "]]");


    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, java.io.IOException {

        if (player1 == null || player2 == null) {
            response.setContentType("application/json");
            response.getWriter().print("{\"response\":\"there should be 2 players connected\"}");
            response.getWriter().flush();
            return;
        }

        User currentUser;
        User otherUser;
        if (((PlayData)(request.getSession().getAttribute("PlayData"))).userId == player1.getUserId()) {
            currentUser = player1;
            otherUser = player2;
        } else {
            currentUser = player2;
            otherUser = player1;
        }


        response.setContentType("application/json");
        response.getWriter().print("{\"response\":\"success\",\"board\":");

        flushForUser(currentUser, response);
        response.getWriter().print(",\"opponent\":");
        flushForUser(otherUser, response);

        response.getWriter().print("}");

    }

    protected void doPost(HttpServletRequest request,
                          HttpServletResponse response) throws ServletException, IOException {

        if (request.getSession().getAttribute("PlayData") == null) {
            PlayData data = new PlayData();
            if (player1 == null) {
                player1 = new User(data.userId);
                addToDb(player1);
            } else {
                player2 = new User(data.userId);
                addToDb(player2);
            }
            request.getSession().setAttribute("PlayData", data);
        }

        User currentUser;
        User otherUser;
        if (((PlayData)(request.getSession().getAttribute("PlayData"))).userId == player1.getUserId()) {
            currentUser = player1;
            otherUser = player2;
        } else {
            currentUser = player2;
            otherUser = player1;
        }

        if(request.getParameter("orientation") == null) {
            //attack
            if (player1 == null || player2 == null) {
                response.setContentType("application/json");
                response.getWriter().print("{\"response\":\"there should be 2 players connected\"}");
                response.getWriter().flush();
                return;
            }

            Integer x = Integer.parseInt(request.getParameter("x"));
            Integer y = Integer.parseInt(request.getParameter("y"));

            if (otherUser.board.shipsAdded != 2) {
                response.setContentType("application/json");
                response.getWriter().print("{\"response\":\"other player didn't select yet\"}");
                response.getWriter().flush();
                return;
            }
            if (currentUser.board.shipsAdded != 2) {
                response.setContentType("application/json");
                response.getWriter().print("{\"response\":\"please select ships first\"}");
                response.getWriter().flush();
                return;
            }

            if ((isFirstPlayer && currentUser != player1) || (!isFirstPlayer && currentUser != player2)) {
                response.setContentType("application/json");
                response.getWriter().print("{\"response\":\"other player's turn\"}");
                response.getWriter().flush();
                return;
            }

            otherUser.board.attack(x, y);
            isFirstPlayer = !isFirstPlayer;
            response.setContentType("application/json");
            response.getWriter().print("{\"response\":\"success\"}");
            response.getWriter().flush();
            updateDb(currentUser);
            updateDb(otherUser);
            return;
        } else {
            //position ship
            Integer x = Integer.parseInt(request.getParameter("x"));
            Integer y = Integer.parseInt(request.getParameter("y"));
            Integer orientation = Integer.parseInt(request.getParameter("orientation"));
            if (currentUser.board.shipsAdded != 2) {
                currentUser.board.addShip(x, y, orientation);
                response.setContentType("application/json");
                response.getWriter().print("{\"response\":\"success\"}");
                response.getWriter().flush();
                updateDb(currentUser);
            } else {
                response.setContentType("application/json");
                response.getWriter().print("{\"response\":\"there are 2 ships already\"}");
                response.getWriter().flush();
                return;
            }
        }
    }

}
