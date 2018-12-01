package Model.Stmt;

import java.io.BufferedReader;

import Model.PrgState;
import Model.ADTs.MyIMap;
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
		MyIMap<Integer, Pair<String, BufferedReader>> fileTable = state.getFileTable();
		MyIMap<String, Integer> tbl = state.getSymTable();
		MyIMap<Integer, Integer> heap = state.getHeap();

		Integer fileDresc = fileId.eval(tbl, heap);
		Pair<String, BufferedReader> file = fileTable.get(fileDresc);
		if (file == null) {
			throw new MyStmtExecException("Invalid file descriptor");
		}

		BufferedReader in = file.getValue();
		Integer nextInt;
		try {
			nextInt = Integer.parseInt(in.readLine());
		} catch (Exception e) {
			nextInt = 0;
		}

		tbl.put(varName, nextInt);
		return null;
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
