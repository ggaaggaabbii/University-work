package Controller;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

import Model.PrgState;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.ADTs.MyMap;
import Model.Exceptions.MyStmtExecException;
import Model.Stmt.IStmt;
import Repository.MyIRepo;
import javafx.util.Pair;

public class Ctrl {
	MyIRepo repo;
	boolean printFlag;
	ExecutorService executor;
	MyIMap<Integer, Pair<String, BufferedReader>> fileTable;

	PrgState oneStep(PrgState state) throws MyStmtExecException {
		MyIStack<IStmt> stack = state.getExeStack();
		if (stack.empty()) {
			throw new MyStmtExecException("Finished program");
		}
		IStmt crtStmt = stack.pop();
		return crtStmt.execute(state);
	}

	public void allSteps() throws MyStmtExecException {

		repo.resetPtgState();
		executor = Executors.newFixedThreadPool(2);
		List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());
		MyIMap<Integer, Integer> heap = prgList.get(0).getHeap();
		fileTable = repo.getPrgList().get(0).getFileTable();
		System.out.println(fileTable);

		while (prgList.size() > 0) {
			oneStepForAllPrg(prgList);
			MyIMap<String, Integer> tmpSymTable = new MyMap<String, Integer>();
			prgList.stream().map(p -> p.getSymTable()).forEach((p) -> {
				p.getContent().entrySet().stream().forEach((ent) -> {
					tmpSymTable.put(ent.getKey(), ent.getValue());
				});
			});
			heap.setContent(conservativeGarbageCollector(tmpSymTable.getContent().values(), heap));
			prgList = removeCompletedPrg(repo.getPrgList());
		}

		executor.shutdownNow();
		repo.setPrgList(prgList);
	}

	public void oneStepForAllPrg(List<PrgState> prgList) {
		List<Callable<PrgState>> callList = prgList.stream().map((PrgState p) -> (Callable<PrgState>) (() -> {
			return p.oneStep();
		})).collect(Collectors.toList());

		List<PrgState> newPrgList = null;
		try {
			newPrgList = executor.invokeAll(callList).stream().map(future -> {
				try {
					return future.get();
				} catch (InterruptedException | ExecutionException e) {
					e.printStackTrace();
					return null;
				}
			}).filter(p -> p != null).collect(Collectors.toList());
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		if (newPrgList != null) {
			prgList.addAll(newPrgList);
		}

		prgList.forEach(prg -> repo.logPrgState(prg));
		repo.setPrgList(prgList);
	}

	public Ctrl(MyIRepo repo, boolean flag) {
		this.repo = repo;
		printFlag = flag;
	}

	private MyIMap<Integer, Integer> conservativeGarbageCollector(Collection<Integer> symTableValues,
			MyIMap<Integer, Integer> heap) {
		return new MyMap<Integer, Integer>(heap.entrySet().stream().filter(e -> symTableValues.contains(e.getKey()))
				.collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue)));
	}

	public void closeAllFiles() throws MyStmtExecException {
		System.out.println("Closing remaining files");
		System.out.println(fileTable);

		fileTable.entrySet().stream().map(e -> e.getValue().getValue()).forEach(e -> {
			try {
				e.close();
			} catch (IOException ex) {
				System.out.println("Could not close file");
			}
		});
	}

	public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList) {
		return inPrgList.stream().filter(p -> p.isNotCompleted()).collect(Collectors.toList());
	}

}
