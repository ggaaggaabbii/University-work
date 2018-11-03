package Model;

public class Pepper implements IWeightOfVegetables {
	int weightOfSeeds;
	int weightOfPepper;

	public Pepper(int weight) {
		this.weightOfPepper = weight / 2;
		this.weightOfSeeds = weight;
	}

	public int getWeight() {
		return weightOfPepper + weightOfSeeds;
	}

	public String toString() {
		return "Pepper of weight " + getWeight();
	}
}
