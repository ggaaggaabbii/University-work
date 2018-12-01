package Model.Stmt;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.Exp;

public class HeapAllocStmt implements IStmt {
	String varName;
	Exp expresion;
	static int address = 0;

	public HeapAllocStmt(String varName2, Exp expresion2) {
		varName = varName2;
		expresion = expresion2;
	}

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		MyIMap<String, Integer> tbl = state.getSymTable();
		MyIMap<Integer, Integer> heap = state.getHeap();
		Integer adr = HeapAllocStmt.getAdr();
		heap.put(adr, expresion.eval(tbl, heap));
		tbl.put(varName, adr);

		return null;
	}

	private static Integer getAdr() {
		++address;
		return address;
	}

	@Override
	public IStmt deepCopy() {
		return new HeapAllocStmt(varName, expresion);
	}

	@Override
	public String toString() {
		return "new(" + varName + ", " + expresion.toString() + ")";
	}

}
