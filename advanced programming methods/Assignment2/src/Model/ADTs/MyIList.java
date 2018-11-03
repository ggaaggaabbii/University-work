package Model.ADTs;

public interface MyIList<E> {
	boolean add(E e);

	void add(int index, E element);

	void clear();

	E get(int index);

	int size();

	boolean contains(Object o);
}
