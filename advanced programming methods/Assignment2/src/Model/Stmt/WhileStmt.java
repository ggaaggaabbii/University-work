package Model.Stmt;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.Exp;

public class WhileStmt implements IStmt {

	Exp condition;
	IStmt codeBlock;

	public WhileStmt(Exp condition2, IStmt block) {
		condition = condition2;
		codeBlock = block;
	}

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		MyIMap<String, Integer> tbl = state.getSymTable();
		MyIMap<Integer, Integer> heap = state.getHeap();
		MyIStack<IStmt> exeStack = state.getExeStack();

		if (condition.eval(tbl, heap) != 0) {
			exeStack.push(this);
			exeStack.push(codeBlock);
		}

		return state;
	}

	@Override
	public IStmt deepCopy() {
		return new WhileStmt(condition, codeBlock.deepCopy());
	}

	@Override
	public String toString() {
		return "while(" + condition.toString() + ") {\n\t" + codeBlock + "\n}";
	}

}
