package model;

import lombok.*;

/**
 * Created by Nicu on 01-Jun-17.
 */

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@Builder
public class Move extends BaseEntity<Integer> {
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Move move = (Move) o;

        if (!x.equals(move.x)) return false;
        return y.equals(move.y);
    }

    @Override
    public int hashCode() {
        int result = x.hashCode();
        result = 31 * result + y.hashCode();
        return result;
    }

    private Player player;
    private Integer x;
    private Integer y;
}
