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
	bool verbose = true;

	vector<vector<string> > commands;
	map<string, int> labels;
	regex r_label("label:");
	regex r_lb("[a-zA-Z0-9]+");
	regex r_digit("[0-9]+");

	ifstream file;
	std::string line;
	
	file.open("program.tm");
	std::string temp;
	vector<string> words;
	int line_number = 1;
	while (std::getline(file, line)) {

		bool f_ignore = false;
		bool f_ignore_word = false;
		int word_index = 0;
		std::istringstream iss(line);

		if (!line.size()) {
			f_ignore = true;
		}

		while (iss >> temp) {
			if (temp[0] == '#') {
				f_ignore = true;
			}

			if (word_index == 0) {
				
				if (word_index == 0 && !f_ignore) {
					if (regex_search(temp, r_label)) {
						smatch match;
						temp = regex_replace(temp, r_label, "");
						regex_search(temp, match, r_lb);
						string l = match[0];
						cout << l << endl;
						labels.insert(pair<string, int>(l, line_number));
						f_ignore_word = true;
					}
					else {
						labels.insert(pair<string, int>(to_string(line_number), line_number));
					}
				}
			}
			if(word_index == 1) f_ignore_word = false;
			if (temp != " ") {
				if (!f_ignore && !f_ignore_word) words.push_back(temp);
				if (!f_ignore) word_index++;
			}
			
		}
		if (!f_ignore && !f_ignore_word) commands.push_back(words);
		if (!f_ignore) line_number++;
		words.clear();
	}
	file.close();

	if (verbose) {
		cout << "Priniting commands" << endl;
		for (int i = 0; i < commands.size(); i++)
		{
			for (int j = 0; j < commands[i].size(); j++)
			{
				cout << commands[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	if (verbose) {
		cout << "Prinitng map" << endl;
		std::map<std::string, int>::iterator it = labels.begin();
		while (it != labels.end())
		{
			std::string label = it->first;
			int num = it->second;
			std::cout << label << ":" << num << std::endl;
			it++;
		}
	}
	

	Tape tape;
	tape.moveToPosition(15);

	while(!halt) {
		if (verbose) cout << "Executing command at " << PC + 1 << endl;
		string instr = commands[PC][0];

		if (instr == "move") {
			string arg = commands[PC][1];
			if (arg == "left") {
				tape.moveLeft();
			}
			else if(arg == "right") {
				tape.moveRight();
			}
			else if (arg == "br") {
				while (tape.scan() != ' ') {
					tape.moveRight();
				}
				tape.moveLeft();
			}
			else if (arg == "bl") {
				while (tape.scan() != ' ') {
					tape.moveLeft();
				}
				tape.moveRight();
			}
			else if (arg == "Br") {
				while (tape.scan() != ' ') {
					tape.moveRight();
				}
			}
			else if (arg == "Bl") {
				while (tape.scan() != ' ') {
					tape.moveLeft();
				}
			}
			else if(regex_search(arg,r_digit)) {
				tape.moveToPosition(stoi(arg) - 1);
			}
			else {
				//TODO: Throw error
			}
		}

		else if (instr == "write") {
			string s = commands[PC][1];
			char c = s[0];
			tape.write(c);
		}

		else if (instr == "goto") {
			int pos = labels.find(commands[PC][1])->second;
			if (pos >= 1) {
				if(verbose) cout << "Goto Pos: " << pos << endl;

				PC = pos - 2;
			}
		}

		else if (instr == "if") {
			char getCurrentChar = tape.scan();
			string arg = commands[PC][1];
			
			char expectedChar = arg[0];
			if (expectedChar == 'b') expectedChar = ' ';
			
			if (getCurrentChar == expectedChar) {
				int pos = labels.find(commands[PC][2])->second;
				if (pos >= 1) {
					PC = pos - 2;
				}
				if (verbose) cout << "If Jump: " << pos << endl;
			}
		}

		else if (instr == "accept") {
			cout << "Accepted" << endl;
			tape.printTapeStats();
			halt = true;
		}

		else if (instr== "reject") {
			cout << "Rejected" << endl;
			tape.printTapeStats();
			halt = true;
		}

		else {
			cout << "Unrecognized Instruction!" << endl;
		}

		PC++;
	}

	return 1;
}
