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
public class FinishController extends HttpServlet {

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Integer pid = Integer.parseInt(request.getSession().getAttribute("pid").toString());
        Database db = new Database();
        db.connect();
        Player p = new Player();
        p.setId(pid);
        db.deletePlayer(p);
        request.getSession().removeAttribute("pid");

        RequestDispatcher rd = request.getRequestDispatcher("/index.jsp");
        rd.forward(request, response);

    }
}
