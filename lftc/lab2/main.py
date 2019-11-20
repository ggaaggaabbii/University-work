from finite_automaton import FiniteAutomaton
from grammer import Grammer
import json

def print_menu():
	print("##################################")
	print("###            Hello           ###")
	print("##################################")
	print("0. Exit")
	print("1. Read grammer")
	print("2. Read finite automaton")

def get_file_input():
	print("Give file path")
	file = input()
	with open(file) as f:
		return json.load(f)

def select_read_option(option):
	if option != "1" and option != "2":
		print("Invalid option")
		return

	print("1. File")
	print("2. Std input")
	read_option = input()
	if read_option != "1" and read_option != "2":
		print("Invalid option")
		return

	if read_option == "1":
		main_input = get_file_input()
	else:
		main_input = json.load(input())

	if option == "1":
		process_grammer(main_input)
	else:
		process_finite_automaton(main_input)

def print_grammer_menu():
	print("0. Back")
	print("1. Print Non terminal")
	print("2. Print Terminals")
	print("3. Print Productions")
	print("4. Print Productions for non terminal")
	print("5. Convert to Finite Automaton")

def process_grammer(json):
	gr = Grammer(json)
	if not gr.is_regular():
		print("Grammer is not regular")
		return 
	while True:
		print_grammer_menu()
		option = input()
		if option == "0":
			break
		elif option == "1":
			print(gr.get_non_terminals())
		elif option == "2":
			print(gr.get_terminals())
		elif option == "3":
			print(gr.get_productions())
		elif option == "4":
			print(gr.get_productions_for_non_terminal(input()))
		elif option == "5":
			print(gr.convert())
		else:
			print("Invalid option")

def print_fa_menu():
	print("0. Back")
	print("1. Print States")
	print("2. Print Alphabet")
	print("3. Print Transitions")
	print("4. Print Final States")
	print("5. Convert to Finite Automaton")
	
def process_finite_automaton(json):
	fa = FiniteAutomaton(json)
	while True:
		print_fa_menu()
		option = input()
		if option == "0":
			break
		elif option == "1":
			print(fa.get_states())
		elif option == "2":
			print(fa.get_alphabet())
		elif option == "3":
			print(fa.get_transitions())
		elif option == "4":
			print(fa.get_final_states())
		elif option == "5":
			print(fa.convert())
		else:
			print("Invalid option")

if __name__ == '__main__':
	while True:
		print_menu()
		option = input()
		if option == "0":
			break
		try:
			select_read_option(option)
		except Exception as e:
			print(e)
			print("Something went wrong, please try again")