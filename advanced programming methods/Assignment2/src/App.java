
import java.io.BufferedReader;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.ReentrantReadWriteLock;

import Controller.Ctrl;
import Model.PrgState;
import Model.ADTs.MyIList;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.ADTs.MyList;
import Model.ADTs.MyMap;
import Model.ADTs.MyStack;
import Model.Commands.Command;
import Model.Commands.ExitCommand;
import Model.Commands.RunCommand;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.ArithExp;
import Model.Expresions.BooleanExp;
import Model.Expresions.ConstExp;
import Model.Expresions.ReadHeapExp;
import Model.Expresions.VarExp;
import Model.Stmt.AssignStmt;
import Model.Stmt.AwaitStmt;
import Model.Stmt.CloseRFile;
import Model.Stmt.CompStmt;
import Model.Stmt.ForkStmt;
import Model.Stmt.HeapAllocStmt;
import Model.Stmt.IStmt;
import Model.Stmt.IfStmt;
import Model.Stmt.NewBarrierStmt;
import Model.Stmt.OpenRFileStmt;
import Model.Stmt.PrintStmt;
import Model.Stmt.ReadFileStmt;
import Model.Stmt.SwitchStmt;
import Model.Stmt.WhileStmt;
import Model.Stmt.WriteHeapStmt;
import Repository.MyIRepo;
import Repository.Repo;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.util.Pair;

public class App extends Application {
	private static int MAXN = 20;
	private static Map<String, Command> commands;
	private static IStmt[] examples;
	private static Ctrl currentController;
	private static PrgState selectedPrg = null;
	private static javafx.scene.control.TextField PrgCount;
	private static HBox buttons;
	private static Button choosePrg;
	private static Button oneStep;
	private static Button allSteps;
	private static GridPane layout;
	private static VBox allComponents;
	private static HBox lists;
	private static ListView<String> prgList;
	private static ListView<String> exeStack;
	private static ListView<String> out;
	private static HBox maps;
	private static TableView<Value> symTable;
	private static TableView<HeapPair> heap;
	private static TableView<FilePair> fileTable;
	private static TableView<BarrierEntry> BarrierTable;

	public static void updateInterface() {
		prgList.getItems().clear();
		List<PrgState> prgs = currentController.getRepo().getPrgList();
		for (int i = 0; i < prgs.size(); ++i) {
			prgList.getItems().add(prgs.get(i).getId().toString());
		}

		if (selectedPrg != null) {
			MyIStack<IStmt> exeStk = selectedPrg.getExeStack();
			exeStack.getItems().clear();
			exeStack.getItems().add(exeStk.toString());
			MyIList<Integer> output = selectedPrg.getOut();
			out.getItems().clear();
			out.getItems().add(output.toString());

			MyIMap<String, Integer> symTbl = selectedPrg.getSymTable();
			MyIMap<Integer, Pair<String, BufferedReader>> fileTbl = selectedPrg.getFileTable();
			MyIMap<Integer, Integer> hep = selectedPrg.getHeap();
			MyIMap<Integer, Pair<Integer, List<Integer>>> barrs = selectedPrg.getBarrierTable();

			final ObservableList<Value> data = FXCollections.observableArrayList();

			for (String string : symTbl.keySet()) {
				data.add(new Value(string, symTbl.get(string)));
			}

			final ObservableList<FilePair> fileData = FXCollections.observableArrayList();

			for (int i : fileTbl.keySet()) {
				fileData.add(new FilePair("" + i, fileTbl.get(i).getKey()));
			}

			final ObservableList<HeapPair> heapData = FXCollections.observableArrayList();

			for (int i : hep.keySet()) {
				heapData.add(new HeapPair("" + i, "" + hep.get(i)));
			}

			final ObservableList<BarrierEntry> barrData = FXCollections.observableArrayList();

			for (int i : barrs.keySet()) {
				barrData.add(new BarrierEntry("" + i, "" + barrs.get(i).getKey(), barrs.get(i).getValue()));
			}

			symTable.setItems(data);
			fileTable.setItems(fileData);
			heap.setItems(heapData);
			BarrierTable.setItems(barrData);
		}
	}

