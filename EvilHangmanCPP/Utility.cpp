#include "Utility.h"

namespace utility
{
	char promptSingleCharacter()
	{
		std::string inputString = utility::promptInput<std::string>();

		while (!utility::isAlphaCharacter(inputString))
		{
			std::cout << "ERROR: Please enter a single letter." << std::endl;
			inputString = utility::promptInput<std::string>();
		}

		return inputString.at(0);
	}

	bool promptYesNo()
	{
		std::string inputString;

		std::cin >> inputString;

		while (!((inputString == "y" || inputString == "Y") || (inputString == "n" || inputString == "N")))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "ERROR: Please Enter Y or N" << std::endl;
			std::cin >> inputString;
		}

		char input = inputString.at(0);

		if (input == 'y' || input == 'Y')
		{
			return true;
		}

		return false;
	}

	bool isAlphaCharacter(std::string input)
	{
		char inputCharacter = input.at(0);

		if (input.length() > 1 || !isalpha(inputCharacter) || isspace(inputCharacter))
		{
			return false;
		}

		return true;
	}

	int getNumberOfCharactersInString(std::string input, char targetCharacter)
	{
		int targetCharacterCount = 0;

		for (int i = 0; i < input.length(); i++)
		{
			if (input.at(i) == targetCharacter)
			{
				targetCharacterCount++;
			}
		}

		return targetCharacterCount;
	}
};