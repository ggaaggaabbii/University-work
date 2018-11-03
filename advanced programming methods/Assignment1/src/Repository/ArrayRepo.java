package Repository;

import Model.AppException;
import Model.IWeightOfVegetables;

public class ArrayRepo implements IRepo {
	IWeightOfVegetables[] vegetables;
	int size;

	public ArrayRepo() {
		vegetables = new IWeightOfVegetables[200];
		size = 0;
	}

	@Override
	public IWeightOfVegetables[] getAll() {
		IWeightOfVegetables[] repo = new IWeightOfVegetables[size];
		for (int i = 0; i < size; ++i) {
			repo[i] = vegetables[i];
		}
		return repo;
	}

	@Override
	public void add(IWeightOfVegetables vegetable) throws AppException {
		if (size == vegetables.length) {
			throw new AppException("Full array");
		}
		vegetables[size++] = vegetable;
	}

	@Override
	public void remove(int pos) throws AppException {
		if (pos > size || pos < 0) {
			throw new AppException("Invalid position");
		}
		vegetables[pos] = vegetables[size - 1];
		vegetables[--size] = null;
	}

}
