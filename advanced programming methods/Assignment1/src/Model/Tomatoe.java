package Model;

public class Tomatoe implements IWeightOfVegetables {
	int weight;

	public Tomatoe(int weight) {
		this.weight = weight;
	}

	public int getWeight() {
		return 2 * weight;
	}

	public String toString() {
		return "Tomatoe of weight " + getWeight();
	}
}
