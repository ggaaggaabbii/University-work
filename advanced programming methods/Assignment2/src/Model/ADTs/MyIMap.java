package Model.ADTs;

import java.util.Set;

public interface MyIMap<K, V> {
	void clear();

	boolean containsKey(Object key);

	boolean containsValue(Object value);

	int size();

	V remove(Object key);

	V get(Object key);

	V put(K key, V value);

	boolean isEmpty();

	Set<K> keySet();
}
