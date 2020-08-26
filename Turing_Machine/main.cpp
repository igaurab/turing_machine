#include <iostream>
#include <string>
#include "test_tape.h"

using namespace std;

class Controller {

};




int main() {
	string commands[][3] = {
		{"goto","5"},

		{"write","1"},
		{"move","left"},
		{"write","0"},
		{"move","right"},
		{"move","right"},
		{"write","1"},

		{"goto","4"},
		{"if","1","20"},

		{"accept"},
	};

	Tape tape;
	using array_type = decltype(commands);

//http://www.cplusplus.com/forum/general/110091/
//	std::cout << "array 'second' rank: " << std::rank<array_type>::value << ", "
//		<< "nrows: " << std::extent<array_type>::value << ", "
//		<< "ncols: " << std::extent<array_type, 1>::value << '\n';
//op: array 'second' rank: 2, nrows: 5, ncols: 6

	for (int i = 0; i < std::extent<array_type>::value ; i++) {
		if (commands[i][0] == "move") {
			if (commands[i][1] == "left") {
				tape.moveLeft();
			}
			else {
				tape.moveRight();
			}
		}

		if (commands[i][0] == "write") {
			string s = commands[i][1];
			char c = s[0];
			tape.write(c);
		}

		if (commands[i][0] == "goto") {
			string pos = commands[i][1];
			tape.moveToPosition(stoi(pos));

		}

		if (commands[i][0] == "if") {
			char getCurrentChar = tape.scan();
			string s = commands[i][1];
			char expectedChar = s[0];

			if (getCurrentChar == expectedChar) {
				string pos = commands[i][2];
				tape.moveToPosition(stoi(pos));
			}

		}

		if (commands[i][0] == "accept") {
			cout << "Accepted" << endl;
			tape.printTapeStats();

		}

		if (commands[i][0] == "reject") {
			cout << "Rejected" << endl;
			tape.printTapeStats();

		}
	}

	return 1;
}
