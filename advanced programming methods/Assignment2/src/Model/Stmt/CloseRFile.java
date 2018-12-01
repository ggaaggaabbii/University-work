package Model.Stmt;

import java.io.BufferedReader;
import java.io.IOException;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.Exp;
import javafx.util.Pair;

public class CloseRFile implements IStmt {
	Exp fileId;

	public CloseRFile(Exp fileId) {
		this.fileId = fileId;
	}

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		MyIStack<IStmt> exeStack = state.getExeStack();
		MyIMap<Integer, Pair<String, BufferedReader>> fileTable = state.getFileTable();
		MyIMap<String, Integer> tbl = state.getSymTable();
		MyIMap<Integer, Integer> heap = state.getHeap();

		Integer fileDresc = fileId.eval(tbl, heap);
		Pair<String, BufferedReader> file = fileTable.get(fileDresc);
		if (file == null) {
			throw new MyStmtExecException("Invalid file descriptor");
		}
		BufferedReader in = file.getValue();
		try {
			in.close();
		} catch (IOException e) {
			throw new MyStmtExecException("File could not be closed: " + file.getKey());
		}
		fileTable.remove(fileDresc);
		return null;
	}

	@Override
	public IStmt deepCopy() {
		return new CloseRFile(fileId);
	}

	@Override
	public String toString() {
		return "closeRFile(" + fileId.toString() + ")";
	}
}
