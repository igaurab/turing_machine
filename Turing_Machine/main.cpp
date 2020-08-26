#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <map>
#include <iterator>

#include "test_tape.h"

using namespace std;

int main() {
	// Program Counter
	int PC = 0;
	bool halt = false;
	bool verbose = false;

	vector<vector<string> > commands;
	map<string, int> labels;

	ifstream file;
	std::string line;
	
	file.open("program.tm");
	std::string temp;
	vector<string> words;
	int line_number = 0;
	while (std::getline(file, line)) {
		bool f_ignore = false;
		int word_index = 0;
		std::istringstream iss(line);

		if (!line.size()) {
			f_ignore = true;
		}

		while (iss >> temp) {
			
			if (word_index == 0 || word_index == 1) {
				if (word_index == 0 && (temp == "#")) {
						f_ignore = true;
				}

				if (word_index == 1) {

				}
			}
			if(!f_ignore) words.push_back(temp);
		}
		if (!f_ignore) commands.push_back(words);
		words.clear();
	}
	file.close();
	
	for (int i = 0; i < commands.size(); i++)
	{
		for (int j = 0; j < commands[i].size(); j++)
		{
			cout << commands[i][j] << " ";
		}
		cout << endl;
	}
	
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

			if (expectedChar == 'b') expectedChar = ' ';
			
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
