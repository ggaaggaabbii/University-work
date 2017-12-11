from controller.controller import controller
from model.operand import operand
from ui.ui import UI

def main():
	ct = controller()
	ui = UI(ct)
	ui.start()

main()
