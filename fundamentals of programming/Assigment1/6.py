months = [0, 1, -1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1]

import datetime

now = datetime.datetime.now()

def check_bisect(n):
	if n % 400 == 0 or (n % 100 != 0 and n % 4 == 0):
		return True
	return False

def sum_of_days_between(a, b):
	Sum = 0
	for i in range(a + 1, b):
		if check_bisect(i):
			Sum += 366
		else:
			Sum += 365
	return Sum

def sum_of_months(start, stop, year):
	Sum = 0
	for i in range(start, stop):
		if months[i] == 1:
			Sum += 31
		elif months[i] == 0:
			Sum += 30
		elif check_bisect(year):
			Sum += 29
		else:
			Sum += 28
	return Sum

def sum_of_current_year(a, b):
	Sum = 0
	if yearofbirth < currentyear:
		start = 1
		Sum += a
	else:
		start = monthofbirth + 1
		if monthofbirth < b:
			if months[monthofbirth] == 1:
				Sum += 31 - dayofbirth
			elif months[monthofbirth] == 0:
				Sum += 30 - dayofbirth
			elif check_bisect(yearofbirth):
				Sum += 29 - dayofbirth
			else:
				Sum += 28 - dayofbirth
			Sum += a + 1
		else:
			Sum += a - dayofbirth + 1
	Sum += sum_of_months(start, b, currentyear)
	return Sum

def sum_of_birthyear(a, b):
	Sum = 0	
	if yearofbirth < currentyear:
		start = 13
	else:
		return 0
	Sum += sum_of_months(b, start, yearofbirth)
	Sum -= dayofbirth
	return Sum + 1

a = raw_input("introduce your birthday(ex: 01.03.2001): ")

dayofbirth = int(a[:2])
monthofbirth = int(a[3:5])
yearofbirth = int(a[6:])

currentday = now.day
currentmonth = now.month
currentyear = now.year

if currentday > 31 or dayofbirth > 31:
	print("Error")
elif currentmonth > 12 or monthofbirth > 12:
	print("Error")
elif currentyear < yearofbirth:
	print("Error")
elif currentyear == yearofbirth and currentmonth < monthofbirth:
	print("Error")
elif currentyear == yearofbirth and currentmonth == monthofbirth and currentday < dayofbirth:
	print("Error")
else:
	result = sum_of_days_between(yearofbirth, currentyear)
	result += sum_of_current_year(currentday, currentmonth)
	result += sum_of_birthyear(dayofbirth, monthofbirth)

	print("you are " + str(result) + " days old")
