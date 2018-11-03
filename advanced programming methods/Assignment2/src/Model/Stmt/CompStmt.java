package Model.Stmt;

import Model.PrgState;
import Model.ADTs.MyIStack;

public class CompStmt implements IStmt {

	IStmt first;
	IStmt second;

	@Override
	public String toString() {
		return "(" + first.toString() + "; " + second.toString() + ")";
	}

	@Override
	public PrgState execute(PrgState state) {
		MyIStack<IStmt> stack = state.getExeStack();
		stack.push(second);
		stack.push(first);
		return state;
	}

	public CompStmt(IStmt f, IStmt s) {
		first = f;
		second = s;
	}
}
