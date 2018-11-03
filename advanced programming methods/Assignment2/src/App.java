
import Controller.Ctrl;
import Model.PrgState;
import Model.ADTs.MyIList;
import Model.ADTs.MyIMap;
import Model.ADTs.MyIStack;
import Model.ADTs.MyList;
import Model.ADTs.MyMap;
import Model.ADTs.MyStack;
import Model.Expresions.ArithExp;
import Model.Expresions.ConstExp;
import Model.Expresions.VarExp;
import Model.Stmt.AssignStmt;
import Model.Stmt.CompStmt;
import Model.Stmt.IStmt;
import Model.Stmt.IfStmt;
import Model.Stmt.PrintStmt;
import Repository.Repo;
import View.Ui;

public class App {

	public static void main(String[] args) {
		boolean debugFlag = true;
		/*
		 * v=2;Print(v);Print(5+6)
		 */
		IStmt ex1 = new CompStmt(new CompStmt(new AssignStmt("v", new ConstExp(2)), new PrintStmt(new VarExp("v"))),
				new PrintStmt(new ArithExp("+", new ConstExp(5), new ConstExp(6))));
		/*
		 * a=2+3*5;b=a+1;Print(b)
		 */
		IStmt ex2 = new CompStmt(
				new AssignStmt("a",
						new ArithExp("+", new ConstExp(2), new ArithExp("*", new ConstExp(3), new ConstExp(5)))),
				new CompStmt(new AssignStmt("b", new ArithExp("+", new VarExp("a"), new ConstExp(1))),
						new PrintStmt(new VarExp("b"))));
		/*
		 * a=2-2;(If a Then v=2 Else v=3);Print(v)
		 */
		IStmt ex3 = new CompStmt(new AssignStmt("a", new ArithExp("-", new ConstExp(2), new ConstExp(2))), new CompStmt(
				new IfStmt(new VarExp("a"), new AssignStmt("v", new ConstExp(2)), new AssignStmt("v", new ConstExp(3))),
				new PrintStmt(new VarExp("v"))));
		/*
		 * a=4/0
		 */
		IStmt ex4 = new AssignStmt("a", new ArithExp("/", new ConstExp(4), new ConstExp(0)));

		/*
		 * a=b
		 */
		IStmt ex5 = new AssignStmt("a", new VarExp("b"));

		MyIStack<IStmt> stack = new MyStack<IStmt>();
		MyIList<Integer> output = new MyList<Integer>();
		MyIMap<String, Integer> symTable = new MyMap<String, Integer>();
		PrgState prgState = new PrgState(stack, symTable, output, ex3);
		Repo repo = new Repo(prgState);
		Ctrl ctrl = new Ctrl(repo, debugFlag);
		Ui ui = new Ui(ctrl);
		ui.start();
	}
}
