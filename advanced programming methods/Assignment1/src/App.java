import Controller.Ctrl;
import Model.AppException;
import Model.Eggplant;
import Model.Pepper;
import Model.Tomatoe;
import Repository.ArrayRepo;
import View.ui;

public class App {
	public static void main(String[] args) {
		Tomatoe a = new Tomatoe(10);
		Eggplant b = new Eggplant(100);
		Pepper c = new Pepper(200);
		ArrayRepo repo = new ArrayRepo();
		try {
			repo.add(a);
			repo.add(b);
			repo.add(c);
		} catch (AppException e) {

		}
		Ctrl ctrl = new Ctrl(repo);
		ui ui = new ui(ctrl);
		ui.start();
	}
}
