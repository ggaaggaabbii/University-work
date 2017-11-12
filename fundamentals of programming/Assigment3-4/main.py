import command_base_ui as cmd
import menu_based_ui as menu
import test_module as t

def main():
	while True:
		print("Select a ui")
		print("1. Command based")
		print("2. Menu based")
		print("0. Exit")
		c = input()
		if c == "1":
			cmd.start()
		elif c == "2":
			menu.start()
		elif c == "0":
			break
		else:
			print("Error")

t.test_all()
main()
