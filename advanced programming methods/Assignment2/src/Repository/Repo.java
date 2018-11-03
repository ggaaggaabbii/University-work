package Repository;

import Model.PrgState;

public class Repo implements MyIRepo {

	PrgState crtState;

	@Override
	public PrgState getCrtProg() {
		return crtState;
	}

	public Repo(PrgState state) {
		crtState = state;
	}
}
