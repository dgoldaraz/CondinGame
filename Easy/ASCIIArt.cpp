/// 
/// ASCII art allows you to represent forms by using characters. To be precise, in our case, these forms are words. For example, the word "MANHATTAN" could be displayed as follows in ASCII art:
/// 
///  
/// # #  #  ### # #  #  ### ###  #  ###
/// ### # # # # # # # #  #   #  # # # #
/// ### ### # # ### ###  #   #  ### # #
/// # # # # # # # # # #  #   #  # # # #
/// # # # # # # # # # #  #   #  # # # #
///  
​/// Your mission is to write a program that can display a line of text in ASCII art in a style you are given as input.
/// 
///  	Game Input
/// 
/// Input
/// 
/// Line 1: the width L of a letter represented in ASCII art. All letters are the same width.
/// 
/// Line 2: the height H of a letter represented in ASCII art. All letters are the same height.
/// 
/// Line 3: The line of text T, composed of N ASCII characters.
/// 
/// Following lines: the string of characters ABCDEFGHIJKLMNOPQRSTUVWXYZ? Represented in ASCII art.
/// 
/// Output
/// 
/// The text T in ASCII art.
/// The characters a to z are shown in ASCII art by their equivalent in upper case.
/// The characters that are not in the intervals [a-z] or [A-Z] will be shown as a question mark in ASCII art.
/// 
/// Constraints
/// 0 < L < 30
/// 0 < H < 30
/// 0 < N < 200
/// 
/// 
/// Example 1
/// 
/// Input
/// 4
/// 5 
/// E
///  #  ##   ## ##  ### ###  ## # # ###  ## # # #   # # ###  #  ##   #  ##   ## ### # # # # # # # # # # ### ### 
/// # # # # #   # # #   #   #   # #  #    # # # #   ### # # # # # # # # # # #    #  # # # # # # # # # #   #   # 
/// ### ##  #   # # ##  ##  # # ###  #    # ##  #   ### # # # # ##  # # ##   #   #  # # # # ###  #   #   #   ## 
/// # # # # #   # # #   #   # # # #  #  # # # # #   # # # # # # #    ## # #   #  #  # # # # ### # #  #  #       
/// # # ##   ## ##  ### #    ## # # ###  #  # # ### # # # #  #  #     # # # ##   #  ###  #  # # # #  #  ###  #  
/// 
/// Output
/// ### 
/// #   
/// ##  
/// #   
/// ### 
/// 
/// Example 2
/// 
/// Input
/// 4
/// 5
/// MANHATTAN
///  #  ##   ## ##  ### ###  ## # # ###  ## # # #   # # ###  #  ##   #  ##   ## ### # # # # # # # # # # ### ### 
/// # # # # #   # # #   #   #   # #  #    # # # #   ### # # # # # # # # # # #    #  # # # # # # # # # #   #   # 
/// ### ##  #   # # ##  ##  # # ###  #    # ##  #   ### # # # # ##  # # ##   #   #  # # # # ###  #   #   #   ## 
/// # # # # #   # # #   #   # # # #  #  # # # # #   # # # # # # #    ## # #   #  #  # # # # ### # #  #  #       
/// # # ##   ## ##  ### #    ## # # ###  #  # # ### # # # #  #  #     # # # ##   #  ###  #  # # # #  #  ###  #  
/// 
/// Output
/// # #  #  ### # #  #  ### ###  #  ###  
/// ### # # # # # # # #  #   #  # # # #  
/// ### ### # # ### ###  #   #  ### # #  
/// # # # # # # # # # #  #   #  # # # #  
/// # # # # # # # # # #  #   #  # # # # 

// Solution Code by dgoldaraz:

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T;
    getline(cin, T);
    
    //cerr << "L: " << L << " H:" << H << " T: "<< T << endl;
    
    vector<string> letters;
    for (int i = 0; i < H; i++) {
        string ROW;
        getline(cin, ROW);
        letters.push_back(ROW);
    }
    
    string answer = "";
    for(int j = 0; j < letters.size(); ++j)
    {
        string line = letters.at(j);
        for(int i = 0; i < T.size(); i++)
        {   
            char c = T.at(i);
            int position = -1;
        
            if (c >= 'a' && c <= 'z') 
            {
                position =  c - 'a';
            }
            else if (c >= 'A' && c <= 'Z') 
            {
                position =  c - 'A';
            }
            if(position < 0)
            {
                //Go to the very end
                position  = 26;
            }
            int start = L * position;
            for( int k = 0; k < L; k++)
            {
                //cout << position << endl;
                answer.push_back(line[start + k]);
            }
        }
        answer.push_back('\n');
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << answer << endl;
}