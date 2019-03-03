package Repository;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReentrantReadWriteLock;

import Model.PrgState;
import Model.ADTs.MyIList;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.ADTs.MyList;
import Model.ADTs.MyMap;
import Model.ADTs.MyStack;
import Model.Stmt.IStmt;
import javafx.util.Pair;

public class Repo implements MyIRepo {

	IStmt originalProgram;
	List<PrgState> prgList;
	String logFilePath;

	public Repo(PrgState state, String logFilePath) {
		prgList = new ArrayList<PrgState>();
		prgList.add(state);
		originalProgram = state.getOriginalProgram();

		this.logFilePath = logFilePath;
	}

	@Override
	public void logPrgState(PrgState prg) {
		try {
			PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
			logFile.println(prg);
			logFile.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	@Override
	public void resetPtgState() {
		PrintWriter logFile;
		try {
			logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath)));
			logFile.print("");
			logFile.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		MyIStack<IStmt> stack = new MyStack<IStmt>();
		MyIList<Integer> output = new MyList<Integer>();
		MyIMap<String, Integer> symTable = new MyMap<String, Integer>();
		MyIMap<Integer, Pair<String, BufferedReader>> fileTable = new MyMap<Integer, Pair<String, BufferedReader>>();
		MyIMap<Integer, Integer> heap = new MyMap<Integer, Integer>();
		MyIMap<Integer, Pair<Integer, List<Integer>>> barrTbl = new MyMap<Integer, Pair<Integer, List<Integer>>>();
		ReentrantReadWriteLock barrSync = new ReentrantReadWriteLock();
		prgList = new ArrayList<PrgState>();

		prgList.add(
				new PrgState(stack, symTable, output, fileTable, heap, barrTbl, originalProgram.deepCopy(), barrSync));
	}

	@Override
	public List<PrgState> getPrgList() {
		return prgList;
	}

	@Override
	public void setPrgList(List<PrgState> list) {
		prgList = list;
	}
}
