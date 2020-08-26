#include "Tape.h"
#include <iostream>
#define TAPE_SIZE 30

Tape::Tape() {

	this->tape = new char[TAPE_SIZE];
	
	for (int i = 0; i < TAPE_SIZE; i++) {
		this->tape[i] = ' ';
	}

	this->head = (int) TAPE_SIZE / 2;

	this->size = TAPE_SIZE;
}

int Tape::getSize() {
	return this->size;
}

int Tape::getHeadPosition() {
	return this->head;
}


char Tape::scan() {
	return this->tape[head];
}

void Tape::write(char c) {
	this->tape[head] = c;
}

void Tape::moveLeft() {
	if (this->head - 1 >= 0) {
		this->head--;
	}
}

void Tape::moveRight() {
	if (this->head + 1 < this->getSize() ) {
		this->head++;
	}
} 

void Tape::moveToPosition(int x) {
	if (x >= 0 && x < this->getSize()) {
		this->head = x;
	}
}

void Tape::display() {
	for (int i = 0; i < this->getSize(); i++) {
		if (this->tape[i] != ' ') {
			std::cout << this->tape[i] << " ";
		}
	}
}

void Tape::printTapeStats() {
	int len = 0;
	for (int i = 0; i < this->getSize() ; i++) {
		if (this->tape[i] != ' ') {
			len++;
		}
	}

	std::cout << "Tape State:" << std::endl;
	std::cout << "---------------------" << std::endl;
	std::cout << "Capacity of Tape: " << this->getSize() << std::endl;
	std::cout << "Bytes Written: " << len << std::endl;

	std::cout << "Position of Head: " << this->head << std::endl;

	std::cout << "Current Output: ";
	this->display();
	std::cout << std::endl;
}

void Tape::clear() {
	for (int i = 0; i < this->getSize() ; i++) {
		if (this->tape[i] != ' ') {
			this->tape[i] = ' ';
		}
	}
}