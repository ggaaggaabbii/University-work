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
		if (printFlag) {
			System.out.println(crtStmt);
		}
		return crtStmt.execute(state);
	}

	public void allSteps() throws MyStmtExecException {
		PrgState prgState = repo.getCrtProg();
		MyIStack<IStmt> stack = prgState.getExeStack();
		MyIList<Integer> output = prgState.getOut();

		while (!stack.empty()) {
			oneStep(prgState);
			if (printFlag) {
				System.out.println(prgState);
			}
		}

		for (int i = 0; i < output.size(); ++i) {
			System.out.println(output.get(i));
		}
	}

	public Ctrl(MyIRepo repo, boolean flag) {
		this.repo = repo;
		printFlag = flag;
	}
}
