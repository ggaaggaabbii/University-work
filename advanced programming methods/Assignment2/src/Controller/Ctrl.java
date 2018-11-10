package Controller;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Collection;
import java.util.Map;
import java.util.stream.Collectors;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.ADTs.MyMap;
import Model.Exceptions.MyStmtExecException;
import Model.Stmt.IStmt;
import Repository.MyIRepo;
import javafx.util.Pair;

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
		MyIMap<Integer, Integer> heap = prgState.getHeap();
		MyIMap<String, Integer> symTable = prgState.getSymTable();

		while (!stack.empty()) {
			oneStep(prgState);
			heap.setContent(conservativeGarbageCollector(symTable.getContent().values(), heap));

			if (printFlag) {
				repo.logPrgState();
			}
		}
	}

	public Ctrl(MyIRepo repo, boolean flag) {
		this.repo = repo;
		printFlag = flag;
	}

	private MyIMap<Integer, Integer> conservativeGarbageCollector(Collection<Integer> symTableValues,
			MyIMap<Integer, Integer> heap) {
		return new MyMap<Integer, Integer>(heap.entrySet().stream().filter(e -> symTableValues.contains(e.getKey()))
				.collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue)));
	}

	public void closeAllFiles() throws MyStmtExecException {
		MyIMap<Integer, Pair<String, BufferedReader>> fileTable = repo.getCrtProg().getFileTable();

		for (Integer fileDesc : fileTable.keySet()) {
			Pair<String, BufferedReader> file = fileTable.get(fileDesc);
			BufferedReader fileReader = file.getValue();
			try {
				fileReader.close();
			} catch (IOException e) {
				throw new MyStmtExecException("Error trying to close file:" + file.getKey());
			}
		}
	}
}
