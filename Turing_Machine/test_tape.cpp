#include "tape.h"
#include "test_tape.h"
#include <iostream>

void test_moveLeft(Tape* tape) {
	std::cout << "Move head to left: " << std::endl;

	for (int i = 0; i <= tape->getSize() ; i++) {
		tape->moveLeft();
	}

	if (tape->getHeadPosition() == 0) {
		std::cout << "Test Passed!" << std::endl;
		//std::cout << "Head moved to left[" << tape->getHeadPosition() << "]" << std::endl;
	}
	else {
		std::cout << "Test Failed!" << "Head Pos: " << tape->getHeadPosition() << std::endl;
	}
}

void test_moveRight(Tape* tape) {
	std::cout << "Move head to right: " << std::endl;

	for(int i = 0; i <= tape->getSize(); i++) {
		tape->moveRight();
	}

	if (tape->getHeadPosition() == tape->getSize() - 1) {
		std::cout << "Test Passed!" << std::endl;
		//std::cout << "Head moved to right[" << tape->getHeadPosition() << "]" << std::endl;
	}
	else {
		std::cout << "Test Failed!" << "Head Pos: " << tape->getHeadPosition() << std::endl;
	}
}

void test_moveToPosition(Tape* tape) {
	int pos = 7;
	tape->moveToPosition(pos);
	std::cout << "Move to Position (x)" << std::endl;
	if (tape->getHeadPosition() == pos) {
		std::cout << "Test Passed!" << std::endl;
	}else {
		std::cout << "Test Failed!" << std::endl;
	}
}

void printDot() {
	std::cout << "............................" << std::endl;
}

void test_tape_main() {
	Tape tape;
	std::cout << "Tape Initialized" << std::endl;
	printDot();

	tape.printTapeStats();
	
	printDot();
	std::cout << "Testing" << std::endl;
	printDot();

	test_moveRight(&tape);
	printDot();

	test_moveLeft(&tape);
	printDot();

	test_moveToPosition(&tape);
}

