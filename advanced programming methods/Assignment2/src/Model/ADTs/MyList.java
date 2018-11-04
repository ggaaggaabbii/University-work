package Model.ADTs;

import java.util.ArrayList;

public class MyList<E> implements MyIList<E> {

	ArrayList<E> list;

	@Override
	public boolean add(E e) {
		return list.add(e);
	}

	@Override
	public void add(int index, E element) {
		list.add(index, element);
	}

	@Override
	public void clear() {
		list.clear();
	}

	@Override
	public E get(int index) {
		return list.get(index);
	}

	@Override
	public int size() {
		return list.size();
	}

	@Override
	public boolean contains(Object o) {
		return list.contains(o);
	}

	public MyList() {
		list = new ArrayList<E>();
	}

	@Override
	public String toString() {
		String result = "";
		for (E a : list) {
			result += a.toString() + "\n";
		}
		return result + "";
	}
}
