
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

bool isAllDash(const string& s)
{
    for (unsigned int i = 0; i < s.length(); i++)
        if (s[i] != '-') return false;
    return true;
}

bool isAllNotDash(const string& s)
{
    for (unsigned int i = 0; i < s.length(); i++)
        if (s[i] == '-') return false;
    return true;
}

set<char> getRemainingChars(const set<char>& previousGuesses)
{
    set<char> remainingChars;
    for (char c = 'a'; c <= 'z'; c++)
        remainingChars.insert(c);
    for (char c: previousGuesses)
        remainingChars.erase(c);
    return remainingChars;
}

char selectRandomChar(const set<char>& s) {
    int r = rand() % s.size();
    for (char c : s) {
        if (r-- == 0) return c;
    }
    return 0;
}

vector<string> readWordListFromFile(const char* fileName)
{
    vector<string> wordList;    //Khai bao vector kieu string
    ifstream file(fileName);	//Mở tệp có đường dẫn như trong tham số
    if (file.is_open()) {    	// Kiểm tra tệp mở thành công
        string word;
        while (file >> word) {	//Đọc từng từ đến khi không đọc được nữa
            wordList.push_back(word);//them vao vector
        }
        file.close();
    } else cout << "Error opening " << fileName;

    return wordList;
}

char getVowelGuess(const set<char>& remainingChars)
{
    char vowel[] = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; i < 5; i++) {
        if (remainingChars.find(vowel[i]) != remainingChars.end())
            return vowel[i];
    }
    return 0;
}

bool isSuitableWord(const string& word, const string& secretWord,
                    const set<char>& remainingChars)
{
    if (word.length() != secretWord.length()) return false;
    for (unsigned int i = 0; i < word.length(); i++) {
        if (secretWord[i] != '-') {
            if (tolower(word[i]) != tolower(secretWord[i])) return false;
        }
        else if (remainingChars.find(word[i]) == remainingChars.end())
             return false;
    }
    return true;
}
vector<string> getSuitableWords(const vector<string>& wordList,
                                const string& secretWord,
                                const set<char>& remainingChars)
{
    vector<string> result;
    for (unsigned int i = 0; i < wordList.size(); i++)
        if (isSuitableWord(wordList[i], secretWord, remainingChars))
            result.push_back(wordList[i]);
    return result;
}

map<char, int> getOccurenceCount(const set<char>& remainingChars,
                                 const vector<string>& wordList)
{
    map<char, int> count;
    for (char c: remainingChars) count[c] = 0;

    for (unsigned int i = 0; i < wordList.size(); i++) {
        const string& word = wordList[i];
        for (unsigned int j = 0; j < word.length(); j++)
            if (count.find(word[j]) != count.end())
                count[word[j]]++;
    }
    return count;
}

char getMaxOccurenceChar(const set<char>& remainingChars,
                         const map<char, int>& count)
{
    char best = 0;
    int best_count = 0;
    for (auto p : count)
        if (p.second > best_count) {
            best = p.first;
            best_count = p.second;
        }
    return best;
}

char getNextGuess(const set<char>& previousGuesses, const string& secretWord) {
    static vector<string> wordList = readWordListFromFile("100words.txt");
    set<char> remainingChars = getRemainingChars(previousGuesses);
    if (remainingChars.size() == 0)
        return 0;
    if (isAllDash(secretWord))
        return getVowelGuess(remainingChars);
    vector<string> filteredWordList = getSuitableWords(wordList, secretWord, remainingChars);
    map<char, int> occurenceCount = getOccurenceCount(remainingChars, filteredWordList);
    return getMaxOccurenceChar(remainingChars, occurenceCount);
} // chỉ có hàm này được khai báo ở guesser.h, các hàm khác chỉ nằm trong guesser.cpp
