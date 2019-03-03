import java.util.List;

public class BarrierEntry {
	private String id;
	private String barrCount;
	private String list;

	public BarrierEntry(String id, String barrCount, List<Integer> list) {
		this.id = id;
		this.barrCount = barrCount;
		this.list = "";
		for (Integer e : list) {
			this.list += e + " ";
		}
	}

	public String getId() {
		return id;
	}

	public String getBarrCount() {
		return barrCount;
	}

	public String getList() {
		return list;
	}

}
