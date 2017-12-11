import unittest
import sys
sys.path.append('./..')
from controller.controller import controller
from model.operand import operand

class tester(unittest.TestCase):

	def testApp(self):
		CT = controller()
		#additions
		a = CT.addition([2, "11100111001110101", "1101111011111"])
		assert str(a) == "11110101001010100"
		a = CT.addition([6, "23045", "100254"])
		assert str(a) == "123343"
		a = CT.addition([16, "54AB6F", "CD097D"])
		assert str(a) == "121B4EC"
		a = CT.addition([3, "2122012", "10112222"])
		assert str(a) == "20012011"
		a = CT.addition([4, "3220013", "22303231"])
		assert str(a) == "32123310"
		a = CT.addition([5, "3401323", "444033"])
		assert str(a) == "4400411"
		a = CT.addition([7, "6543210", "664455"])
		assert str(a) == "10540665"
		a = CT.addition([8, "5677034", "1234567"])
		assert str(a) == "7133623"
		a = CT.addition([16, "ABCDE", "D9037F"])
		assert str(a) == "E3C05D"
		a = CT.addition([2, "1100101011", "11101101"])
		assert str(a) == "10000011000"


		#substractions
		a = CT.substraction([2, "10001100010", "1110111011"])
		assert str(a) == "10100111"
		a = CT.substraction([9, "102387", "64502"])
		assert str(a) == "26785"
		a = CT.substraction([16, "501BA", "32ED"])
		assert str(a) == "4CECD"
		a = CT.substraction([8, "130046", "71257"])
		assert str(a) == "36567"
		a = CT.substraction([7, "210354", "55466"])
		assert str(a) == "121555"
		a = CT.substraction([6, "210354", "44355"])
		assert str(a) == "121555"
		a = CT.substraction([5, "102003", "3333"])
		assert str(a) == "43120"
		a = CT.substraction([4, "102003", "3333"])
		assert str(a) == "32010"
		a = CT.substraction([2, "100111000", "1100111"])
		assert str(a) == "11010001"
		a = CT.substraction([16, "10B009", "A5FCD"])
		assert str(a) == "6503C"
	

		#multiplications
		a = CT.multiplicationWithOneDigit([8, "7023", 5])
		assert str(a) == "43137"
		a = CT.multiplicationWithOneDigit([16, "32001B", 6])
		assert str(a) == "12C00A2"
		a = CT.multiplicationWithOneDigit([7, "12345", 5])
		assert str(a) == "65424"
		a = CT.multiplicationWithOneDigit([6, "12345", 5])
		assert str(a) == "111101"
		a = CT.multiplicationWithOneDigit([5, "31203", 3])
		assert str(a) == "144114"
		a = CT.multiplicationWithOneDigit([4, "31203", 3])
		assert str(a) == "220221"
		a = CT.multiplicationWithOneDigit([8, "21563", 7])
		assert str(a) == "174045"
		a = CT.multiplicationWithOneDigit([16, "A23F4", 11])
		assert str(a) == "6F8B7C"


		#division
		a = CT.divisionWithOneDigit([3, "20101", 2])
		assert str(a[0]) == "10012"
		assert str(a[1]) == "0"
		a = CT.divisionWithOneDigit([16, "1FED0205", 9])
		assert str(a[0]) == "38C1CAB"
		assert str(a[1]) == "2"
		a = CT.divisionWithOneDigit([8, "120456", 6])
		assert str(a[0]) == "15335"
		assert str(a[1]) == "0"
		a = CT.divisionWithOneDigit([7, "120456", 6])
		assert str(a[0]) == "13421"
		assert str(a[1]) == "0"
		a = CT.divisionWithOneDigit([5, "321023", 3])
		assert str(a[0]) == "103322"
		assert str(a[1]) == "2"
		a = CT.divisionWithOneDigit([4, "321023", 3])
		assert str(a[0]) == "103003"
		assert str(a[1]) == "2"
		a = CT.divisionWithOneDigit([16, "2A0F86", 14])
		assert str(a[0]) == "3011B"
		assert str(a[1]) == "C"
		a = CT.divisionWithOneDigit([8, "765433", 4])
		assert str(a[0]) == "175306"
		assert str(a[1]) == "3"


		#conversion
		a = CT.rapidConversion([2, "10000001101100", 8])
		assert str(a) == "20154"
		a = CT.rapidConversion([2, "11110010000001001010", 16])
		assert str(a) == "F204A"
		a = CT.rapidConversion([8, "11024", 2])
		assert str(a) == "1001000010100"
		a = CT.rapidConversion([16, "BC13F", 2])
		assert str(a) == "10111100000100111111"
		a = CT.rapidConversion([4, "1230", 8])
		assert str(a) == "154"
		a = CT.rapidConversion([16, "AB650", 8])
		assert str(a) == "2533120"
		a = CT.rapidConversion([16, "1C3D", 4])
		assert str(a) == "1300331"
		a = CT.rapidConversion([8, "63401", 16])
		assert str(a) == "6701"
		a = CT.conversionWithBase10([10, "3842", 5])
		assert str(a) == "110332"
		a = CT.conversionWithBase10([10, "10379", 7])
		assert str(a) == "42155"
		a = CT.conversionWithBase10([10, "2653", 6])
		assert str(a) == "20141"
		a = CT.conversionWithBase10([10, "222", 2])
		assert str(a) == "11011110"
		a = CT.conversionWithBase10([4, "3210", 10])
		assert str(a) == "228"
		a = CT.conversionWithBase10([5, "3041", 10])
		assert str(a) == "396"
		a = CT.conversionWithBase10([8, "1735", 10])
		assert str(a) == "989"
		a = CT.conversionWithBase10([2, "10111010011", 10])
		assert str(a) == "1491"
		a = CT.substitutionMethod([3, "2122", 5])
		assert str(a) == "241"
		a = CT.substitutionMethod([5, "1043", 7])
		assert str(a) == "301"
		a = CT.substitutionMethod([4, "2013", 6])
		assert str(a) == "343"
		a = CT.substitutionMethod([6, "1054", 16])
		assert str(a) == "FA"
		a = CT.succesiveDivisions([8, "1467", 5])
		assert str(a) == "11243"
		a = CT.succesiveDivisions([7, "2510", 3])
		assert str(a) == "1021202"
		a = CT.succesiveDivisions([9, "7048", 4])
		assert str(a) == "1100123"
		a = CT.succesiveDivisions([16, "BC0D", 6])
		assert str(a) == "1010513"


if __name__ == '__main__':
	tests = unittest.TestLoader().discover('.')
	unittest.TextTestRunner(verbosity = 2).run(tests)
