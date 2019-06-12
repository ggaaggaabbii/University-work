package controller;

import model.Player;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

/**
 * Created by Nicu on 04-Jun-17.
 */
public class PhaseTwoController extends HttpServlet {

    CyclicBarrier barrier = new CyclicBarrier(2);
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
    {
        Integer pid=0, x, y;
        Database db = new Database();
        db.connect();
        RequestDispatcher rd = null;
        try {
            pid = Integer.parseInt(request.getSession().getAttribute("pid").toString());
            x = Integer.parseInt(request.getParameter("x"));
            y = Integer.parseInt(request.getParameter("y"));

        } catch(RuntimeException e) {

            request.setAttribute("ERROR", e.getMessage());
            rd = request.getRequestDispatcher("/phase2.jsp");
            rd.forward(request, response);
            return;
        }

        if(x>4 || x<=0 || y<=0 || y>2)
        {
            request.setAttribute("ERROR", "Invalid attributes for battleship 2");
            rd = request.getRequestDispatcher("/phase2.jsp");
            rd.forward(request, response);
            return;
        }


        Player p = db.findById(pid);
        p.setBattleShipTwoX(x);
        p.setBattleShipTwoY(y);
        db.updatePlayer(p);
        request.setAttribute("me", p);
        try {

            barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        rd = request.getRequestDispatcher("/game.jsp");
        rd.forward(request, response);
    }
}
