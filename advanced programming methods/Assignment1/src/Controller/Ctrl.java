package Controller;

import Model.AppException;
import Model.IWeightOfVegetables;
import Repository.IRepo;

public class Ctrl {
	private IRepo repo;

	public Ctrl(IRepo repo) {
		this.repo = repo;
	}

	public IWeightOfVegetables[] getAll() {
		return repo.getAll();
	}

	public void add(IWeightOfVegetables e) throws AppException {
		repo.add(e);
	}

	public void remove(int pos) throws AppException {
		repo.remove(pos);
	}

	public IWeightOfVegetables[] filter(int weight) {
		IWeightOfVegetables[] filteredArray = new IWeightOfVegetables[200];
		IWeightOfVegetables[] vegetables = repo.getAll();
		int size = 0;
		for (int i = 0; i < vegetables.length; ++i) {
			if (vegetables[i].getWeight() > weight) {
				filteredArray[size++] = vegetables[i];
			}
		}
		return filteredArray;
	}
}
