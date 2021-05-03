#pragma once
#include "HangmanCore.hpp"
#include "Utility.h"

HangmanCore::HangmanCore()
{
	std::string line;
	std::ifstream dictionaryFile("dictionary.txt");

	if (dictionaryFile.is_open())
	{
		while (getline(dictionaryFile, line))
		{
			this->Dictionary[line.length() - 1].push_back(line);
		}
	}
}

void HangmanCore::run()
{
	bool CoreRunning = true, playAgain = false;

	while (CoreRunning)
	{
		this->promptGameParams();
		this->initializeWord();

		while (!this->gameEnded)
		{
			this->printGameState();
			this->promptGuess();
			this->updateGame();
			this->gameEnded = this->isGameEnded();
		}

		std::cout << "Play Again?" << std::endl;

		playAgain = utility::promptYesNo();

		std::cout << std::endl;

		if (playAgain)
		{
			this->resetGame();
			continue;
		}
		else
		{
			break;
		}
	}
}

void HangmanCore::promptGameParams()
{
	std::cout << "Enter a word length to play with." << std::endl;

	this->GameLength = utility::promptInput<int>();

	while(this->GameLength > 29 || this->GameLength < 1)
	{
		std::cout << "ERROR: Word length must be between 1 and 29" << std::endl;
		this->GameLength = (utility::promptInput<int>()) - 1;
	}

	std::cout << "How many guesses would you like to have?" << std::endl;

	this->RemainingGuesses = utility::promptInput<int>();

	while (this->RemainingGuesses > 100 || this->RemainingGuesses < 1)
	{
		std::cout << "ERROR: Guesses must be between 1 and 100" << std::endl;
		this->RemainingGuesses = utility::promptInput<int>();
	}
}

void HangmanCore::initializeWord()
{
	for (int i = 0; i < this->GameLength; i++)
	{
		this->Word.append("-");
	}

	this->CurrentWordFamily = this->Dictionary[this->GameLength];
}

void HangmanCore::printGameState()
{
	std::cout << "You have " << this->RemainingGuesses << " guesses left" << std::endl;
	std::cout << "Used letters: ";

	for (auto i : this->UsedLetters)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl;
	std::cout <<"Word: " << this->Word << std::endl;
}

void HangmanCore::promptGuess()
{
	std::cout << "Enter Guess: ";
	char guessInput = utility::promptSingleCharacter();

	while (std::find(this->UsedLetters.begin(), this->UsedLetters.end(), guessInput) != this->UsedLetters.end())
	{
		std::cout << "ERROR: Letter already guessed. Please Enter a New Guess." << std::endl;
		guessInput = utility::promptSingleCharacter();
	}

	this->Guess = guessInput;
	this->populateWordFamilies();
}

void HangmanCore::updateGame()
{
	std::string largestWordFamily = this->getLargestWordFamily();

	if (largestWordFamily.find(this->Guess) == std::string::npos)
	{
		std::cout << "Sorry, there are no " << this->Guess << "'s" << std::endl;
		this->RemainingGuesses--;
	}
	else
	{
		int guessLettersInFamily = utility::getNumberOfCharactersInString(largestWordFamily, this->Guess);

		if (guessLettersInFamily == 1)
		{
			std::cout << "Yes, there is 1 copy of " << this->Guess << std::endl;
		}
		else
		{
			std::cout << "Yes, there are " << guessLettersInFamily << " copies of " << this->Guess << std::endl;
		}
	}

	this->UsedLetters.push_back(this->Guess);
	this->CurrentWordFamily = this->WordFamilyMap[largestWordFamily];
	this->Word = largestWordFamily;
	this->WordFamilyMap.clear();
}

void HangmanCore::resetGame()
{
	this->Word = std::string();
	this->RemainingGuesses = 0;
	this->GameLength = 0;
	this->UsedLetters.clear();
	this->Guess = 0;
	this->gameEnded = false;
}

void HangmanCore::populateWordFamilies()
{
	std::string wordFamily;

	for (auto i : this->CurrentWordFamily)
	{
		wordFamily = this->stringToWordFamily(i, this->Guess);

		if (this->WordFamilyMap.find(wordFamily) == this->WordFamilyMap.end())
		{
			this->WordFamilyMap[wordFamily] = std::vector<std::string>();
		}

		this->WordFamilyMap[wordFamily].push_back(i);

	}
}

bool HangmanCore::isGameEnded()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, this->CurrentWordFamily.size() - 1);
	std::string actualWord;

	if (this->RemainingGuesses == 0)
	{
		actualWord = this->CurrentWordFamily.at(distrib(gen));
		std::cout << "You lose! The word was: " << actualWord << std::endl;
		return true;
	}
	else if (this->Word.find('-') == std::string::npos)
	{
		std::cout << "Congrats you win!!! The word was: " << this->Word << std::endl;
		return true;
	}
	std::cout << std::endl;
	return false;
}

std::string HangmanCore::stringToWordFamily(std::string word, char guess)
{
	std::string parsedFamily = this->Word;

	for (int i = 0; i < word.length(); i++)
	{
		if (word.at(i) == guess)
		{
			parsedFamily[i] = guess;
		}
	}

	return parsedFamily;

}

std::string HangmanCore::getLargestWordFamily()
{
	int maxSize = 0;
	std::string largestWordFamily;

	std::map<std::string, std::vector<std::string>>::iterator it;

	for (it = this->WordFamilyMap.begin(); it != this->WordFamilyMap.end(); it++)
	{
		if (it->second.size() > maxSize)
		{
			maxSize = it->second.size();
			largestWordFamily = it->first;
		}
	}
	
	return largestWordFamily;
}