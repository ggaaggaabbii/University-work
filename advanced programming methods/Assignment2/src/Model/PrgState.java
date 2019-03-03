package Model;

import java.io.BufferedReader;
import java.util.List;
import java.util.concurrent.locks.ReentrantReadWriteLock;

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
	MyIMap<Integer, Pair<Integer, List<Integer>>> BarrierTable;
	IStmt originalProgram;
	ReentrantReadWriteLock barrSync;
	Integer id;

	static Integer fileId = 0;
	static Integer idCounter = 0;
	static Integer barrierCounter = 0;

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

	public ReentrantReadWriteLock getBarrSync() {
		return barrSync;
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

	public MyIMap<Integer, Pair<Integer, List<Integer>>> getBarrierTable() {
		return BarrierTable;
	}

	public void setBarrierTable(MyIMap<Integer, Pair<Integer, List<Integer>>> barrierTable) {
		BarrierTable = barrierTable;
	}

	public PrgState(MyIStack<IStmt> stk, MyIMap<String, Integer> symtbl, MyIList<Integer> ot,
			MyIMap<Integer, Pair<String, BufferedReader>> ft, MyIMap<Integer, Integer> heap,
			MyIMap<Integer, Pair<Integer, List<Integer>>> barrTbl, IStmt prg, ReentrantReadWriteLock barrSync) {
		exeStack = stk;
		symTable = symtbl;
		out = ot;
		FileTable = ft;
		Heap = heap;
		originalProgram = prg.deepCopy();
		exeStack.push(prg);
		BarrierTable = barrTbl;
		id = getNewId();
		this.barrSync = barrSync;
	}

	@Override
	public String toString() {
		return "Prg state " + id.toString() + ":\nExeStack:\n" + exeStack.toString() + "SymTable:\n"
				+ symTable.toString() + "Out:\n" + out.toString() + "FileTable:\n" + FileTable.toString() + "Heap:\n"
				+ Heap.toString() + "BarrierTable:\n" + BarrierTable.toString();
	}

	public static Integer getFileDescr() {
		++fileId;
		return fileId;
	}

	public static Integer getNewId() {
		++idCounter;
		return idCounter;
	}

	public static Integer getNewBarrId() {
		++barrierCounter;
		return barrierCounter;
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
