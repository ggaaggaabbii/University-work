class Grammar(object):
	def __init__(self, json):
		self.terminals = json["Terminals"]
		self.non_terminals = json["Non terminals"]
		self.productions = json["Productions"]
		self.start_symbol = json["Starting symbol"]

	def enchant(self):
		self.non_terminals.append("S\'")
		self.productions["S\'"] = [[self.start_symbol]]
		self.start_symbol = "S\'"

	def ex_start_symbol(self):
		return self.productions[self.start_symbol][0][0]

	def __str__(self):
		s = ""
		s += "Terminals: "
		s += str(self.terminals)
		s += "\n"
		s += "Non terminals: "
		s += str(self.non_terminals)
		s += "\n"
		s += "Productions: "
		s += str(self.productions)
		s += "\n"
		s += "Start symbol: "
		s += self.start_symbol
		return s