	public static void clearAll() {
		exeStack.getItems().clear();
		out.getItems().clear();
		PrgCount.clear();
		fileTable.getItems().clear();
		symTable.getItems().clear();
		heap.getItems().clear();
		BarrierTable.getItems().clear();
	}

	public static void initializeLists() {
		prgList = new ListView<String>();
		exeStack = new ListView<String>();
		out = new ListView<String>();

		prgList.setOnMouseClicked(new EventHandler<MouseEvent>() {

			@Override
			public void handle(MouseEvent event) {
				int row = prgList.getSelectionModel().getSelectedIndex();
				if (row == -1) {
					return;
				}
				List<PrgState> list = currentController.getRepo().getPrgList();
				selectedPrg = list.get(row);
				PrgCount.setText(selectedPrg.getId().toString());
				updateInterface();
			}

		});

		lists = new HBox();
		lists.getChildren().add(prgList);
		lists.getChildren().add(exeStack);
		lists.getChildren().add(out);

		allComponents.getChildren().add(lists);

	}

	public static void initializeButtons() {
		allComponents = new VBox();
		choosePrg = new Button();
		choosePrg.setText("Choose Program");
		choosePrg.setOnAction((ActionEvent event) -> {
			Stage stage = new Stage();
			stage.setTitle("Select Program");
			stage.initModality(Modality.WINDOW_MODAL);
			ListView<String> listView = new ListView<String>();
			for (int i = 0; i < MAXN; ++i) {
				listView.getItems().add((i + 1) + " " + examples[i].toString());
			}
			listView.setOnMouseClicked(new EventHandler<MouseEvent>() {

				@Override
				public void handle(MouseEvent event) {
					int row = listView.getSelectionModel().getSelectedIndex();
					currentController = commands.get("" + (row + 1)).getCtrl();
					oneStep.setDisable(false);
					allSteps.setDisable(false);
					updateInterface();
					selectedPrg = null;
					clearAll();
					stage.close();
				}

			});

			VBox layout = new VBox();
			layout.getChildren().add(listView);

			GridPane grid = new GridPane();
			grid.addColumn(0, layout);
			Scene s = new Scene(grid);
			stage.setScene(s);
			stage.show();
		});
		buttons = new HBox();
		buttons.getChildren().add(choosePrg);
		PrgCount = new javafx.scene.control.TextField();
		PrgCount.setPromptText("Program Count");
		PrgCount.setEditable(false);
		buttons.getChildren().add(PrgCount);
		oneStep = new Button();
		oneStep.setText("OneStep");
		oneStep.setDisable(true);
		oneStep.setOnAction((ActionEvent event) -> {
			MyIRepo repo = currentController.getRepo();
			List<PrgState> prgList = currentController.removeCompletedPrg(repo.getPrgList());
			currentController.oneStepForAllPrg(prgList);
			MyIMap<String, Integer> tmpSymTable = new MyMap<String, Integer>();
			prgList.stream().map(p -> p.getSymTable()).forEach((p) -> {
				p.getContent().entrySet().stream().forEach((ent) -> {
					tmpSymTable.put(ent.getKey(), ent.getValue());
				});
			});
			try {
				prgList.get(0).getHeap().setContent(currentController
						.conservativeGarbageCollector(tmpSymTable.getContent().values(), prgList.get(0).getHeap()));
			} catch (Exception e) {
				System.out.println("No program left to execute");
			}
			updateInterface();
		});
		allSteps = new Button();
		allSteps.setText("AllSteps");
		allSteps.setDisable(true);
		allSteps.setOnAction((ActionEvent event) -> {
			try {
				currentController.allSteps();
			} catch (MyStmtExecException e) {
				System.out.println(e.getMessage());
			}
			updateInterface();
		});
		buttons.getChildren().add(oneStep);
		buttons.getChildren().add(allSteps);
		allComponents.getChildren().add(buttons);
		layout = new GridPane();
		layout.addColumn(0, allComponents);
	}

