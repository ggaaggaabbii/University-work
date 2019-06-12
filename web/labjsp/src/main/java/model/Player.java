package model;

import lombok.*;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Nicu on 01-Jun-17.
 */

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@Builder
public class Player extends BaseEntity<Integer> {

    List<Move> moves = new ArrayList<>();

    Integer gameState;
    // battle ship one will be like
        // X
        // X
        // X
    Integer battleShipOneX;
    Integer battleShipOneY;
    // battle ship two will be like
        // X X X

    Integer battleShipTwoX;

    Integer battleShipTwoY;


    public void addMove(Move m)
    {
        moves.add(m);
    }
}
