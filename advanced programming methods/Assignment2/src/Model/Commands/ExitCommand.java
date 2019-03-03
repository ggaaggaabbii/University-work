package Model.Commands;

import Controller.Ctrl;

public class ExitCommand extends Command {
	public ExitCommand(String key, String desc) {
		super(key, desc);
	}

	@Override
	public void execute() {
		System.exit(0);
	}

	@Override
	public Ctrl getCtrl() {
		// TODO Auto-generated method stub
		return null;
	}
}