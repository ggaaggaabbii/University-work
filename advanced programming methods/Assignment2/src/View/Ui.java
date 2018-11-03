package View;

import Controller.Ctrl;
import Model.Exceptions.MyStmtExecException;

public class Ui {
	Ctrl ctrl;

	public void start() {
		try {
			ctrl.allSteps();
		} catch (MyStmtExecException e) {
			System.out.println(e.getMessage());
		}
	}

	public Ui(Ctrl ctrl) {
		this.ctrl = ctrl;
	}
}
