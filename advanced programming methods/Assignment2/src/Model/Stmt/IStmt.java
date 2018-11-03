package Model.Stmt;

import Model.PrgState;
import Model.Exceptions.MyStmtExecException;

public interface IStmt {
	PrgState execute(PrgState state) throws MyStmtExecException;
}
