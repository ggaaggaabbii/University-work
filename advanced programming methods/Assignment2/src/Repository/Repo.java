package Repository;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

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

	PrgState crtState;
	String logFilePath;

	@Override
	public PrgState getCrtProg() {
		return crtState;
	}

	public Repo(PrgState state, String logFilePath) {
		crtState = state;
		this.logFilePath = logFilePath;
	}

	@Override
	public void logPrgState() {
		try {
			PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
			logFile.println(crtState);
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

		IStmt originalProgram = crtState.getOriginalProgram();
		MyIStack<IStmt> stack = new MyStack<IStmt>();
		MyIList<Integer> output = new MyList<Integer>();
		MyIMap<String, Integer> symTable = new MyMap<String, Integer>();
		MyIMap<Integer, Pair<String, BufferedReader>> fileTable = new MyMap<Integer, Pair<String, BufferedReader>>();
		MyIMap<Integer, Integer> heap = new MyMap<Integer, Integer>();

		crtState = new PrgState(stack, symTable, output, fileTable, heap, originalProgram.deepCopy());
	}
}
