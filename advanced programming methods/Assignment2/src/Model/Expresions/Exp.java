package Model.Expresions;

import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;

public abstract class Exp {
	public abstract int eval(MyIMap<String, Integer> tbl) throws MyStmtExecException;
}
