package View;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import Model.Commands.Command;

public class Ui {
	private Map<String, Command> commands;

	public Ui() {
		commands = new HashMap<>();
	}

	public void addCommand(Command c) {
		commands.put(c.getKey(), c);
	}

	private void printMenu() {
		for (Command com : commands.values()) {
			String line = String.format("%s. %s", com.getKey(), com.getDescription());
			System.out.println(line);
		}
	}

	public void show() {
		@SuppressWarnings("resource")
		Scanner scanner = new Scanner(System.in);
		while (true) {
			printMenu();
			System.out.printf("Input the option: ");
			String key = scanner.nextLine();
			Command com = commands.get(key);
			if (com == null) {
				System.out.println("Invalid Option");
				continue;
			}
			com.execute();
		}
	}
}
