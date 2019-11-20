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
		s = ""
		s += "States: ["
		for st in self.non_terminals:
			s += st
			s += ", "
		s += "final_state"
		s += "]\n"
		s += "Alphabet: ["
		for al in self.terminals:
			s += al
			s += ", "
		s = s[:len(s) - 2]
		s += "]\n"
		s += "Initial state: " + self.start_symbol + "\n"
		s += "Final states: ["
		if "Ɛ" in self.terminals:
			s += self.start_symbol + ", "
		s += "final_state]\n"
		s += "Transitions:\n"

		for non_terminal in self.productions.keys():
			s += non_terminal + " -> "
			for prod in self.productions[non_terminal]:
				if len(prod) == 2:
					s += "(" + prod[1] + ", " + prod[0] + "), "
				else:
					if prod[0] == "Ɛ":
						continue
					s += "(final_state, " + prod[0] + "), "
			s = s[:len(s) - 2]
			s += "\n"

		return s	