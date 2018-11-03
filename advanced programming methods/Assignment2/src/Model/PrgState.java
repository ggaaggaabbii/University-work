package Model;

import Model.ADTs.MyIList;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.Stmt.IStmt;

public class PrgState {
	MyIStack<IStmt> exeStack;
	MyIList<Integer> out;
	MyIMap<String, Integer> symTable;
	IStmt originalProgram;

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

	public PrgState(MyIStack<IStmt> stk, MyIMap<String, Integer> symtbl, MyIList<Integer> ot, IStmt prg) {
		exeStack = stk;
		symTable = symtbl;
		out = ot;
		// originalProgram = deepCopy(prg);
		exeStack.push(prg);
	}

	@Override
	public String toString() {
		return "Prg state:\nExeStack: " + exeStack.toString() + "\nSymTable: " + symTable.toString() + "\nOut: "
				+ out.toString() + "\n";
	}
}
