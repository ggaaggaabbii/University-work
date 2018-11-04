package Model;

import java.io.BufferedReader;

import Model.ADTs.MyIList;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.Stmt.IStmt;
import javafx.util.Pair;

public class PrgState {
	MyIStack<IStmt> exeStack;
	MyIList<Integer> out;
	MyIMap<String, Integer> symTable;
	MyIMap<Integer, Pair<String, BufferedReader>> FileTable;
	IStmt originalProgram;

	static Integer fileId = 0;

	public MyIStack<IStmt> getExeStack() {
		return exeStack;
	}

	public void setExeStack(MyIStack<IStmt> exeStack) {
		this.exeStack = exeStack;
	}

	public MyIList<Integer> getOut() {
		return out;
	}

	public void setOut(MyIList<Integer> out) {
		this.out = out;
	}

	public MyIMap<String, Integer> getSymTable() {
		return symTable;
	}

	public void setSymTable(MyIMap<String, Integer> symTable) {
		this.symTable = symTable;
	}

	public IStmt getOriginalProgram() {
		return originalProgram;
	}

	public void setOriginalProgram(IStmt originalProgram) {
		this.originalProgram = originalProgram;
	}

	public MyIMap<Integer, Pair<String, BufferedReader>> getFileTable() {
		return FileTable;
	}

	public void setFileTable(MyIMap<Integer, Pair<String, BufferedReader>> fileTable) {
		FileTable = fileTable;
	}

	public PrgState(MyIStack<IStmt> stk, MyIMap<String, Integer> symtbl, MyIList<Integer> ot,
			MyIMap<Integer, Pair<String, BufferedReader>> ft, IStmt prg) {
		exeStack = stk;
		symTable = symtbl;
		out = ot;
		FileTable = ft;
		originalProgram = prg.deepCopy();
		exeStack.push(prg);
	}

	@Override
	public String toString() {
		return "Prg state:\nExeStack:\n" + exeStack.toString() + "SymTable:\n" + symTable.toString() + "Out:\n"
				+ out.toString();
	}

	public static Integer getFileDescr() {
		++fileId;
		return fileId;
	}

}
