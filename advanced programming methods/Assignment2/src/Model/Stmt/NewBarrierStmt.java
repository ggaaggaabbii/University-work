package Model.Stmt;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.Exp;
import javafx.util.Pair;

public class NewBarrierStmt implements IStmt {

	String var;
	Exp count;

	public NewBarrierStmt(String var, Exp count) {
		this.var = var;
		this.count = count;
	}

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		ReentrantReadWriteLock barrSync = state.getBarrSync();
		MyIMap<String, Integer> symTbl = state.getSymTable();
		MyIMap<Integer, Integer> heap = state.getHeap();
		MyIMap<Integer, Pair<Integer, List<Integer>>> barrTbl = state.getBarrierTable();
		Integer c = count.eval(symTbl, heap);

		Lock l = barrSync.writeLock();
		l.lock();
		Integer id = PrgState.getNewBarrId();
		symTbl.put(var, id);
		barrTbl.put(id, new Pair<Integer, List<Integer>>(c, new ArrayList<Integer>()));
		l.unlock();

		return null;
	}

	@Override
	public IStmt deepCopy() {
		return new NewBarrierStmt(var, count);
	}

	@Override
	public String toString() {
		return "newBarrier(" + var + ", " + count.toString() + ")";
	}

}
