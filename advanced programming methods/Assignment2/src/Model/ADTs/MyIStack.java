package Model.ADTs;

public interface MyIStack<E> {
	boolean empty();

	E peek();

	E pop();

	E push(E item);

	int search(Object o);
}
