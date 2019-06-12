package mvcIntelliJIdea.controller;

/**
 * Created by forest on 16.12.2014.
 */


import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


public class LoginController extends HttpServlet {

    private int players;

    public LoginController() {
        super();
        this.players = 0;
    }

    protected void doPost(HttpServletRequest request,
                          HttpServletResponse response) throws ServletException, IOException {

        RequestDispatcher rd = null;

        if (this.players < 2) {
            this.players += 1;
            rd = request.getRequestDispatcher("/succes.jsp");

        } else {
            rd = request.getRequestDispatcher("/error.jsp");
        }
        //request.getSession().getAttribute("userid");
        rd.forward(request, response);
    }

}