/// When playing Scrabble©, each player draws 7 letters and must find a word that scores the most points using these letters.
/// 
/// A player doesn't necessarily have to make a 7-letter word; the word can be shorter. The only constraint is that the word must be made using the 7 letters which the player has drawn.
/// 
/// For example, with the letters  etaenhs, some possible words are: ethane, hates, sane, ant.
/// 
/// Your objective is to find the word that scores the most points using the available letters (1 to 7 letters).
/// 
///  	Rules
/// 
/// In Scrabble©, each letter is weighted with a score depending on how difficult it is to place that letter in a word. You will see below a table showing the points corresponding to each letter:
///  
/// 
/// Letters	Points
/// e, a, i, o, n, r, t, l, s, u	1
/// d, g	2
/// b, c, m, p	3
/// f, h, v, w, y	4
/// k	5
/// j, x	8
/// q, z	10
/// The word banjo earns you 3 + 1 + 1 + 8 + 1 = 14 points.
/// 
/// A dictionary of authorized words is provided as input for the program. The program must find the word in the dictionary which wins the most points for the seven given letters (a letter can only be used once). If two words win the same number of points, then the word which appears first in the order of the given dictionary should be chosen.
///  
/// 
/// All words will only be composed of alphabetical characters in lower case. There will always be at least one possible word.
/// 
///  	Game Input
/// 
/// Input
/// Line 1: the number N of words in the dictionary
/// 
/// N following lines: the words in the dictionary. One word per line.
/// 
/// Last line: the 7 letters available.
/// 
/// Output
/// The word that scores the most points using the available letters (1 to 7 letters). The word must belong to the dictionary. Each letter must be used at most once in the solution. There is always a solution.
/// 
/// Constraints
/// 0 < N < 100000
/// 
/// Words in the dictionary have a maximum length of 30 characters.
/// Example
/// 
/// Input
/// 
/// 5
/// because
/// first
/// these
/// could
/// which
/// hicquwh
/// 
/// Output
/// which

// Solution Code by dgoldaraz:

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
int getLetterValue(char l)
{
    switch(l)
    {
        case 'e':
        case 'a':
        case 'i':
        case 'o':
        case 'n':
        case 'r':
        case 't':
        case 'l':
        case 's':
        case 'u':
            return 1;
            break;
        case 'd':
        case 'g':
            return 2;
            break;
        case 'b':
        case 'c':
        case 'm':
        case 'p':
            return 3;
            break;
        case 'f':
        case 'h':
        case 'v':
        case 'w':
        case 'y':
            return 4;
            break;
        case 'k':
            return 5;
            break;
        case 'j':
        case 'x':
            return 8;
            break;
        case 'q':
        case 'z':
            return 10;
            break;
        default:
            return 0;
    }
    return 0;
}

void insertWord( map<char, vector<string>>& dictionary, string word)
{
    map<char, vector<string>>::iterator it = dictionary.find(word[0]);
    if(it != dictionary.end())
    {
        it->second.push_back(word);
    }
    else
    {
        vector<string> s;
        s.push_back(word);
        dictionary[word[0]] = s;
    }
}


int getValueInWord(string word, string oLetters)
{
    //We do this to avoid any change on the in string
    if( oLetters.size() < word.size() )
    {
        return 0;
    }
    
    int value = 0;
    string copyL = oLetters;
    
    for(int i = 0; i < word.size(); i++)
    {
        char c = word[i];
        size_t found = oLetters.find(c);
        if(found != string::npos)
        {
            //get value of the word and erase it from the letters
            value += getLetterValue(c);
            oLetters.erase(found, 1);
        }
        else
        {
            //This word can't be formed with the letters
            return 0;
        }
        
    }
    
    return value;
}

int main()
{
    int N;
    cin >> N; cin.ignore();
    map<char, vector<string>> dictionary;
    
    for (int i = 0; i < N; i++) {
        string W;
        getline(cin, W);
        //cerr << W << endl;
        insertWord(dictionary, W);
    }
    
    string LETTERS;
    getline(cin, LETTERS);
    cerr << LETTERS << endl;
    
    int maxValue = 0;
    string bestWord = "";
    
    map<char, vector<string>>::iterator it;
    for(int i = 0; i < LETTERS.size(); i++)
    {
        it = dictionary.find(LETTERS[i]);
        if(it != dictionary.end())
        {
            vector<string> words = it->second;
            
            for(int j = 0; j < words.size(); ++j)
            {
                int wValue = getValueInWord(words[j], LETTERS);
                if(wValue > maxValue)
                {
                    maxValue = wValue;
                    bestWord = words[j];
                }
            }
        }
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << bestWord << endl;
}