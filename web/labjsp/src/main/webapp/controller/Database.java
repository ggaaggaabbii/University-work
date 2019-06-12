package controller;

import model.Move;
import model.Player;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Nicu on 04-Jun-17.
 */
public class Database {
    private String driver;
    private String connString;
    private String user;
    private String pass;
    private Connection con;

    public Database() {
        this.driver = "org.gjt.mm.mysql.Driver";
        this.connString = "jdbc:mysql://127.0.0.1:3306/web-jsp";
        this.user = "bnie1869";
        this.pass = "cocacola";
    }

    public void connect() {
        try {
            Class.forName(driver);
            con = DriverManager.getConnection(connString, user, pass);
        } catch (Exception ex) {
            System.out.println("Error while connecting: " + ex.getMessage());
        }
    }

    public void addPlayer(Player p) {
        PreparedStatement pStmt = null;
        try {
            pStmt = this.con.prepareStatement("INSERT INTO player (id, gamestate, xbs1, ybs1, xbs2, ybs2) VALUES(?, ?, ?, ?, ?, ?)");
            pStmt.setInt(1, p.getId());
            pStmt.setInt(2, p.getGameState());
            pStmt.setInt(3, p.getBattleShipOneX());
            pStmt.setInt(4, p.getBattleShipOneY());
            pStmt.setInt(5, p.getBattleShipTwoX());
            pStmt.setInt(6, p.getBattleShipTwoY());
            pStmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }

    }

    public void updatePlayer(Player p) {
        PreparedStatement pStmt = null;
        try {
            pStmt = this.con.prepareStatement("UPDATE player SET gamestate = ?, xbs1 = ?, ybs1 = ?, xbs2 = ?, ybs2 = ? WHERE id = ? ");
            pStmt.setInt(1, p.getGameState());
            pStmt.setInt(2, p.getBattleShipOneX());
            pStmt.setInt(3, p.getBattleShipOneY());
            pStmt.setInt(4, p.getBattleShipTwoX());
            pStmt.setInt(5, p.getBattleShipTwoY());
            pStmt.setInt(6, p.getId());
            pStmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }

    }

    public void deletePlayer(Player p) {
        PreparedStatement pStmt = null;
        try {
            pStmt = this.con.prepareStatement("DELETE FROM player WHERE id = ?");
            pStmt.setInt(1, p.getId());
            pStmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Player findById(Integer id) {
        List<Player> list = findAllPlayers();
        for(int i=0; i<list.size(); i++)
        {
            if(list.get(i).getId() == id)
            {
                return list.get(i);
            }
        }
        return null;
    }

    public void insertMove(Move m) {
        PreparedStatement pStmt = null;
        try {
            pStmt = this.con.prepareStatement("INSERT INTO move (id, pid, x, y) VALUES(?, ?, ?, ?)");
            pStmt.setInt(1, m.getId());
            pStmt.setInt(2, m.getPlayer().getId());
            pStmt.setInt(3, m.getX());
            pStmt.setInt(4, m.getY());
            pStmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<Player> findAllPlayers() {
        try {
            String selectSQL = "SELECT * FROM player";
            PreparedStatement preparedStatement = this.con.prepareStatement(selectSQL);
            ResultSet rs = preparedStatement.executeQuery(selectSQL);
            List<Player> toRet = new ArrayList<>();
            while (rs.next()) {
                Integer userid = rs.getInt("id");
                Integer gameState = rs.getInt("gamestate");
                Integer bs1_x = rs.getInt("xbs1");
                Integer bs1_y = rs.getInt("ybs1");
                Integer bs2_x = rs.getInt("xbs2");
                Integer bs2_y = rs.getInt("ybs2");
                Player p = new Player(new ArrayList<>(), gameState, bs1_x, bs1_y, bs2_x, bs2_y);
                p.setId(userid);
                String selectMoves = "SELECT * FROM move WHERE pid=?";
                PreparedStatement preparedStatement1 = this.con.prepareStatement(selectMoves);
                preparedStatement1.setInt(1, userid);
                ResultSet resultSet = preparedStatement1.executeQuery();
                while(resultSet.next()) {
                    Integer mid = resultSet.getInt("id");
                    Integer pid = resultSet.getInt("pid");
                    Integer x = resultSet.getInt("x");
                    Integer y = resultSet.getInt("y");
                    Move m = new Move(p, x, y);
                    m.setId(mid);
                    p.addMove(m);
                }
                toRet.add(p);
            }
            return toRet;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }
}