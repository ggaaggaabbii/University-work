package Model.Expresions;

import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;

public class VarExp extends Exp {

	String id;

	@Override
	public int eval(MyIMap<String, Integer> tbl, MyIMap<Integer, Integer> heap) throws MyStmtExecException {
		if (tbl.get(id) == null) {
			throw new MyStmtExecException("Undefined variable: " + id);
		}
		return tbl.get(id);
	}

	public VarExp(String id) {
		this.id = id;
	}

	@Override
	public String toString() {
		return id;
	}
}
