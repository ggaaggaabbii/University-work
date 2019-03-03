package Model.Stmt;

import Model.PrgState;
import Model.ADTs.MyIStack;
import Model.Exceptions.MyStmtExecException;
import Model.Expresions.BooleanExp;
import Model.Expresions.Exp;

public class SwitchStmt implements IStmt {
	Exp SwitchExp;
	Exp exp1;
	Exp exp2;
	IStmt stmt1;
	IStmt stmt2;
	IStmt stmt3;

	public SwitchStmt(Exp exp, Exp exp1, IStmt stmt1, Exp exp2, IStmt stmt2, IStmt stmt3) {
		SwitchExp = exp;
		this.exp1 = exp1;
		this.exp2 = exp2;
		this.stmt1 = stmt1;
		this.stmt2 = stmt2;
		this.stmt3 = stmt3;
	}

	@Override
	public PrgState execute(PrgState state) throws MyStmtExecException {
		MyIStack<IStmt> exeStack = state.getExeStack();
		exeStack.push(new IfStmt(new BooleanExp("==", SwitchExp, exp1), stmt1,
				new IfStmt(new BooleanExp("==", SwitchExp, exp2), stmt2, stmt3)));
		return null;
	}

	@Override
	public IStmt deepCopy() {
		return new SwitchStmt(SwitchExp, exp1, stmt1.deepCopy(), exp2, stmt2.deepCopy(), stmt3.deepCopy());
	}

	@Override
	public String toString() {
		return "switch(" + SwitchExp.toString() + ")" + "\n" + "(case (" + exp1.toString() + ")" + " "
				+ stmt1.toString() + ")\n" + "(case (" + exp2.toString() + ")" + " " + stmt2.toString() + ")\n"
				+ "(default " + stmt3.toString() + ")";
	}

}
