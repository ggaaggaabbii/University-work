package Model.Stmt;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.Exp;

public class AssignStmt implements IStmt {

	String id;
	Exp exp;

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		MyIStack<IStmt> stack = state.getExeStack();
		MyIMap<String, Integer> symTable = state.getSymTable();
		MyIMap<Integer, Integer> heap = state.getHeap();
		int val = exp.eval(symTable, heap);
		symTable.put(id, val);
		return null;
	}

	public AssignStmt(String id, Exp exp) {
		this.id = id;
		this.exp = exp;
	}

	@Override
	public String toString() {
		return id + " = " + exp.toString();
	}

	@Override
	public IStmt deepCopy() {
		return new AssignStmt(id, exp);
	}
}
