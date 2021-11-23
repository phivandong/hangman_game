#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

const int MAX_BAD_GUESSES = 7;
const string FIGURE[] = {
         "   -------------    \n"
         "   |                \n"
         "   |                \n"
         "   |                \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |                \n"
         "   |                \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |                \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",
         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |           |    \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|    \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|\\  \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",
         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|\\  \n"
         "   |          /     \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|\\  \n"
         "   |          / \\  \n"
         "   |     \n"
         " -----   \n",
   };

void renderGame(string guessedWord, int badGuessCount)
{
   cout << FIGURE[badGuessCount] << endl;
   cout << guessedWord << endl;
   cout << "Number of wrong guesses: " << badGuessCount << endl;
}

const string& getNextHangMan()
{
    const static string figure[] = {
    "   ------------+    \n"
    "   |    /           \n"
    "   |    O           \n"
    "   |   /|\\         \n"
    "   |   / \\         \n"
    "   |                \n"
    " -----      \n" ,
    "   ------------+     \n"
    "   |     |           \n"
    "   |     O           \n"
    "   |    /|\\         \n"
    "   |    / \\         \n"
    "   |        \n"
    " -----      \n",
    "   ------------+    \n"
    "   |    /           \n"
    "   |    O           \n"
    "   |   /|\\         \n"
    "   |   / \\         \n"
    "   |                \n"
    " -----      \n" ,
    "   ------------+     \n"
    "   |     |           \n"
    "   |     O           \n"
    "   |    /|\\         \n"
    "   |    / \\         \n"
    "   |        \n"
    " -----      \n",
    "   ------------+     \n"
    "   |      \\         \n"
    "   |      O          \n"
    "   |     /|\\        \n"
    "   |     / \\        \n"
    "   |      \n"
    " -----    \n",
    "   ------------+     \n"
    "   |     |           \n"
    "   |     O           \n"
    "   |    /|\\         \n"
    "   |    / \\         \n"
    "   |        \n"
    " -----      \n",
    };
    const int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

const string& getNextDancingMan()
{
    static string figure[] = {
    "     O     \n"
    "    /|\\   \n"
    "    | |    \n",
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n",
    "   __O__   \n"
    "     |     \n"
    "    / \\   \n",
    "    \\O/   \n"
    "     |     \n"
    "    / \\   \n",
    "   __O__   \n"
    "     |     \n"
    "    / \\   \n",
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n" ,
    "    O      \n"
    "    /|\\   \n"
    "    / \\   \n" ,
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n" ,
    "      O    \n"
    "    /|\\   \n"
    "    / \\   \n" ,
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n" ,
    };
    const int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

void displayFinalResult(bool won, string word)
{
    while (true) {
        for (int i = 0; i < 30; i++) cout << endl;
          if (won)
             cout << "Congratulations! You win!" << endl;
          else
             cout << "You lost. The correct word is " << word << endl;
          cout << (won ? getNextDancingMan() : getNextHangMan());
          this_thread::sleep_for(chrono::milliseconds(500));
    }
}

