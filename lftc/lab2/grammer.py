class Grammer(object):
	def __init__(self, json):
		self.terminals = json["Terminals"]
		self.non_terminals = json["Non terminals"]
		self.productions = json["Productions"]
		self.start_symbol = json["Starting symbol"]

	def get_non_terminals(self):
		return self.non_terminals

	def get_terminals(self):
		return self.terminals

	def get_productions(self):
		s = ""
		for non_terminal in self.productions.keys():
			s += non_terminal
			s += " -> "
			for prod in self.productions[non_terminal]:
				for terminal in prod:
					s += terminal
				s += " | "
			s = s[:len(s) - 3]
			s += "\n"
		return s

	def get_productions_for_non_terminal(self, non_terminal):
		s = ""
		s += non_terminal
		s += " -> "
		for prod in self.productions[non_terminal]:
			for terminal in prod:
				s += terminal
			s += " | "
		s = s[:len(s) - 3]
		s += "\n"
		return s

	def is_regular(self):
		for non_terminal in self.productions.keys():
			for prod in self.productions[non_terminal]:
				if len(prod) > 2:
					return False
				if len(prod) == 1 and prod[0] not in self.terminals:
					print("aici")
					return False
				if len(prod) == 2:
					if prod[0] not in self.terminals:
						return False
					if prod[1] not in self.non_terminals:
						return False
				if prod[0] == "Ɛ" and non_terminal != self.start_symbol:
					return False
		return True

	def convert(self):
		return "Not implemented yet"	