public class Value {

	private final String Name;
	private final String Value;

	Value(String name, int value) {
		this.Name = new String(name);
		this.Value = new String("" + value);
	}

	public String getName() {
		return Name;
	}

	public String getValue() {
		return Value;
	}

}