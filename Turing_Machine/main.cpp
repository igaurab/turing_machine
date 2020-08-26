#include <iostream>
#include <string>
#include "test_tape.h"

using namespace std;

int main() {
	// Program Counter
	int PC = 0;
	bool halt = false;
	bool verbose = false;

	string commands[100][4] = {
		{"write","1"}, //1
		{"move","left"}, //2
		{"write","0"}, //3
		{"move","right"}, //4

		{"move","right"}, //5
		{"write","1"}, //6

		{"if","1","11"}, //7
		{"if","0","9"}, //8

		{"accept"}, //9
		{"reject"}, //10

		{"move","right"}, //11
		{"write","0"}, //12
		{"goto", "10"} //13
	};

	Tape tape;
	tape.moveToPosition(20);
	while(!halt) {
		if (verbose) cout << "Executing command at " << PC + 1 << endl;

		if (commands[PC][0] == "move") {
			if (commands[PC][1] == "left") {
				tape.moveLeft();
			}
			else {
				tape.moveRight();
			}
		}

		else if (commands[PC][0] == "write") {
			string s = commands[PC][1];
			char c = s[0];
			tape.write(c);
		}

		else if (commands[PC][0] == "goto") {
			int pos = stoi(commands[PC][1]);
			if (pos >= 1) {
				if(verbose) cout << "Goto Pos: " << pos << endl;

				PC = pos - 2;
			}
		}

		else if (commands[PC][0] == "if") {
			char getCurrentChar = tape.scan();
			string s = commands[PC][1];
			char expectedChar = s[0];
			
			if (getCurrentChar == expectedChar) {
				int pos = stoi(commands[PC][2]);
				if (verbose) cout << "Goto Pos: " << pos << endl;
				if (pos >= 1) {
					PC = pos - 2;
				}
			}

		}

		else if (commands[PC][0] == "accept") {
			cout << "Accepted" << endl;
			tape.printTapeStats();
			halt = true;
		}

		else if (commands[PC][0] == "reject") {
			cout << "Rejected" << endl;
			tape.printTapeStats();
			halt = true;
		}

		else {
			cout << "Unrecognized Input!!" << endl;
		}

		PC++;
	}

	return 1;
}
