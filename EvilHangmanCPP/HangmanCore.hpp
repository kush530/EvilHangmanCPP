#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <memory>
#include <random>
#include <algorithm>

class HangmanCore
{
	public:

		HangmanCore();

		void run();

		void promptGameParams();
		
		void initializeWord();

		void printGameState();

		void promptGuess();

		void updateGame();

		void resetGame();

		void populateWordFamilies();

		bool isGameEnded();

		std::string getLargestWordFamily();

		std::string stringToWordFamily(std::string word, char guess);

	private:

		std::map<std::string, std::vector<std::string>>WordFamilyMap;
		std::vector<std::string> Dictionary[29];
		std::vector<char> UsedLetters;
		std::vector <std::string> CurrentWordFamily;

		std::string Word;

		int GameLength = 0, RemainingGuesses = 0, WordsRemaining = 0;
		char Guess = 0;
		bool gameEnded = false;
};