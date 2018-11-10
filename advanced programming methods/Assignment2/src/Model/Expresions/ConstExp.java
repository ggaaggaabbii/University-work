package Model.Expresions;

import Model.ADTs.MyIMap;

public class ConstExp extends Exp {

	int number;

	@Override
	public int eval(MyIMap<String, Integer> tbl, MyIMap<Integer, Integer> heap) {
		return number;
	}

	@Override
	public String toString() {
		return "" + number;
	}

	public ConstExp(int n) {
		number = n;
	}
}
