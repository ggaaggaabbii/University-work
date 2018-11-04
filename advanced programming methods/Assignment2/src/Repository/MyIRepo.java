package Repository;

import Model.PrgState;

public interface MyIRepo {
	PrgState getCrtProg();

	void logPrgState();

	void resetPtgState();
}
