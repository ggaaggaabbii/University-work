package Model;

import java.io.BufferedReader;

import Model.ADTs.MyIList;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.Exceptions.MyStmtExecException;
import Model.Stmt.IStmt;
import javafx.util.Pair;

public class PrgState {
	MyIStack<IStmt> exeStack;
	MyIList<Integer> out;
	MyIMap<String, Integer> symTable;
	MyIMap<Integer, Pair<String, BufferedReader>> FileTable;
	MyIMap<Integer, Integer> Heap;
	IStmt originalProgram;
	Integer id;

	static Integer fileId = 0;
	static Integer idCounter = 0;

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

	public void setHeap(MyIMap<Integer, Integer> heap) {
		Heap = heap;
	}

	public MyIMap<Integer, Integer> getHeap() {
		return Heap;
	}

	public PrgState(MyIStack<IStmt> stk, MyIMap<String, Integer> symtbl, MyIList<Integer> ot,
			MyIMap<Integer, Pair<String, BufferedReader>> ft, MyIMap<Integer, Integer> heap, IStmt prg) {
		exeStack = stk;
		symTable = symtbl;
		out = ot;
		FileTable = ft;
		Heap = heap;
		originalProgram = prg.deepCopy();
		exeStack.push(prg);
		id = getNewId();
	}

	@Override
	public String toString() {
		return "Prg state " + id.toString() + ":\nExeStack:\n" + exeStack.toString() + "SymTable:\n"
				+ symTable.toString() + "Out:\n" + out.toString() + "FileTable:\n" + FileTable.toString() + "Heap:\n"
				+ Heap.toString();
	}

	public static Integer getFileDescr() {
		++fileId;
		return fileId;
	}

	public static Integer getNewId() {
		++idCounter;
		return idCounter;
	}

	public boolean isNotCompleted() {
		return !exeStack.empty();
	}

	public PrgState oneStep() throws MyStmtExecException {
		if (exeStack.empty()) {
			throw new MyStmtExecException("Empty exe stack");
		}
		IStmt crtStmt = exeStack.pop();
		return crtStmt.execute(this);
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public Integer getId() {
		return id;
	}
}
