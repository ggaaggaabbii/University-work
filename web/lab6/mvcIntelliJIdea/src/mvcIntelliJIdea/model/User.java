package mvcIntelliJIdea.model;


public class User {

    public Board board;
    private Double id;

    public User(Double id){
        this.id = id;
        this.board = new Board();
    }

    public Double getUserId() {
        return this.id;
    }



}