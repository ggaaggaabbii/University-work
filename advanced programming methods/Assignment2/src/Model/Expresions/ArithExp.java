package Model.Expresions;

import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;

public class ArithExp extends Exp {

	Exp e1;
	Exp e2;
	String op;

	@Override
	public int eval(MyIMap<String, Integer> tbl) throws MyStmtExecException {
		if (op == "+") {
			return e1.eval(tbl) + e2.eval(tbl);
		} else if (op == "-") {
			return e1.eval(tbl) - e2.eval(tbl);
		} else if (op == "*") {
			return e1.eval(tbl) * e2.eval(tbl);
		} else {
			if (e2.eval(tbl) == 0) {
				throw new MyStmtExecException("Division By 0");
			}
			return e1.eval(tbl) / e2.eval(tbl);
		}
	}

	public ArithExp(String op, Exp e1, Exp e2) {
		this.e1 = e1;
		this.e2 = e2;
		this.op = op;
	}

	@Override
	public String toString() {
		return "(" + e1.toString() + " " + op + " " + e2.toString() + ")";
	}
}
