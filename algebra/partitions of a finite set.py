f = open('output.out', 'w')
current_partition = 0

def get_total(n):
	"""
	calculate the number of partitions using the Bell number dynamic
	"""
	A = []
	A.append([1])
	for i in range(1, n):
		A.append([])
		A[i].append(A[i - 1][i - 1])
		for j in range(1, i + 1):
			A[i].append(A[i][j - 1] + A[i - 1][j - 1])
	return A[n - 1][n - 1]

def initialize_list(v, n):
	"""
	initialize the first configuration with 1, 1, 1, ... 1
	"""
	for i in range(0, n + 1):	
		v.append(1)

def valid_conf(v, n):
	"""
	check if a configuration is valid
	"""
	w = []
	Min = n + 1
	Max = 0
	nr = 0
	for i in range(0, n + 1):
		w.append(0)
	"""
	check if the current subsets are indexed correctly starting from 1
	"""
	for i in range(1, n + 1):
		if v[i] < Min:
			Min = v[i]
		if v[i] > Max:
			Max = v[i]
		if w[v[i]] == 0:
			w[v[i]] = 1
			nr += 1
	"""
	if not every subset index is contained in a configuration it is invalid
	"""
	if Max - Min + 1 != nr:
		return False
	for i in range(0, n + 1):
		w[i] = 0
	"""
	check if the smallest number from each subset form an ascending sequence
	"""
	for i in range(1, n + 1):
		if w[v[i]] == 0:
			w[v[i]] = i
	for i in range(1, nr):
		if w[i] > w[i + 1]:
			return False
	return True

def show_partition(v, n):
	"""
	use the global counter of partitions to show the index of the current partition
	"""
	global current_partition
	A = []
	for i in range(0, n + 1):
		A.append([])
	"""
	each element from the set A goes to the coresponding subset for this partition
	"""
	for i in range(1, n + 1):
		A[v[i]].append(i)
	current_partition += 1
	print("Partition No. " + str(current_partition), file = f)
	for i in A:
		if i != []:
			print(i, file = f)
	print("with the equivalance relations:", file = f)
	for i in A:
		for j in i:
			for k in i:
				print("(" + str(j) + ", " + str(k) + ")", file = f)

def bktr(v, n):
	"""
	loop through the numbers from 1111...1 to 123...n in base n + 1 where each number represents a configuration of a partition
	"""
	for i in range (1, n ** n + 1):
		v[n] += 1
		t = 0
		if v[n] == n + 1:
			v[n] = 1
			t = 1
		pos = n - 1
		while t > 0 and pos > 0:
			v[pos] += 1
			if v[pos] == pos + 1 and pos != 1:
				v[pos] = 1
				pos -= 1
			else:
				t = 0
		"""
		when v[1] reaches the value of 2, that means we passed the 123...n limit
		"""
		if v[1] == 2:
			break
		"""
		if the current configuration forms a valid partition, print it to the file
		"""
		if valid_conf(v, n):
			show_partition(v, n)

def main():
	v = []
	n = int(input("give a number: "))
	initialize_list(v, n)
	v[n] = 0
	print("Total number of partitions: " + str(get_total(n)), file = f)
	if n <= 10:
		bktr(v, n)
	
main()
