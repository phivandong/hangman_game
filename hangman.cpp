#include <iostream>
#include <ctime>
#include <algorithm>
#include "draw.h"
#include "guesser.h"

using namespace std;

const string VERSION = "3.0";
const int MAX_GUESSES = 7;

void updateSecretWord(const string& mask, string& secretWord)
{
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-')
            secretWord[i] = mask[i];
}

bool isGoodMask(char guess, const string& mask,
                const string& secretWord)
{
    if (mask.length() != secretWord.length()) return false;
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-') {
            if (mask[i] != guess)
                return false;
            if (secretWord[i] != '-' && secretWord[i] != mask[i])
                return false;
        }
    return true;
}

int getUserWordLength()
{
    int wordLength;
    cout << endl << "Enter your word length: ";
    cin >> wordLength;
    return wordLength;
}

string getUserAnswer(char guess)
{
    string answer;
    cout << endl << "I guess " << guess << ", please enter your mask: ";
    cin >> answer;
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    return answer;
}
void initialize(int& wordLength, string& secretWord,
                int& incorrectGuess, set<char>& previousGuesses,
                bool& stop)
{
    wordLength = getUserWordLength();
    secretWord = string(wordLength, '-');
    incorrectGuess = 0;
    previousGuesses = set<char>();
    stop = false;
}
void render(int incorrectGuess, const set<char>& previousGuesses, const string& secretWord) {
//    clearScreen();
    cout << endl << "Incorrect guess = " << incorrectGuess
         << "   previous guesses = ";
    for (char c : previousGuesses)
        cout << c;
    cout << "   secretWord = " << secretWord << endl;
//    cout << getDrawing(incorrectGuess) << endl;
}
void playAnimation(bool isLosing, const string& word)
{
//    clearScreen();
//    while (true) {
        if (isLosing)
            cout << endl << "I lost :(. My best word is: " << word << endl;
        else
            cout << endl << "Haha, I win :D. The word is: " << word << endl;
//        cout << (isLosing ? getNextHangman() : getNextStandingman());
//        this_thread::sleep_for(chrono::milliseconds(500));
        //clearScreen();
//    }
}
void update(char guess, const string& mask,
            int& incorrectGuess, set<char>& previousGuesses,
            string& secretWord, bool& stop)
{
    if (!isGoodMask(guess, mask, secretWord))
        throw invalid_argument("mistake entering answer");
    previousGuesses.insert(guess);
    if (isAllDash(mask)) {
        incorrectGuess ++;
        if (incorrectGuess == MAX_GUESSES) stop = true;
    } else {
        updateSecretWord(mask, secretWord);
        if (isAllNotDash(secretWord)) stop = true;
    }
}

int main() {
    srand(time(0));
    int wordLength;
    string secretWord;
    int incorrectGuess;
    set<char> previousGuesses;
    bool stop;
    initialize(wordLength, secretWord, incorrectGuess, previousGuesses, stop);
    render(incorrectGuess, previousGuesses, secretWord);
    do {
        char guess = getNextGuess(previousGuesses, secretWord);
        string mask = getUserAnswer(guess);
        update(guess, mask, incorrectGuess, previousGuesses, secretWord, stop);
        render(incorrectGuess, previousGuesses, secretWord);
    } while (!stop);
    playAnimation(incorrectGuess == MAX_GUESSES, secretWord);
    return 0;
}


