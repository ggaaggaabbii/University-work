package controller;

import model.Player;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * Created by Nicu on 04-Jun-17.
 */
public class NewPlayerController extends HttpServlet {


    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        Database db = new Database();
        db.connect();
        RequestDispatcher requestDispatcher = null;
        if(db.findAllPlayers().size() >= 2)
        {
            requestDispatcher = request.getRequestDispatcher("/error.jsp");

            request.setAttribute("ERROR", "Already 2 players");
            requestDispatcher.forward(request, response);

        }
        else {
            Player p = new Player();
            p.setGameState(0);
            p.setId(0);
            p.setBattleShipOneX(0);
            p.setBattleShipOneY(0);
            p.setBattleShipTwoX(0);
            p.setBattleShipTwoY(0);
            db.addPlayer(p);
            Integer pid = db.findAllPlayers().get(db.findAllPlayers().size() - 1).getId();
            request.setAttribute("player_id", pid);
            //Cookie cookie = new Cookie("pid", pid.toString());
            //response.addCookie(cookie);
            request.getSession().setAttribute("pid", pid);
            requestDispatcher = request.getRequestDispatcher("/phase1.jsp");
            requestDispatcher.forward(request, response);
        }
    }
}
