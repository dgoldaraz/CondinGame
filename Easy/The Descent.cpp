/// Destroy the mountains before your starship collides with one of them. For that, shoot the highest mountain on your path.
///  	Rules
/// 
/// At the start of each game turn, you are given the height of the 8 mountains from left to right.
/// By the end of the game turn, you must fire on the highest mountain by outputting its index (from 0 to 7).
/// 
/// Firing on a mountain will only destroy part of it, reducing its height. Your ship descends after each pass.  
///  
/// Victory Conditions
/// You win if you destroy every mountain
///  
/// Lose Conditions
/// Your ship crashes into a mountain
/// You provide incorrect output or your program times out
/// 
/// Within an infinite loop, read the heights of the mountains from the standard input and print to the standard output the index of the mountain to shoot.
/// 
/// Input for one game turn
/// 8 lines: one integer mountainH per line. Each represents the height of one mountain given in the order of their index (from 0 to 7).
/// 
/// Output for one game turn
/// A single line with one integer for the index of which mountain to shoot.
/// 
/// Constraints
/// 0 ≤ mountainH ≤ 9
/// 
/// Response time per turn ≤ 100ms

//Solution Code by dgoldaraz

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

    // game loop
    while (1) {
        
        int indexH = 0;
        int maxH = -1;
        
        for (int i = 0; i < 8; i++) {
            int mountainH; // represents the height of one mountain, from 9 to 0.
            cin >> mountainH; cin.ignore();
            if(mountainH > maxH)
            {
                indexH = i;
                maxH = mountainH;
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << indexH << endl; // The number of the mountain to fire on.
    }
}