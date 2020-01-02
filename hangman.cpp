#include "hangman.h"
#include <time.h>
#include <iostream>
#include <string>
#include <ctype.h>
#include <algorithm>



hangman::hangman(vector<string>& wordArray)
{
	// copying the vector to member vector 
	copy(wordArray.begin(), wordArray.end(), back_inserter(this.words) );
}


hangman::~hangman()
{
}


void hangman::drawHangman(int number) // drawing the hangman depending on how many mistake user has made so far.
{
	cout << endl;
	
	if ( number > 0 )
	{
		cout << " o" ;
		if (number > 1)
		{
			cout << endl << "/";
			if (number > 2)
			{
				cout << "|";
				if (number > 3)
				{
					cout << "\\";
					if (number > 4)
					{
						cout << endl << " |";
						if (number > 5)
						{
							cout << endl << "/";
							if (number > 6)
							{
								cout << " \\";
							}
						}
					}
				}
			}
		}
		cout << endl ;
	}

}

void hangman::play()
{
	srand(time(NULL)); // init the random function

	string inputStr = "y";

	while (inputStr.size() > 0 && (inputStr.front() == 'y' || inputStr.front() == 'Y'))
	{
		inputStr.erase(0, 1); //erase 'y' , keep the rest in case user entered more than 'y'.
		size_t wordIndex = rand() % (words.size()); // get an index by randon function to pick from 'words' 
		string  word = words[wordIndex];
		std::transform(word.begin(), word.end(), word.begin(), ::toupper); // convert the random word to uppercase
		string guessWord(word.size(), '?');
		string guessedLetters = "";

		cout << "Guess the word : " << string(word.size(), 'X') << endl << endl;

		int wrongGuesses = 0;

		while (wrongGuesses < 7)
		{
			if (inputStr.size() > 0)
			{
				char front = toupper( inputStr.front() ); // pick the first char , convert it to uppercase

				if (isalpha(front)) // is it alphabet?
				{
					if (guessedLetters.find(front) == string::npos) // did user enter this char before?
					{
						bool found = false;
						auto  g = guessWord.begin();
						for (auto l = word.cbegin(); l < word.cend(); l++, g++)
						{
							if (*l == front) // if the random word has the char, copy it in the 'question mark word' for showing to user
							{
								*g = *l;
								found = true;
							}
						}
						guessedLetters.push_back(front); // add the char in list of entered chars
						guessedLetters.push_back(' ');

						cout << "\nYour guesses:" << endl << guessedLetters << endl; // print the list of entered chars

						if (!found) // if the char was not in the word, add wrong counter
						{
							wrongGuesses++;

						}
						else if (guessWord.find('?') == string::npos) // if there is no '?' in guessed word '????' ,it means user guessed the word
						{
							cout << "\nWord: " << word << endl;
							cout << "\nCongratulation!!! You guessed my word." << endl;
							break;
						}
						drawHangman(wrongGuesses); // draw the hangman for the number of wrong letters user entered.
					}
					else
					{ //  case where the first char user entered is not alphabet
						cout << "\n'" << front << "'was already guessed. Try another letter\n";
					}
				}
				else
				{ // user entered none alphabetic letter
					cout << "Letters only please\n";
				}
				inputStr.erase(0, 1);
				if (inputStr.size() > 0) // we have letters in our buffer, just want to show the word after replacing latest letter
				{
					cout << "\nGuess a letter: " << guessWord << "\n?";

				}
			}
			else
			{
				cout << "\nGuess a letter: " << guessWord << "\n?";
				cin >> inputStr;
			}
		}

		if (wrongGuesses == 7) // reached max number of error
		{
			cout << "\nSorry - you have run out of guesses ;-(" << endl;
			cout << "The correct answer was: " << word << endl << endl;
			cout << "...GAME OVER..." << endl;
		}

		cout << "\nplay again? (y/n)";
		cin >> inputStr;
	}

	system("pause");
}

