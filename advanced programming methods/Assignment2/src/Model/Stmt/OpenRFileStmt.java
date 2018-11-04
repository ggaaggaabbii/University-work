package Model.Stmt;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.Exceptions.MyStmtExecException;
import javafx.util.Pair;

public class OpenRFileStmt implements IStmt {
	String varId;
	String fileName;

	public OpenRFileStmt(String id, String file) {
		varId = id;
		fileName = file;
	}

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		MyIStack<IStmt> exeStack = state.getExeStack();
		MyIMap<Integer, Pair<String, BufferedReader>> fileTable = state.getFileTable();
		MyIMap<String, Integer> tbl = state.getSymTable();
		for (Integer a : fileTable.keySet()) {
			if (fileTable.get(a).getKey() == fileName) {
				throw new MyStmtExecException("File opened 2 times: " + fileName);
			}
		}

		BufferedReader in;
		try {
			in = new BufferedReader(new FileReader(fileName));
		} catch (IOException e) {
			throw new MyStmtExecException("Could not open file: " + fileName);
		}
		Integer fileDescr = PrgState.getFileDescr();
		fileTable.put(fileDescr, new Pair<String, BufferedReader>(fileName, in));
		tbl.put(varId, fileDescr);
		return state;
	}

	@Override
	public IStmt deepCopy() {
		return new OpenRFileStmt(varId, fileName);
	}

	@Override
	public String toString() {
		return "openRFile(" + varId + ", \"" + fileName + "\")";
	}

}
