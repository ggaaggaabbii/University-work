
import java.io.BufferedReader;

import Controller.Ctrl;
import Model.PrgState;
import Model.ADTs.MyIList;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.ADTs.MyList;
import Model.ADTs.MyMap;
import Model.ADTs.MyStack;
import Model.Commands.ExitCommand;
import Model.Commands.RunCommand;
import Model.Expresions.ArithExp;
import Model.Expresions.ConstExp;
import Model.Expresions.ReadHeapExp;
import Model.Expresions.VarExp;
import Model.Stmt.AssignStmt;
import Model.Stmt.CloseRFile;
import Model.Stmt.CompStmt;
import Model.Stmt.HeapAllocStmt;
import Model.Stmt.IStmt;
import Model.Stmt.IfStmt;
import Model.Stmt.OpenRFileStmt;
import Model.Stmt.PrintStmt;
import Model.Stmt.ReadFileStmt;
import Model.Stmt.WriteHeapStmt;
import Repository.Repo;
import View.Ui;
import javafx.util.Pair;

public class App {

	public static void main(String[] args) {
		boolean debugFlag = true;
		IStmt[] examples = new IStmt[14];

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

		Ui ui = new Ui();
		ExitCommand exitCommand = new ExitCommand("0", "Exit");
		ui.addCommand(exitCommand);

		for (Integer i = 1; i < examples.length + 1; ++i) {
			// initialize data structures for the program state
			MyIStack<IStmt> stack = new MyStack<IStmt>();
			MyIList<Integer> output = new MyList<Integer>();
			MyIMap<String, Integer> symTable = new MyMap<String, Integer>();
			MyIMap<Integer, Pair<String, BufferedReader>> fileTable = new MyMap<Integer, Pair<String, BufferedReader>>();
			MyIMap<Integer, Integer> heap = new MyMap<Integer, Integer>();

			PrgState prgState = new PrgState(stack, symTable, output, fileTable, heap, examples[i - 1]);
			Repo repo = new Repo(prgState, "File" + i.toString() + ".log");
			Ctrl ctrl = new Ctrl(repo, debugFlag);
			RunCommand runCommand = new RunCommand(i.toString(),
					"Run exemple " + i.toString() + ": (" + examples[i - 1].toString() + ")");
			runCommand.setCtrl(ctrl);
			ui.addCommand(runCommand);
		}

		ui.show();
	}
}
