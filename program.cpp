
#include <vector>
#include <string>
#include "hangman.h"

using namespace std;

int main()
{
	// vector with 10 string to send to hangman object to choose from
	vector<string>  words = { "study","improve","weekend","nation","window","Building","weather","health","village","night" };

	hangman myGame(words); //instantiate the game object

	myGame.play(); //play the game
}