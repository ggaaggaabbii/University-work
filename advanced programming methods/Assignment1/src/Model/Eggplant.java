package Model;

public class Eggplant implements IWeightOfVegetables {
	int weight;

	public Eggplant(int weight) {
		this.weight = weight;
	}

	public int getWeight() {
		return 10;
	}

	public String toString() {
		return "Eggplant of weight " + getWeight();
	}
}
