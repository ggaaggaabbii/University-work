package Model.Expresions;

import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;

public class BooleanExp extends Exp {

	String sign;
	Exp e1;
	Exp e2;

	@Override
	public int eval(MyIMap<String, Integer> tbl, MyIMap<Integer, Integer> heap) throws MyStmtExecException {
		if (sign == "==" && e1.eval(tbl, heap) == e2.eval(tbl, heap)) {
			return 1;
		}
		if (sign == "<" && e1.eval(tbl, heap) < e2.eval(tbl, heap)) {
			return 1;
		}
		if (sign == "<=" && e1.eval(tbl, heap) <= e2.eval(tbl, heap)) {
			return 1;
		}
		if (sign == ">=" && e1.eval(tbl, heap) >= e2.eval(tbl, heap)) {
			return 1;
		}
		if (sign == ">" && e1.eval(tbl, heap) > e2.eval(tbl, heap)) {
			return 1;
		}
		if (sign == "!=" && e1.eval(tbl, heap) != e2.eval(tbl, heap)) {
			return 1;
		}

		return 0;
	}

	public BooleanExp(String sign, Exp e1, Exp e2) {
		this.e1 = e1;
		this.e2 = e2;
		this.sign = sign;
	}

	@Override
	public String toString() {
		return "(" + e1.toString() + " " + sign + " " + e2.toString() + ")";
	}
}
