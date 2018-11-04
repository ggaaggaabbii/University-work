package Model.ADTs;

import java.util.HashMap;
import java.util.Set;

public class MyMap<K, V> implements MyIMap<K, V> {

	HashMap<K, V> map;

	@Override
	public void clear() {
		map.clear();
	}

	@Override
	public boolean containsKey(Object key) {
		return map.containsKey(key);
	}

	@Override
	public boolean containsValue(Object value) {
		return map.containsValue(value);
	}

	@Override
	public int size() {
		return map.size();
	}

	@Override
	public V remove(Object key) {
		return map.remove(key);
	}

	@Override
	public V get(Object key) {
		return map.get(key);
	}

	@Override
	public V put(K key, V value) {
		return map.put(key, value);
	}

	@Override
	public boolean isEmpty() {
		return map.isEmpty();
	}

	public MyMap() {
		map = new HashMap<K, V>();
	}

	@Override
	public String toString() {
		String result = "";
		for (K a : map.keySet()) {
			result += a.toString() + " -> " + map.get(a) + "\n";
		}
		return result;
	}

	@Override
	public Set<K> keySet() {
		return map.keySet();
	}
}
