from model import *
import unittest

class tester(unittest.TestCase):

	def testList(self):
		List = MyList()
		List[1] = 2
		self.assertEqual(List[1], 2)
		List[2] = 3
		List['a'] = 1
		List[6] = 'a'
		keys = [1, 2, 'a', 6]
		values = [2, 3, 1, 'a']
		for i in range(4):
			self.assertEqual(List[keys[i]], values[i])

		for i in List:
			assert i in values


	def testSort(self):
		List = [2, 3, 1, 4, 2, 1]
		SortedList = [1, 1, 2, 2, 3, 4]
		SortedListDescending = [4, 3, 2, 2, 1, 1]
		sort(List)
		for i in range(len(List)):
			self.assertEqual(List[i], SortedList[i])
		sort(List, cmpFunc)
		for i in range(len(List)):
			self.assertEqual(List[i], SortedListDescending[i])

	def testFilter(self):
		List = ['aab', 'dadas', 'dsdd', 'dda']
		ResultList = ['aab', 'dadas', 'dda']
		List = Filter(List)
		for i in range(2):
			self.assertEqual(List[i], ResultList[i])


def filterFunc(a):
	return 'a' in a

def cmpFunc(a, b):
	return a > b

if __name__ == '__main__':
	tests = unittest.TestLoader().discover('.')
	unittest.TextTestRunner(verbosity = 2).run(tests)
