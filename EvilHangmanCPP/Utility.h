#pragma once
#include <iostream>

namespace utility
{
	template<typename T>
	T promptInput()
	{
		T input;

		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return input;
	}

	char promptSingleCharacter();

	bool promptYesNo();

	bool isAlphaCharacter(std::string input);

	int getNumberOfCharactersInString(std::string input, char targetCharacter);

};