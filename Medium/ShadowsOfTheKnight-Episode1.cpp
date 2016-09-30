/// Batman will look for the hostages on a given building by jumping from one window to another using his grapnel gun. Batman's goal is to jump to the window where the hostages are located in order to disarm the bombs. Unfortunately he has a limited number of jumps before the bombs go off...
///  	Rules
/// 
/// Before each jump, the heat-signature device will provide Batman with the direction of the bombs based on Batman current position: 
/// U (Up)
/// UR (Up-Right)
/// R (Right)
/// DR (Down-Right)
/// D (Down)
/// DL (Down-Left)
/// L (Left)
/// UL (Up-Left)
/// 
/// Your mission is to program the device so that it indicates the location of the next window Batman should jump to in order to reach the bombs' room as soon as possible.
/// 
/// Buildings are represented as a rectangular array of windows, the window in the top left corner of the building is at index (0,0).
///  	Note
/// 
/// For some tests, the bombs' location may change from one execution to the other: the goal is to help you find the best algorithm in all cases.
/// 
/// The tests provided are similar to the validation tests used to compute the final score but remain different.
///  	Game Input
/// 
/// The program must first read the initialization data from standard input. Then, within an infinite loop, read the device data from the standard input and provide to the standard output the next movement instruction.
/// Initialization input
/// Line 1 : 2 integers W H. The (W, H) couple represents the width and height of the building as a number of windows.
/// 
/// Line 2 : 1 integer N, which represents the number of jumps Batman can make before the bombs go off.
/// 
/// Line 3 : 2 integers X0 Y0, representing the starting position of Batman.
/// 
/// Input for one game turn
/// The direction indicating where the bomb is.
/// Output for one game turn
/// A single line with 2 integers X Y separated by a space character. (X, Y) represents the location of the next window Batman should jump to. X represents the index along the horizontal axis, Y represents the index along the vertical axis. (0,0) is located in the top-left corner of the building.
/// Constraints
/// 1 ≤ W ≤ 10000
/// 1 ≤ H ≤ 10000
/// 2 ≤ N ≤ 100
/// 0 ≤ X, X0 < W
/// 0 ≤ Y, Y0 < H
/// Response time per turn ≤ 150ms
/// Response time per turn ≤ 150ms
/// Example
/// Initialization input
/// 10 10     Building has 100 windows (10x10)
/// 6         Batman has 6 jumps to find the bombs
/// 2 5       Batman starts at position (2,5)
///  
/// No output expected
/// Input for turn 1
/// UR
/// Hostages are in the upward-right direction
///  
/// Output for turn 1
/// 5 4
/// Batman jumps to window (5,4)
/// Input for turn 2
/// R
/// Hostages are located to the right of Batman
///  
/// Output for turn 2
/// 7 4
/// Batman jumps to window (7,4)
///  
/// Batman found the hostages. He can defuse the bombs in time. You win!

// Code Solution by dgoldaraz

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
void updateData(int& l, int& r, int& u, int& d, int X, int Y, string bombDir)
{
    
    if( bombDir.find("U") != string::npos)
    {
        cerr << "Up" << endl;
        d = Y;
    }
    if( bombDir.find("D") != string::npos)
    {
        cerr << "Down" << endl;
        u = Y;
    }
    if( bombDir.find("R") != string::npos)
    {
        cerr << "Right" << endl;
        l = X;
    }
    if( bombDir.find("L") != string::npos)
    {
        cerr << "Left" << endl;
        r = X;
    }
}

void calculateNextJump( int l, int r, int u, int d, int& X, int& Y, string bombDir)
{
    int xIncrement = ceil((r - l) * 0.5);
    int yIncrement = ceil((d - u) * 0.5);
    
    if( bombDir.find("U") != string::npos)
    {
        Y = Y - yIncrement;
    }
    if( bombDir.find("D") != string::npos)
    {
        Y = Y + yIncrement;
    }
    if( bombDir.find("R") != string::npos)
    {
        X = X + xIncrement;
    }
    if( bombDir.find("L") != string::npos)
    {
        X = X - xIncrement;
    }
    
}

int main()
{
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();

    int left = 0;
    int right = W;
    int up = 0;
    int down = H;
    
    // game loop
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();
        
        
        updateData(left,right,up,down,X0,Y0, bombDir);
        
        cerr << "L: "<< left <<" R: " << right << " U: " << up <<" D: " << down;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        //Choose a new location based on the square formed by l,r,u,d
        
        
        calculateNextJump(left,right,up,down,X0,Y0, bombDir);
        
        string answer;
        answer += to_string(X0);
        answer += " ";
        answer += to_string(Y0);
        
        // the location of the next window Batman should jump to.
        cout << answer << endl;
    }
}