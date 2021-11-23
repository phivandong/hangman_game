//#pragma once

#include <string>
#include <set>

char getNextGuess(const set<char>& previousGuesses, const string& secretWord);
bool isAllNotDash(const string& s);
bool isAllDash(const string& s);
