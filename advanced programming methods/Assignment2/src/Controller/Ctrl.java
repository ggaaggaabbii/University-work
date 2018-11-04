package Controller;

import Model.PrgState;
import Model.ADTs.MyIList;
import Model.ADTs.MyIStack;
import Model.Exceptions.MyStmtExecException;
import Model.Stmt.IStmt;
import Repository.MyIRepo;

public class Ctrl {
	MyIRepo repo;
	boolean printFlag;

	PrgState oneStep(PrgState state) throws MyStmtExecException {
		MyIStack<IStmt> stack = state.getExeStack();
		if (stack.empty()) {
			throw new MyStmtExecException("Finished program");
		}
		IStmt crtStmt = stack.pop();
		return crtStmt.execute(state);
	}

	public void allSteps() throws MyStmtExecException {
		repo.resetPtgState();
		PrgState prgState = repo.getCrtProg();
		MyIStack<IStmt> stack = prgState.getExeStack();
		MyIList<Integer> output = prgState.getOut();

		while (!stack.empty()) {
			oneStep(prgState);
			if (printFlag) {
				repo.logPrgState();
			}
		}
	}

	public Ctrl(MyIRepo repo, boolean flag) {
		this.repo = repo;
		printFlag = flag;
	}
}
