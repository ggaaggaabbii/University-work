package Model.Expresions;

import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;

public class ReadHeapExp extends Exp {

	String varName;

	@Override
	public int eval(MyIMap<String, Integer> tbl, MyIMap<Integer, Integer> heap) throws MyStmtExecException {
		Integer adr = tbl.get(varName);
		if (adr == null) {
			throw new MyStmtExecException("Undefined variable: " + varName);
		}

		Integer val = heap.get(adr);
		if (val == null) {
			throw new MyStmtExecException("Invalid memory location: " + adr);
		}

		return val;
	}

	public ReadHeapExp(String var) {
		varName = var;
	}

	@Override
	public String toString() {
		return "rH(" + varName + ")";
	}
}
