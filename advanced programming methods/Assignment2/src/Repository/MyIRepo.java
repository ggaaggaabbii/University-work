package Repository;

import java.util.List;

import Model.PrgState;

public interface MyIRepo {

	void logPrgState(PrgState prg);

	void resetPtgState();

	List<PrgState> getPrgList();

	void setPrgList(List<PrgState> list);
}
