package model;

import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;

import java.io.Serializable;

/**
 * Created by Nicu on 01-Jun-17.
 */

@AllArgsConstructor
@NoArgsConstructor
public abstract class BaseEntity<ID extends Serializable> implements Serializable {

    private ID id;

    @Override
    public String toString() {
        return "BaseEntity{" +
                "id=" + id +
                '}';
    }

    public ID getId() {
        return id;
    }

    public void setId(ID id) {
        this.id = id;
    }
}
