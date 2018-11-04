package Model.ADTs;

import java.util.Stack;

public class MyStack<E> implements MyIStack<E> {

	Stack<E> stack;

	@Override
	public boolean empty() {
		return stack.empty();
	}

	@Override
	public E peek() {
		return stack.peek();
	}

	@Override
	public E pop() {
		return stack.pop();
	}

	@Override
	public E push(E item) {
		return stack.push(item);
	}

	@Override
	public int search(Object o) {
		return stack.search(o);
	}

	public MyStack() {
		stack = new Stack<E>();
	}

	@Override
	public String toString() {
		String result = "";
		for (E a : stack) {
			result = a.toString() + "\n" + result;
		}
		return result;
	}
}
