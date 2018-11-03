package View;

import java.util.Scanner;

import Controller.Ctrl;
import Model.AppException;
import Model.Eggplant;
import Model.IWeightOfVegetables;
import Model.Pepper;
import Model.Tomatoe;

public class ui {
	private Ctrl ctrl;
	private Scanner reader;

	public ui(Ctrl ctrl) {
		reader = new Scanner(System.in);
		this.ctrl = ctrl;
	}

	public void printMenu() {
		System.out.println("0. Exit");
		System.out.println("1. Show");
		System.out.println("2. Filter");
		System.out.println("3. Add");
		System.out.println("4. Remove");
	}

	public void printVegetables() {
		IWeightOfVegetables[] vegetables = ctrl.getAll();
		for (int i = 0; i < vegetables.length; ++i) {
			if (vegetables[i] == null) {
				return;
			}
			System.out.println("\t" + (i + 1) + ": " + vegetables[i].toString());
		}
	}

	public void filter() {
		int weight;
		try {
			reader.nextLine();
			weight = reader.nextInt();
		} catch (Exception e) {
			System.out.println("Weight is not an integer");
			reader.nextLine();
			return;
		}
		IWeightOfVegetables[] vegetables = ctrl.filter(weight);
		for (int i = 0; i < vegetables.length; ++i) {
			if (vegetables[i] == null) {
				return;
			}
			System.out.println("\t" + (i + 1) + ": " + vegetables[i].toString());
		}
	}

	public void add() throws AppException {
		reader.nextLine();
		String input = reader.nextLine();
		String[] strings = input.split(" ");
		int weight;
		IWeightOfVegetables vegetable;
		if (strings.length != 2) {
			System.out.println("Invalid vegetable");
		}
		// make sure the weight is an integer
		try {
			weight = Integer.parseInt(strings[1]);
		} catch (Exception e) {
			System.out.println("Weight is not an integer");
			return;
		}

		// check the type of the vegetable
		if (strings[0].toLowerCase().equals("tomatoe")) {
			vegetable = new Tomatoe(weight);
			ctrl.add(vegetable);
			return;
		}
		if (strings[0].toLowerCase().equals("eggplant")) {
			vegetable = new Eggplant(weight);
			ctrl.add(vegetable);
			return;
		}
		if (strings[0].toLowerCase().equals("pepper")) {
			vegetable = new Pepper(weight);
			ctrl.add(vegetable);
			return;
		}
		System.out.println("Unknown vegetable type");
	}

	public void remove() throws AppException {
		reader.nextLine();
		String line = reader.nextLine();
		int pos;
		try {
			pos = Integer.parseInt(line);
		} catch (Exception e) {
			System.out.println("Positions is not an iteger");
			return;
		}
		ctrl.remove(pos - 1);
	}

	public void start() {
		while (true) {
			printMenu();
			try {
				int option = reader.nextInt();
				try {
					if (option == 0) {
						break;
					} else if (option == 1) {
						printVegetables();
					} else if (option == 2) {
						filter();
					} else if (option == 3) {
						add();
					} else if (option == 4) {
						remove();
					} else {
						System.out.println("Unknown option");
					}
				} catch (AppException e) {
					System.out.println(e.getText());
				}
			} catch (Exception e) {
				reader.nextLine();
				System.out.println("Invalid input");
			}
		}
	}
}
