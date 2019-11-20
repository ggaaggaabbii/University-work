class FiniteAutomaton():
	def __init__(self, json):
		self.states = json["States"]
		self.alphabet = json["Alphabet"]
		self.transitions = json["Transitions"]
		self.initial_state = json["Initial state"]
		self.final_states = json["Final states"]

	def get_states(self):
		return self.states

	def get_alphabet(self):
		return self.alphabet

	def get_transitions(self):
		s = ""
		for state in self.transitions.keys():
			s += state + ": "
			for transition in self.transitions[state]:
				s += "(" + transition["state"] + ", " 
				s += transition["symbol"] + "); "
			s = s[:len(s) - 2]
			s += "\n"
		return s

	def get_final_states(self):
		return self.final_states

	def convert(self):
		s = ""
		s += "Terminals: ["
		for t in self.alphabet:
			s += t + ", "
		
		if self.initial_state in self.final_states:
			s += "Ɛ, "
		s = s[:len(s) - 2]
		s += "]\n"
		s += "Non Terminals: ["
		for t in self.states:
			s += t + ", "
		s = s[:len(s) - 2]
		s += "]\n"
		s += "Starting symbol: "
		s += self.initial_state
		s += "\n"
		s += "P:\n"
		for t in self.transitions.keys():
			s += t + " -> "
			if t == self.initial_state and t in self.final_states:
				s += "Ɛ | "
			for tran in self.transitions[t]:
				if tran["state"] in self.final_states:
					s += tran["symbol"]
					if tran["state"] in self.transitions.keys():
						s += " | " + tran["symbol"] + tran["state"]
				else:
					s += tran["symbol"] + tran["state"]
				
				s += " | "
			s = s[:len(s) - 2]
			s += "\n"

		return s