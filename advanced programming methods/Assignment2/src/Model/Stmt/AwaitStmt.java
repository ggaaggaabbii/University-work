package Model.Stmt;

import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.Exceptions.MyStmtExecException;
import javafx.util.Pair;

public class AwaitStmt implements IStmt {

	String var;

	public AwaitStmt(String var) {
		this.var = var;
	}

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		ReentrantReadWriteLock barrSync = state.getBarrSync();
		MyIMap<String, Integer> tbl = state.getSymTable();
		MyIStack<IStmt> exeStack = state.getExeStack();
		Integer id = tbl.get(var);
		if (id == null) {
			throw new MyStmtExecException("Invalid barrier" + var);
		}
		Lock lock = barrSync.readLock();
		lock.lock();
		MyIMap<Integer, Pair<Integer, List<Integer>>> barrTbl = state.getBarrierTable();
		Pair<Integer, List<Integer>> entry = barrTbl.get(id);
		List<Integer> barrList = entry.getValue();

		Integer length = barrList.size();
		Boolean found = false;
		if (length < entry.getKey()) {
			for (Integer i : barrList) {
				if (i == state.getId()) {
					found = true;
					break;
				}
			}
			if (!found) {
				barrList.add(state.getId());
			}
			exeStack.push(new AwaitStmt(var));
		}

		lock.unlock();

		return null;
	}

	@Override
	public IStmt deepCopy() {
		return new AwaitStmt(var);
	}

	@Override
	public String toString() {
		return "await(" + var + ")";
	}

}
