#include "IO.h"
#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <string>
#include <unordered_map>

using namespace std;


IO::Command IO::getInput(string prompt, string error) {
	// variables to store the requested command type and given arguments
	IO::CommandType commandType = IO::CommandType::Null;
	vector<variant<int, string>> args = {};

	bool goodInput = false;
	string inputMessage = error;

	do {
		
		cout << endl << prompt << endl << inputMessage << endl << "> ";
		string commandInput;
		cin >> commandInput;

		if (IO::CommandMap.count(commandInput) == 0) {
			// Command input not found in list
			inputMessage = "Invalid command; please try again";
			continue;
		}

		// Valid command, check arguments
		commandType = IO::CommandMap[commandInput];
		vector<IO::CommandArgumentType> expectedArgs = IO::CommandArguments[commandType];

		// extract arguments from entry
		for (IO::CommandArgumentType arg : expectedArgs) {
			if (cin.peek() == ' ') {
				// extract argument
				int iInput = 0;
				string sInput = "";

				switch (arg) {

				case IO::Integer:
					cin >> iInput;
					if (cin.good()) {
						args.push_back(variant<int, string>(iInput));
					}
					break;
				case IO::String:
					cin >> sInput;
					if (cin.good()) {
						args.push_back(variant<int, string>(sInput));
					}
					break;

				}

				if (!cin.good()) {
					// String passed for int
					inputMessage = "Argument unusable; please try again";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					goto reprompt;
				}

			} else {
				// Missing argument(s)
				inputMessage = "Too few arguments; " + commandInput + " requires " + to_string(expectedArgs.size());
				goto reprompt;
			}
		}

		// After last argument should be \n and not another argument
		do {
			char nextChar = cin.peek();
			switch (nextChar) {
			case '\n':
				goodInput = true;
				break;
			case ' ':
				// ignore any spaces between arguments
				cin.ignore(1);
				break;
			default:
				inputMessage = "Too many arguments; " + commandInput + " requires " + to_string(expectedArgs.size());
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				goto reprompt;
				break;
			}
		} while (!goodInput);

	reprompt:
		;
	} while (!goodInput);

	return IO::Command{commandType, args};
}