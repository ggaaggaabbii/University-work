package Model.Stmt;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.Exp;

public class IfStmt implements IStmt {

	Exp exp;
	IStmt thenS;
	IStmt elseS;

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		MyIMap<String, Integer> tbl = state.getSymTable();
		if (exp.eval(tbl) != 0) {
			thenS.execute(state);
		} else {
			elseS.execute(state);
		}
		return null;
	}

	public IfStmt(Exp e, IStmt t, IStmt el) {
		exp = e;
		thenS = t;
		elseS = el;
	}

	@Override
	public String toString() {
		return "IF(" + exp.toString() + ") THEN(" + thenS.toString() + ")ELSE(" + elseS.toString() + ")";
	}

	@Override
	public IStmt deepCopy() {
		return new IfStmt(exp, thenS.deepCopy(), elseS.deepCopy());
	}
}
