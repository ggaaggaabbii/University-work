package Model.Stmt;

import Model.PrgState;
import Model.ADTs.MyIList;
import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.Exp;

public class PrintStmt implements IStmt {

	Exp exp;

	@Override
	public String toString() {
		return "Print(" + exp.toString() + ")";
	}

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		MyIList<Integer> ot = state.getOut();
		MyIMap<String, Integer> tbl = state.getSymTable();
		ot.add(exp.eval(tbl));
		return state;
	}

	public PrintStmt(Exp exp) {
		this.exp = exp;
	}
}
