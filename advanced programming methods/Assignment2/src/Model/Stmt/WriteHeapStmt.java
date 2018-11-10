package Model.Stmt;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.Exp;

public class WriteHeapStmt implements IStmt {

	String varName;
	Exp expresion;

	public WriteHeapStmt(String varName2, Exp expresion2) {
		varName = varName2;
		expresion = expresion2;
	}

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		MyIMap<String, Integer> tbl = state.getSymTable();
		MyIMap<Integer, Integer> heap = state.getHeap();
		Integer adr = tbl.get(varName);

		if (adr == null) {
			throw new MyStmtExecException("Undefined variable: " + varName);
		}

		if (heap.get(adr) == null) {
			throw new MyStmtExecException("Invalid memory location: " + adr);
		}

		heap.put(adr, expresion.eval(tbl, heap));

		return state;
	}

	@Override
	public IStmt deepCopy() {
		return new WriteHeapStmt(varName, expresion);
	}

	@Override
	public String toString() {
		return "wH(" + varName + ", " + expresion.toString() + ")";
	}

}