	@SuppressWarnings("unchecked")
	public static void initializeMaps() {
		maps = new HBox();
		symTable = new TableView<Value>();
		heap = new TableView<HeapPair>();
		fileTable = new TableView<FilePair>();
		BarrierTable = new TableView<BarrierEntry>();

		maps.getChildren().add(symTable);
		maps.getChildren().add(heap);
		maps.getChildren().add(fileTable);
		maps.getChildren().add(BarrierTable);

		@SuppressWarnings("rawtypes")
		TableColumn var = new TableColumn("Name");
		var.setCellValueFactory(new PropertyValueFactory<Value, String>("Name"));
		@SuppressWarnings("rawtypes")
		TableColumn value = new TableColumn("Value");
		value.setCellValueFactory(new PropertyValueFactory<Value, String>("Value"));

		symTable.getColumns().addAll(var, value);

		@SuppressWarnings("rawtypes")
		TableColumn id = new TableColumn("Id");
		id.setCellValueFactory(new PropertyValueFactory<FilePair, String>("id"));
		@SuppressWarnings("rawtypes")
		TableColumn name = new TableColumn("FileName");
		name.setCellValueFactory(new PropertyValueFactory<FilePair, String>("fileName"));

		fileTable.getColumns().addAll(id, name);

		@SuppressWarnings("rawtypes")
		TableColumn adr = new TableColumn("Address");
		adr.setCellValueFactory(new PropertyValueFactory<HeapPair, String>("adr"));
		@SuppressWarnings("rawtypes")
		TableColumn val = new TableColumn("Value");
		val.setCellValueFactory(new PropertyValueFactory<HeapPair, String>("value"));

		heap.getColumns().addAll(adr, val);

		@SuppressWarnings("rawtypes")
		TableColumn barrId = new TableColumn("Id");
		barrId.setCellValueFactory(new PropertyValueFactory<BarrierEntry, String>("id"));

		@SuppressWarnings("rawtypes")
		TableColumn count = new TableColumn("Count");
		count.setCellValueFactory(new PropertyValueFactory<BarrierEntry, String>("barrCount"));

		@SuppressWarnings("rawtypes")
		TableColumn barrList = new TableColumn("List");
		barrList.setCellValueFactory(new PropertyValueFactory<BarrierEntry, String>("list"));

		BarrierTable.getColumns().addAll(barrId, count, barrList);

		allComponents.getChildren().add(maps);

	}

	public static void addCommand(Command c) {
		commands.put(c.getKey(), c);
	}

