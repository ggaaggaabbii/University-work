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
public class PhaseOneController extends HttpServlet {
    public static String getCookie(HttpServletRequest request, String name){
        for(int i=0; i<request.getCookies().length; i++)
        {
            if(request.getCookies()[i].getName().equals(name)) {

                return request.getCookies()[i].getValue();
            }
        }
        return null;
    }

    public static void deleteCookie(HttpServletRequest request, String name) {
        for(int i=0; i<request.getCookies().length; i++)
        {
            if(request.getCookies()[i].getName().equals(name)) {

                request.getCookies()[i].setMaxAge(0);
            }
        }
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
    {
        Integer pid = 0, x, y;
        Database db = new Database();
        db.connect();
        RequestDispatcher rd = null;
        try {
            pid = Integer.parseInt(request.getSession().getAttribute("pid").toString());
            x = Integer.parseInt(request.getParameter("x"));
            y = Integer.parseInt(request.getParameter("y"));

        } catch(RuntimeException e) {
            request.setAttribute("ERROR", e.getMessage());
            rd = request.getRequestDispatcher("/phase1.jsp");
            rd.forward(request, response);
            return;
        }

        if(x>2 || x<=0 || y<=0 || y>4)
        {
            request.setAttribute("ERROR", "Invalid attributes for battleship");
            rd = request.getRequestDispatcher("/phase1.jsp");
            rd.forward(request, response);
            return;
        }


       Player p = db.findById(pid);
       p.setBattleShipOneX(x);
       p.setBattleShipOneY(y);
       db.updatePlayer(p);
       rd = request.getRequestDispatcher("/phase2.jsp");
       rd.forward(request, response);
    }
}
