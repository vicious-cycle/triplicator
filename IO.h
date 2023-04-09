#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <string>
#include <variant>
#include <unordered_map>

/// <summary>
/// Manages input from the user.
/// </summary>
class IO {
public:
	enum CommandArgumentType {
		Integer,
		String
	};
	enum CommandType;
	

	/// <summary>
	/// Represents a single command that a user can provide, with the arguments provided by the user.
	/// </summary>
	struct Command {
		/// <summary>The action of this <c>Command</c>.</summary>
		CommandType type;

		/// <summary>The arguments provided to this <c>Command</c>.</summary>
		std::vector<std::variant<int, std::string>> args;

		/// <summary>Initialize a <c>Command</c> with brace initialization.</summary>
		/// <param name="type">The type of the command.</param>
		Command(CommandType type, std::vector<std::variant<int, std::string>> args) : type{type}, args{args} {};
	};

	/// <summary>Maps typed strings with their corresponding commands.</summary>
	static std::unordered_map<std::string, CommandType> CommandMap;
	
	/// <summary>Defines the required arguments for each command.</summary>
	static std::unordered_map<CommandType, std::vector<CommandArgumentType>> CommandArguments;

	
	/// <summary>
	/// <para>Prompts the user to input a command, along with any necessary arguments.</para>
	/// <para>Valid commands are specified using the static member types <c>CommandMap</c> and <c>CommandArguments</c>.</para>
	/// </summary>
	/// <example>
	/// <code>IO::getInput("Please make a selection");</code>
	/// </example>
	/// <param name="prompt">The prompt to display to the user.</param>
	/// <param name="error">An error message that appears by default.</param>
	/// <returns>An <c>IO::Command</c> object detailing the sent command and any arguments.</returns>
	static Command getInput(std::string prompt, std::string error = "");
	
};

enum IO::CommandType {
	Null,
	Go,
	Next,
	Print,
	Info,
	Help,
	Exit
};