	public static void initializeExamples() {
		/*
		 * v=2;Print(v);Print(5+6)
		 */
		examples[0] = new CompStmt(new CompStmt(new AssignStmt("v", new ConstExp(2)), new PrintStmt(new VarExp("v"))),
				new PrintStmt(new ArithExp("+", new ConstExp(5), new ConstExp(6))));
		/*
		 * a=2+3*5;b=a+1;Print(b)
		 */
		examples[1] = new CompStmt(
				new AssignStmt("a",
						new ArithExp("+", new ConstExp(2), new ArithExp("*", new ConstExp(3), new ConstExp(5)))),
				new CompStmt(new AssignStmt("b", new ArithExp("+", new VarExp("a"), new ConstExp(1))),
						new PrintStmt(new VarExp("b"))));
		/*
		 * a=2-2;(If a Then v=2 Else v=3);Print(v)
		 */
		examples[2] = new CompStmt(new AssignStmt("a", new ArithExp("-", new ConstExp(2), new ConstExp(2))),
				new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ConstExp(2)),
						new AssignStmt("v", new ConstExp(3))), new PrintStmt(new VarExp("v"))));
		/*
		 * a=4/0
		 */
		examples[3] = new AssignStmt("a", new ArithExp("/", new ConstExp(4), new ConstExp(0)));

		/*
		 * a=b
		 */
		examples[4] = new AssignStmt("a", new VarExp("b"));
		/*
		 * openRFile(var_f,"test.in"); readFile(var_f,var_c); print(var_c); (if var_c
		 * then readFile(var_f,var_c); print(var_c) else print(0)); closeRFile(var_f)
		 */
		examples[5] = new CompStmt(new OpenRFileStmt("var_f", "test.in"),
				new CompStmt(new ReadFileStmt(new VarExp("var_f"), "var_c"),
						new CompStmt(new PrintStmt(new VarExp("var_c")), new CompStmt(
								new IfStmt(new VarExp("var_c"),
										new CompStmt(new ReadFileStmt(new VarExp("var_f"), "var_c"),
												new PrintStmt(new VarExp("var_c"))),
										new PrintStmt(new ConstExp(0))),
								new CloseRFile(new VarExp("var_f"))))));
		/*
		 * test1.in file does not exist openRFile(var_f,"tes1.in");
		 * readFile(var_f,var_c); print(var_c); (if var_c then readFile(var_f,var_c);
		 * print(var_c) else print(0)); closeRFile(var_f)
		 */
		examples[6] = new CompStmt(new OpenRFileStmt("var_f", "test1.in"),
				new CompStmt(new ReadFileStmt(new VarExp("var_f"), "var_c"),
						new CompStmt(new PrintStmt(new VarExp("var_c")), new CompStmt(
								new IfStmt(new VarExp("var_c"),
										new CompStmt(new ReadFileStmt(new VarExp("var_f"), "var_c"),
												new PrintStmt(new VarExp("var_c"))),
										new PrintStmt(new ConstExp(0))),
								new CloseRFile(new VarExp("var_f"))))));
		/*
		 * openRFile(var_f,"test.in"); readFile(var_f + 2,var_c); print(var_c); (if
		 * var_c then readFile(var_f,var_c); print(var_c) else print(0));
		 * closeRFile(var_f)
		 */
		examples[7] = new CompStmt(new OpenRFileStmt("var_f", "test.in"),
				new CompStmt(new ReadFileStmt(new ArithExp("+", new VarExp("var_f"), new ConstExp(2)), "var_c"),
						new CompStmt(new PrintStmt(new VarExp("var_c")), new CompStmt(
								new IfStmt(new VarExp("var_c"),
										new CompStmt(new ReadFileStmt(new VarExp("var_f"), "var_c"),
												new PrintStmt(new VarExp("var_c"))),
										new PrintStmt(new ConstExp(0))),
								new CloseRFile(new VarExp("var_f"))))));
		/*
		 * test2.in is an empty file openRFile(var_f,"test2.in"); readFile(var_f,var_c);
		 * print(var_c); (if var_c then readFile(var_f,var_c); print(var_c) else
		 * print(0)); closeRFile(var_f)
		 */
		examples[8] = new CompStmt(new OpenRFileStmt("var_f", "test2.in"),
				new CompStmt(new ReadFileStmt(new VarExp("var_f"), "var_c"),
						new CompStmt(new PrintStmt(new VarExp("var_c")), new CompStmt(
								new IfStmt(new VarExp("var_c"),
										new CompStmt(new ReadFileStmt(new VarExp("var_f"), "var_c"),
												new PrintStmt(new VarExp("var_c"))),
										new PrintStmt(new ConstExp(0))),
								new CloseRFile(new VarExp("var_f"))))));

		/*
		 * readFile(var_f,var_c); print(var_c); (if var_c then readFile(var_f,var_c);
		 * print(var_c) else print(0)); closeRFile(var_f)
		 */
		examples[9] = new CompStmt(new ReadFileStmt(new VarExp("var_f"), "var_c"),
				new CompStmt(new PrintStmt(new VarExp("var_c")),
						new CompStmt(
								new IfStmt(new VarExp("var_c"),
										new CompStmt(new ReadFileStmt(new VarExp("var_f"), "var_c"),
												new PrintStmt(new VarExp("var_c"))),
										new PrintStmt(new ConstExp(0))),
								new CloseRFile(new VarExp("var_f")))));

		/*
		 * v=10;new(v,20);new(a,22);print(v)
		 */
		examples[10] = new CompStmt(new AssignStmt("v", new ConstExp(10)),
				new CompStmt(new HeapAllocStmt("v", new ConstExp(20)),
						new CompStmt(new HeapAllocStmt("a", new ConstExp(22)), new PrintStmt(new VarExp("v")))));

		/*
		 * v=10;new(v,20);new(a,22);print(100+rH(v));print(100+rH(a))
		 */
		examples[11] = new CompStmt(new AssignStmt("v", new ConstExp(10)),
				new CompStmt(new HeapAllocStmt("v", new ConstExp(20)),
						new CompStmt(new HeapAllocStmt("a", new ConstExp(22)),
								new CompStmt(new PrintStmt(new ArithExp("+", new ConstExp(100), new ReadHeapExp("v"))),
										new PrintStmt(new ArithExp("+", new ConstExp(100), new ReadHeapExp("a")))))));
		/*
		 * v=10;new(v,20);new(a,22);wH(a,30);print(a);print(rH(a))
		 */
		examples[12] = new CompStmt(new AssignStmt("v", new ConstExp(10)),
				new CompStmt(new HeapAllocStmt("v", new ConstExp(20)),
						new CompStmt(new HeapAllocStmt("a", new ConstExp(22)), new CompStmt(
								new WriteHeapStmt("a", new ConstExp(30)),
								new CompStmt(new PrintStmt(new VarExp("a")), new PrintStmt(new ReadHeapExp("a")))))));
		/*
		 * v=10;new(v,20);new(a,22);wH(a,30);print(a);print(rH(a));a=0
		 */
		examples[13] = new CompStmt(new AssignStmt("v", new ConstExp(10)),
				new CompStmt(new HeapAllocStmt("v", new ConstExp(20)),
						new CompStmt(new HeapAllocStmt("a", new ConstExp(22)),
								new CompStmt(new WriteHeapStmt("a", new ConstExp(30)),
										new CompStmt(new PrintStmt(new VarExp("a")),
												new CompStmt(new PrintStmt(new ReadHeapExp("a")),
														new AssignStmt("a", new ConstExp(10))))))));

		/*
		 * print(10 + (2<6)) //should print 11
		 */
		examples[14] = new PrintStmt(
				new ArithExp("+", new ConstExp(10), new BooleanExp("<", new ConstExp(2), new ConstExp(6))));

		/*
		 * v=6; (while (v-4) print(v);v=v-1);print(v)
		 */
		examples[15] = new CompStmt(new AssignStmt("v", new ConstExp(6)), new CompStmt(
				new WhileStmt(
						new BooleanExp("!=", new ArithExp("-", new VarExp("v"), new ConstExp(4)), new ConstExp(0)),
						new CompStmt(new PrintStmt(new VarExp("v")),
								new AssignStmt("v", new ArithExp("-", new VarExp("v"), new ConstExp(1))))),
				new PrintStmt(new VarExp("v"))));
		/*
		 * v=10;new(a,22); fork(wH(a,30);v=32;print(v);print(rH(a)));
		 * print(v);print(rH(a))
		 */
		examples[16] = new CompStmt(new AssignStmt("v", new ConstExp(10)),
				new CompStmt(new HeapAllocStmt("a", new ConstExp(22)),
						new CompStmt(
								new ForkStmt(new CompStmt(new WriteHeapStmt("a", new ConstExp(30)),
										new CompStmt(new AssignStmt("v", new ConstExp(32)),
												new CompStmt(new PrintStmt(new VarExp("v")),
														new PrintStmt(new ReadHeapExp("a")))))),
								new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new ReadHeapExp("a"))))));

		/*
		 * fork(fork(print(10))); fork(print(11));
		 */
		examples[17] = new CompStmt(new ForkStmt(new ForkStmt(new PrintStmt(new ConstExp(10)))),
				new ForkStmt(new PrintStmt(new ConstExp(11))));

		/*
		 * a=1;b=2;c=5; switch(a*10) (case (b*c) print(a);print(b)) (case (10)
		 * print(100);print(200)) (default print(300)); print(300)
		 */
		examples[18] = new CompStmt(new AssignStmt("a", new ConstExp(1)),
				new CompStmt(new AssignStmt("b", new ConstExp(2)),
						new CompStmt(new AssignStmt("c", new ConstExp(5)), new CompStmt(
								new SwitchStmt(new ArithExp("*", new VarExp("a"), new ConstExp(10)),
										new ArithExp("*", new VarExp("b"), new VarExp("c")),
										new CompStmt(new PrintStmt(new VarExp("a")), new PrintStmt(new VarExp("b"))),
										new ConstExp(10),
										new CompStmt(new PrintStmt(new ConstExp(100)),
												new PrintStmt(new ConstExp(200))),
										new PrintStmt(new ConstExp(300))),
								new PrintStmt(new ConstExp(300))))));
		/*
		 * new(v1,2);new(v2,3);new(v3,4);newBarrier(cnt,rH(v2));
		 * fork(await(cnt);wh(v1,rh(v1)*10));print(rh(v1)));
		 * fork(await(cnt);wh(v2,rh(v2)*10));wh(v2,rh(v2)*10));print(rh(v2)));
		 * await(cnt); print(rH(v3))
		 */
		examples[19] = new CompStmt(
				new CompStmt(new CompStmt(new HeapAllocStmt("v1", new ConstExp(2)),
						new CompStmt(new HeapAllocStmt("v2", new ConstExp(3)),
								new CompStmt(new HeapAllocStmt("v3", new ConstExp(4)),
										new NewBarrierStmt("cnt", new ReadHeapExp("v2"))))),
						new ForkStmt(new CompStmt(new AwaitStmt("cnt"),
								new CompStmt(
										new WriteHeapStmt("v1",
												new ArithExp("*", new ReadHeapExp("v1"), new ConstExp(10))),
										new PrintStmt(new ReadHeapExp("v1")))))),
				new CompStmt(
						new ForkStmt(
								new CompStmt(new AwaitStmt("cnt"),
										new CompStmt(
												new CompStmt(
														new WriteHeapStmt("v2",
																new ArithExp("*", new ReadHeapExp("v2"),
																		new ConstExp(10))),
														new WriteHeapStmt("v2",
																new ArithExp("*", new ReadHeapExp("v2"),
																		new ConstExp(10)))),
												new PrintStmt(new ReadHeapExp("v2"))))),
						new CompStmt(new AwaitStmt("cnt"), new PrintStmt(new ReadHeapExp("v3")))));

	}

	public static void main(String[] args) {
		boolean debugFlag = true;
		examples = new IStmt[MAXN];
		commands = new HashMap<>();

		initializeExamples();

		// Ui ui = new Ui();
		ExitCommand exitCommand = new ExitCommand("0", "Exit");
		// ui.addCommand(exitCommand);
		addCommand(exitCommand);

		for (Integer i = 1; i < examples.length + 1; ++i) {
			// initialize data structures for the program state
			MyIStack<IStmt> stack = new MyStack<IStmt>();
			MyIList<Integer> output = new MyList<Integer>();
			MyIMap<String, Integer> symTable = new MyMap<String, Integer>();
			MyIMap<Integer, Pair<String, BufferedReader>> fileTable = new MyMap<Integer, Pair<String, BufferedReader>>();
			MyIMap<Integer, Integer> heap = new MyMap<Integer, Integer>();
			MyIMap<Integer, Pair<Integer, List<Integer>>> barrTbl = new MyMap<Integer, Pair<Integer, List<Integer>>>();
			ReentrantReadWriteLock barrSync = new ReentrantReadWriteLock();

			PrgState prgState = new PrgState(stack, symTable, output, fileTable, heap, barrTbl, examples[i - 1],
					barrSync);
			Repo repo = new Repo(prgState, "File" + i.toString() + ".log");
			Ctrl ctrl = new Ctrl(repo, debugFlag);
			RunCommand runCommand = new RunCommand(i.toString(),
					"Run exemple " + i.toString() + ": (" + examples[i - 1].toString() + ")");
			runCommand.setCtrl(ctrl);
			// ui.addCommand(runCommand);
			addCommand(runCommand);
		}

		// ui.show();
		launch(args);
	}

	@Override
	public void start(Stage primaryStage) throws Exception {

		initializeButtons();
		initializeLists();
		initializeMaps();

		final Scene scene = new Scene(layout);
		primaryStage.setTitle("ToyLanguageInterpretor");
		primaryStage.setScene(scene);
		primaryStage.show();

	}
}
