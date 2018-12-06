package Model.Stmt;

import Model.PrgState;
import Model.ADTs.MyMap;
import Model.ADTs.MyStack;
import Model.Exceptions.MyStmtExecException;

public class ForkStmt implements IStmt {

	IStmt forkBody;

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		PrgState childProcess = new PrgState(new MyStack<IStmt>(),
				new MyMap<String, Integer>(state.getSymTable().getContent()), state.getOut(), state.getFileTable(),
				state.getHeap(), forkBody);
		childProcess.setId(PrgState.getNewId());
		return childProcess;
	}

	@Override
	public IStmt deepCopy() {
		return new ForkStmt(forkBody.deepCopy());
	}

	public ForkStmt(IStmt body) {
		forkBody = body;
	}

	@Override
	public String toString() {
		return "fork(" + forkBody + ")";
	}
}
