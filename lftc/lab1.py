import re

separators = ['==', '<=', '>=', '->', '<<', '>>', '<', '>', '=', '\+', '\-', '\/', '\*', '{', '}', '\(', '\)', ' ', '\t', ';']
white_spaces = [' ', '\n', '\t', '']
reserved_words = ['for', 'while', 'if', 'else', 'int', 'char', 'string', 'Struct', 'cin', 'cout']
operators = ['+', '-', '*', '/', '=', '<', '<=', '==', '>=', '>', '>>', '<<', '->']

FILE_NAME = 'main.in'

class SymTable(object):
	def __init__(self):
		self.content = []
		self.head = -1

	def add_token(self, token):
		if self.head == -1:
			self.content.append([token, -1])
			self.head = 0
			return 0
	
		current = self.head
		prev = -1
		while current != -1 and self.content[current][0] < token:
			prev = current
			current = self.content[current][1]

		if current == -1:
			self.content.append([token, -1])
			self.content[prev][1] = len(self.content) - 1
			return self.content[prev][1]

		if self.content[current][0] == token:
			return current

		if prev == -1:
			self.content.append([token, current])
			self.head = len(self.content) - 1
			return len(self.content) - 1

		self.content.append([token, current])
		self.content[prev][1] = len(self.content) - 1

		return len(self.content) - 1

	def __str__(self):
		s = "SymTable:\n"
		for x in self.content:
			s += str(x) + "\n"
		return s


class PIF():
	"""docstring for PIF"""
	def __init__(self):
		self.content = []

	def add_to_pif(self, token, sym_table_position):
		self.content.append((token, sym_table_position))

	def __str__(self):
		s = "PIF:\n"
		for x in self.content:
			s += str(x) + "\n"
		return s		

def is_identifier(token):
	parser = re.compile('^[a-zA-Z][a-zA-Z0-9]*$')
	match = parser.match(token)
	return match

def is_constant(token):
	int_parser = re.compile('^0$|^([-+]?[1-9][0-9]*)$')
	match = int_parser.match(token)
	if match:
		return True
	string_parser = re.compile('^\"[0-9a-zA-A]*\"$')
	match = string_parser.match(token)
	if match:
		return True
	char_parser = re.compile('^\'[0-9a-zA-A]\'$')
	match = char_parser.match(token)
	return match

def clear_white_spaces(content):
	new_content = []
	for i in range(len(content) - 1):
		if content[i] in white_spaces:
			continue
		else:
			new_content.append(content[i])
	if content[len(content) - 1] not in white_spaces:
		new_content.append(content[len(content) - 1])
	return new_content

def search_line(token):
	with open(FILE_NAME) as f:
		counter = 1
		for line in f:
			if token in line:
				return counter
			counter += 1

if __name__ == '__main__':

	pif = PIF()
	st = SymTable()

	tokens = []
	codification_table = {}

	with open(FILE_NAME) as f:
		content = f.read()
		new_content = re.split("\n", content)
		temp = []
		for separator in separators:
			temp = []
			for token in new_content:
				to_be_splitted = token[:]
				if to_be_splitted in separators:
					temp.append(to_be_splitted)
					continue
				after_split = re.split('(' + separator + ')', to_be_splitted)
				for x in after_split:
					temp.append(x)
			new_content = temp
		tokens = temp

	tokens = clear_white_spaces(tokens)

	with open('cod_table.in') as f:
		for line in f:
			line = line.split()
			codification_table[line[0].strip()] = int(line[1].strip())

	print(tokens)

	for token in tokens:
		if token in reserved_words or token in operators or token in separators:
			pif.add_to_pif(codification_table[token], -1)
		elif is_identifier(token):
			pos = st.add_token(token)
			pif.add_to_pif(codification_table['identifier'], pos)
		elif is_constant(token):
			pos = st.add_token(token)
			pif.add_to_pif(codification_table['constant'], pos)
		else:
			print('lexical error on token ' + token + ' on line ' + str(search_line(token)))
			break

	print(pif)
	print(st)


