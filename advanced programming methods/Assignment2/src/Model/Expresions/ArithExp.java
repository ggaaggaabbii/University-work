package Model.Expresions;

import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;

public class ArithExp extends Exp {

	Exp e1;
	Exp e2;
	String op;

	@Override
	public int eval(MyIMap<String, Integer> tbl, MyIMap<Integer, Integer> heap) throws MyStmtExecException {
		if (op == "+") {
			return e1.eval(tbl, heap) + e2.eval(tbl, heap);
		} else if (op == "-") {
			return e1.eval(tbl, heap) - e2.eval(tbl, heap);
		} else if (op == "*") {
			return e1.eval(tbl, heap) * e2.eval(tbl, heap);
		} else {
			if (e2.eval(tbl, heap) == 0) {
				throw new MyStmtExecException("Division By 0");
			}
			return e1.eval(tbl, heap) / e2.eval(tbl, heap);
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
