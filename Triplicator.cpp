// triplicator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IO.h"
#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <string>
#include <unordered_map>


using namespace std;

vector<int> sequence {2};
int index = 0;

unordered_map<string, IO::CommandType> IO::CommandMap {
	{"go", IO::Go},
	{"next", IO::Next},
	{"print", IO::Print},
	{"info", IO::Info},
	{"help", IO::Help},
	{"exit", IO::Exit}
};

unordered_map<IO::CommandType, vector<IO::CommandArgumentType>> IO::CommandArguments {
	{IO::CommandType::Print, {IO::CommandArgumentType::Integer, IO::CommandArgumentType::Integer}},
	{IO::CommandType::Info, {}},
	{IO::CommandType::Help, {}},
	{IO::CommandType::Exit, {}}
};

/// <summary>
/// Prints the table of values for values from the start index to the end index.
/// </summary>
/// <param name="startIndex">The index the table starts at.</param>
/// <param name="endIndex">The index the table ends at.</param>
void printIndices(int startIndex, int endIndex) {
	for (int i = startIndex - 1; i < endIndex; ++i) {
		if (i >= sequence.size() || sequence[i] == -1) {
			cout << i + 1 << "\t >> ?\t >> " << 3 * (i + 1) << endl;
		} else {
			cout << i + 1 << "\t >> " << sequence[i] << "\t >> " << 3 * (i + 1) << endl;
		}
	}
}

string infoMessage = "\u001b[7mTRIPLICATOR:\u001b[0m\tA program to calculate a list of numbers.\
	\n\n\u001b[4mPremise:\u001b[24m\
	\n\tAn unknown machine generates an integer output based on an integer input.\
	\n\tThe outputs of the machine are not bound to any rules except the following:\
	\n\n #\tThe machine will only accept inputs that are positive integers, and will only ever output positive integers.\
	\n #\tThe machine's output is always greater than the input it receives.\
	\n #\tThe machine will always generate a constant and unique output for every input.\
	\n #\tThe machine will always generate an output that is three times the number that, when inputted, would output the machine's current input.\
	\n\tThis means that inputting a number, then taking the output and inputting it again, will always yield three times the starting amount.\
	\n\nThe machine is bound to no other rules beyond these.\
	\n\nThis program treats\n\nPress enter to return to the main menu.\u001b[0m";

string helpMessage = "Available commands:\n";

int main() {
	string errorMessage = "";
	IO::CommandType lastCommand = IO::Null;
	while (true) {
		IO::Command userCommand = IO::getInput("Please enter a command.", errorMessage);
		errorMessage = "";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (userCommand.type) {
		case IO::Exit:
			cout << "Thank you and goodbye" << endl;
			exit(0);
			break;
		case IO::Info:
			cout << infoMessage << endl;
			break;
		case IO::Help:
			cout << helpMessage << endl;
			break;
		case IO::Print:
		{
			int startIndex = get<int>(userCommand.args[0]);
			int endIndex = get<int>(userCommand.args[1]);
			if (startIndex > endIndex) {
				errorMessage = "Invalid indices; please try again";
				break;
			} else {
				printIndices(startIndex, endIndex);
			}
		}
			break;
		default:
			break;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
