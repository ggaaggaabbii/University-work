package Repository;

import Model.AppException;
import Model.IWeightOfVegetables;

public interface IRepo {
	IWeightOfVegetables[] getAll();

	void add(IWeightOfVegetables vegetable) throws AppException;

	void remove(int pos) throws AppException;

}
