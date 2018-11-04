package Model.Stmt;

import java.io.BufferedReader;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.Exp;
import javafx.util.Pair;

public class ReadFileStmt implements IStmt {
	Exp fileId;
	String varName;

	public ReadFileStmt(Exp fileId, String varName) {
		this.fileId = fileId;
		this.varName = varName;
	}

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		MyIStack<IStmt> exeStack = state.getExeStack();
		MyIMap<Integer, Pair<String, BufferedReader>> fileTable = state.getFileTable();
		MyIMap<String, Integer> tbl = state.getSymTable();

		Integer fileDresc = fileId.eval(tbl);
		Pair<String, BufferedReader> file = fileTable.get(fileDresc);
		if (file == null) {
			throw new MyStmtExecException("Invalid file descriptor");
		}

		BufferedReader in = file.getValue();
		Integer nextInt;
		try {
			nextInt = Integer.parseInt(in.readLine());
		} catch (Exception e) {
			throw new MyStmtExecException("Invalid input from the file");
		}

		tbl.put(varName, nextInt);
		return state;
	}

	@Override
	public IStmt deepCopy() {
		return new ReadFileStmt(fileId, varName);
	}

	@Override
	public String toString() {
		return "readFile(" + fileId.toString() + ", " + varName + ")";
	}
}
