import json
import traceback
from grammar import Grammar
from copy import deepcopy
DOT = "DOT"
ACC = "ACC"
SHIFT = "SHIFT"
EPSILON = "Ɛ"
REDUCE = "REDUCE"

def can_col(grammar):
	C = []
	ex_start_symbol = grammar.ex_start_symbol()
	s0 = closure([[grammar.start_symbol, DOT, ex_start_symbol]], grammar)
	C.append(s0)

	l1 = len(C)

	while True:
		for s in C:
			for x in grammar.terminals + grammar.non_terminals:
				gt = goto(s, x, grammar)
				if len(gt) and gt not in C:
					C.append(gt)
		l2 = len(C)
		if l1 == l2:
			break
		l1 = l2

	return C

def closure(s, grammar):
	C = s
	l1 = len(C)

	while True:
		for item in C:
			dot_pos = item.index(DOT)
			if dot_pos + 1 == len(item):
				continue
			if item[dot_pos + 1] not in grammar.non_terminals:
				continue
			for gamma in grammar.productions[item[dot_pos + 1]]:
				new_item = [item[dot_pos + 1], DOT]
				new_item += gamma
				if new_item not in C:
					C.append(new_item)
		
		l2 = len(C)
		if l1 == l2:
			break
		l1 = l2
	return C

def goto(s, x, grammar):
	new_state = []
	
	for item in s:
		dot_pos = item.index(DOT)
		if dot_pos + 1 == len(item):
			continue
		if item[dot_pos + 1] != x:
			continue
		new_state.append(item[:dot_pos] + [x] + [DOT] + item[dot_pos + 2:])

	return closure(new_state, grammar)

def first(x, grammar):
	last = {}
	current = {}

	for a in grammar.non_terminals:
		current[a] = set()
		for p in grammar.productions[a]:
			if p[0] in grammar.terminals:
				current[a].add(p[0])

	for a in grammar.terminals:
		current[a] = {a}

	last = deepcopy(current)

	while True:
		for a in grammar.non_terminals:
			for p in grammar.productions[a]:
				for l in last[p[0]]:
					current[a].add(l)					

		if current == last:
			break
		last = deepcopy(current)

	return current[x]

def follow(x, grammar):
	f = {}
	for a in grammar.non_terminals + grammar.terminals:
		f[a] = first(a, grammar)
	fo = {}
	for a in grammar.non_terminals:
		fo[a] = set()

	fo[grammar.start_symbol] = {EPSILON}
	fl = deepcopy(fo)

	while True:
		for a in grammar.non_terminals:
			for elem in fl[a]:
				fo[a].add(elem)
			for non_t in grammar.non_terminals:
				for p in grammar.productions[non_t]:
					if a not in p:
						continue
					pos_a = p.index(a)
					if pos_a + 1 == len(p):
						for elem in fl[non_t]:
							fo[a].add(elem)
					else:
						f_beta = first(p[pos_a + 1], grammar)
						for elem in f_beta:
							if elem != EPSILON:
								fo[a].add(elem)

		if fo == fl:
			break
		fl = deepcopy(fo)

	return fo[x]

def construct_table(can_col, grammar):
	parse_table = {}
	for state in can_col:
		item_list = [tuple(item) for item in state]
		parse_table[tuple(item_list)] = {}
		for element in grammar.non_terminals + grammar.terminals:
			parse_table[tuple(item_list)][element] = 0

		si = tuple(item_list)
		# print(si)
		for item in state:
			dot_pos = item.index(DOT)
			if dot_pos + 1 != len(item):
				sj = goto(state, item[dot_pos + 1], grammar)
				if len(sj) == 0:
					continue
				tupled_sj = tuple(tuple(item) for item in sj)
				if item[dot_pos + 1] in grammar.non_terminals:
					# case 4
					parse_table[si][item[dot_pos + 1]] = tupled_sj
				elif item[dot_pos + 1] in grammar.terminals:
					# case 1
					if parse_table[si][item[dot_pos + 1]] != 0:
						print("Sh CONFLICT", parse_table[si][item[dot_pos + 1]])
					parse_table[si][item[dot_pos + 1]] = (SHIFT, tupled_sj)
			elif dot_pos + 1 == len(item):
				# ex starting symbol
				if item[0] == grammar.start_symbol:
					if item[dot_pos - 1] == grammar.ex_start_symbol():
						# case 3
						parse_table[si][grammar.start_symbol] = ACC
				else:
					# case 2
					for item in si:
						fol = follow(item[0], grammar)
						for p in grammar.productions[item[0]]:
							if p != list(item[1:-1]):
								continue
							for u in fol:
								symbol = u
								if symbol == EPSILON:
									symbol = grammar.start_symbol
								if parse_table[si][symbol] != 0:
									print("CONFLICT")
								parse_table[si][symbol] = (REDUCE, item[:-1])
			else:
				print("Error")

	return parse_table

def next_s(state):
	return convert_state_to_tuple(state[0][-1])

def next_in_seq(state):
	return state[1][0]

def convert_state_to_tuple(state):
	tupled_state = tuple(tuple(item) for item in state)
	return tupled_state

def shift_sj(state, parse_table):
	return parse_table[next_s(state)][next_in_seq(state)][1]

def is_shift(state, parse_table):
	return parse_table[next_s(state)][next_in_seq(state)][0] == SHIFT

def is_acc(state, parse_table):
	return parse_table[next_s(state)][next_in_seq(state)] == ACC

def is_reduce(state, parse_table):
	return parse_table[next_s(state)][next_in_seq(state)][0] == REDUCE

def reduce_production(state, parse_table):
	return parse_table[next_s(state)][next_in_seq(state)][1]

def next_token_in_ws(state):
	return state[0][-2]

def parse_grammar(grammar, w):
	C = can_col(grammar)
	
	print(C)
	print("====================")
	
	parse_table = construct_table(C, grammar)
	"""
	for x in parse_table.keys():
		print(x)
		print("Content:")
		print(parse_table[x])
		print("---")
	"""

	state = [[convert_state_to_tuple(C[0])], w + [grammar.start_symbol], []]
	is_accepted = False

	while True:
		try:
			if is_acc(state, parse_table):
				is_accepted = True
				break
			elif is_shift(state, parse_table):
				sj = shift_sj(state, parse_table)
				state[0].append(state[1][0])
				state[0].append(sj)
				state[1] = state[1][1:]
			elif is_reduce(state, parse_table):
				production = reduce_production(state, parse_table)
				rev_prod = production[::-1]
				rev_prod = rev_prod[:-1]
				for item in rev_prod:
					if next_token_in_ws(state) == item:
						state[0] = state[0][:-2]
					else:
						raise "Error"
				state[2].insert(0, production)
				smp = next_s(state)
				A = production[0]
				sj = parse_table[smp][A]
				state[0].append(A)
				state[0].append(sj)
			else:
				#print(state)
				#print(parse_table[next_s(state)][next_in_seq(state)])
				raise "Error"
		except Exception:
			#traceback.print_exc()
			break
	print(is_accepted)
	#print(state)
	if is_accepted:
		print(state[2])
	pass

if __name__ == "__main__":
	with open("grammar.in") as f:
	#with open("minilanguage_grammer.in") as f:
		g = Grammar(json.load(f))
		g.enchant()
		print(g)
		w = ["id", "+", "(", "id", "+", "const", ")"]
		#w = ["0", "18", "1"]
		print(w)
		parse_grammar(g, w)
