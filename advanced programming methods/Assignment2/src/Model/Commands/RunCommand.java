package Model.Commands;

import Controller.Ctrl;
import Model.Exceptions.MyStmtExecException;

public class RunCommand extends Command {
	Ctrl ctrl;

	public RunCommand(String key, String description) {
		super(key, description);
	}

	public void setCtrl(Ctrl ctrl) {
		this.ctrl = ctrl;
	}

	@Override
	public void execute() {
		try {
			ctrl.allSteps();
		} catch (MyStmtExecException e) {
			System.out.println(e.getMessage());
		}
	}

}
