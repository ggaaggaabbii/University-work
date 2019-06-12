package controller;

import model.Move;
import model.Player;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.stream.Collectors;

/**
 * Created by Nicu on 04-Jun-17.
 */
public class MoveController extends HttpServlet {

    Set<Integer> waitingQueue = new HashSet<>();
    CyclicBarrier barrier = new CyclicBarrier(2);
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
            Integer pid = Integer.parseInt(request.getSession().getAttribute("pid").toString());

            Integer x = Integer.parseInt(request.getParameter("x"));
            Integer y = Integer.parseInt(request.getParameter("y"));

        Database db = new Database();
        db.connect();


        Player p = db.findById(pid);

        List<Move> moves = p.getMoves();
        final Boolean[] found = new Boolean[1];
        found[0] = false;
        moves.forEach(m -> {
            if(m.getX() == x && m.getY() == y)
            {
                found[0] = true;
            }
        });



        waitingQueue.add(pid);

        if(!found[0]) {
            Move m = new Move(p, x, y);
            m.setId(0);
            db.insertMove(m);
        }


        RequestDispatcher rd = request.getRequestDispatcher("/game.jsp");

        try {
            barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        p = db.findById(pid);
        Player other = db.findAllPlayers().get(0).getId() == pid ? db.findAllPlayers().get(1) : db.findAllPlayers().get(0);

        List<Move> mymoves = p.getMoves();
        List<Move> othermoves = other.getMoves();

        request.setAttribute("moves", mymoves);
        request.setAttribute("other", othermoves);
        String myhit = "Missed!";

        if(x >= other.getBattleShipOneX() && x <= other.getBattleShipOneX()+2 && y == other.getBattleShipOneY())
        {
            myhit = "Hit!";
        }

        if(y >= other.getBattleShipTwoY() && y <= other.getBattleShipTwoY()+2 && x == other.getBattleShipTwoX())
        {
            myhit = "Hit!";
        }

        Player winner = verifyIfGameIsFinished(p, other);
        if(winner != null)
        {
            if(p.getId() == winner.getId())
            {
                request.setAttribute("finished", "You won");
            }
            else
            {
                request.setAttribute("finished", "You lost");
            }
        }
        if(found[0])
        {
            request.setAttribute("ERROR", "Move already made");
        }
        request.setAttribute("myhit", myhit);
        request.setAttribute("me", p);
        waitingQueue.remove(pid);
        rd.forward(request, response);
    }



    public static String verifyMyTable(Player p, List<Move> o, Integer x, Integer y) {
        String response = "";
        if(x >= p.getBattleShipOneX() && x<= p.getBattleShipOneX()+2 && y == p.getBattleShipOneY())
        {
            response = "btn-success";
        }
        if(y >= p.getBattleShipTwoY() && y<= p.getBattleShipTwoY()+2 && x == p.getBattleShipTwoX())
        {
            response = "btn-success";
        }
        if(o.contains(new Move(null, x, y)))
        {
            response = "btn-danger";
        }
        return response;
    }

    public Player verifyIfGameIsFinished(Player player1, Player player2) {
        //verify if player 1 won

        List<Move> movesList1 = player1.getMoves();
        List<Move> movesList2 = player2.getMoves();

        // verify bs 1 and bs2
        int cnt = 0, cnt2 = 0;
        for(int i=0; i<3; i++) {
            int finalI = i;
            if (movesList1.stream().filter(m -> m.getX() == player2.getBattleShipOneX()+ finalI && m.getY() == player2.getBattleShipOneY()).collect(Collectors.toList()).size() != 0)
            {
                cnt++;
            }

            int finalI1 = i;
            if (movesList1.stream().filter(m -> m.getX() == player2.getBattleShipTwoX() && m.getY() == player2.getBattleShipTwoY()+ finalI1).collect(Collectors.toList()).size() != 0)
            {
                cnt++;
            }
            int finalI2 = i;
            if (movesList2.stream().filter(m -> m.getX() == player1.getBattleShipOneX()+ finalI2 && m.getY() == player1.getBattleShipOneY()).collect(Collectors.toList()).size() != 0)
            {
                cnt2++;
            }
            int finalI3 = i;
            if (movesList2.stream().filter(m -> m.getX() == player1.getBattleShipTwoX() && m.getY() == player1.getBattleShipTwoY()+ finalI3).collect(Collectors.toList()).size() != 0)
            {
                cnt2++;
            }
        }
        if(cnt == 6)
        {
            return player1;
        }
        if(cnt2 == 6)
        {
            return player2;
        }
        return null;

    }
}
