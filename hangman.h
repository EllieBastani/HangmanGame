#pragma once
#include <vector>
#include <string>

using namespace std;


class hangman
{
public:
	hangman( vector<string>& wordArray);
	~hangman();

private:
	vector<string> words;

	void drawHangman(int number); // drwa the hangman with the number of mistakes

public:
	void play();
};

