/// You mission is to print a specific line of the Conway sequence.
///  	Rules
/// Warning! This sequence can make you ill. The reasoning is simple but unusual: Read a line aloud whilst looking at the line above and you will notice that each line (except the first) makes ​​an inventory of the previous line.
/// 
/// 1
/// 1 1
/// 2 1
/// 1 2 1 1
/// 1 1 1 2 2 1
/// 3 1 2 2 1 1
/// ...
/// - Line 3 shows 2 1 because the line 2 contains two 1, one after the other.
/// - Line 4 displays 1 2 1 1 because the line 3 contains one 2 followed by one 1.
/// - Line 5 displays 1 1 1 2 2 1 because the line 4 contains one 1 followed by one 2 followed by two 1.
/// 
/// This sequence refers to a technique used to encode ranges in order to compress identical values ​​without losing any information. This type of method is used, amongst others, to compress images.
/// 
/// Your mission is to write a program that will display the line L of this series on the basis of an original number R (R equals 1 in our example).
/// 
///  	Game Input
/// 
/// Input
/// Line 1: The original number R of the sequence.
/// 
/// Line 2: The line L to display. The index of the first line is 1.
/// 
/// Output
/// The line L of the sequence. Each element of the sequence is separated by a space.
/// 
/// Constraints
/// 0 < R < 100
/// 0 < L ≤ 25
/// 
/// Example
/// 
/// Input
/// 1
/// 6
/// 
/// Output
/// 3 1 2 2 1 1

// Solution Code dgoldaraz:

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
vector<int> splitString(string t, string separator)
{
    vector<int> array;
    
    size_t found = 0;
    size_t endFound = t.find(separator,found);
    
    while(found != string::npos)
    {
        int lenght = endFound - found;
        string sub = t.substr(found,lenght);
        if(sub != " ")
        {
            int n = atoi(sub.c_str());
            array.push_back(n);
            //cerr << "Add " << sub << "-" <<n << endl;
        }
        found = endFound;
        endFound = t.find(separator, found+1);
    }
    
    return array;
}

int main()
{
    int R;
    cin >> R; cin.ignore();
    int L;
    cin >> L; cin.ignore();

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    string answer;
    answer += to_string(R);
    
    for(int i = 1; i < L; ++i)
    {
        vector<int> stringSplit = splitString(answer, " ");
        string newAnswer;
        int j = 0;
        int count = 0;
        int cInt = stringSplit[0];
        for(int j = 0; j < stringSplit.size(); j++)
        {
            int ccInt = stringSplit[j];
            if(ccInt != cInt)
            {
                //add to answer, update everything
                string localString = to_string(count);
                localString += " ";
                localString += to_string(cInt);
                localString += " ";
                newAnswer+= localString;
                
                count = 1;
                cInt = ccInt;
            }
            else
            {
                count++;
            }
        }
        
        if(count > 0)
        {
            string localString = to_string(count);
            localString += " ";
            localString += to_string(cInt);  
            newAnswer+= localString;
        }
                
        answer = newAnswer;
        cerr << answer << endl;
    }
    
    cout << answer << endl;
}