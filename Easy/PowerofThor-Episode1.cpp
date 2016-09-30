/// Your program must allow Thor to reach the light of power.
///  	Rules
/// 
/// Thor moves on a map which is 40 wide by 18 high. Note that the coordinates (X and Y) start at the top left! This means the most top left cell has the coordinates "X=0,Y=0" and the most bottom right one has the coordinates "X=39,Y=17".
/// 
/// Once the program starts you are given:
/// the variable lightX: the X position of the light of power that Thor must reach.
/// the variable lightY: the Y position of the light of power that Thor must reach.
/// the variable initialTX: the starting X position of Thor.
/// the variable initialTY: the starting Y position of Thor.
/// At the end of the game turn, you must output the direction in which you want Thor to go among:
/// 	
/// N (North)
/// NE (North-East)
/// E (East)
/// SE (South-East)
/// S (South)
/// SW (South-West)
/// W (West)
/// NW (North-West)
/// Each movement makes Thor move by 1 cell in the chosen direction.
///  
///  
/// Victory Conditions
/// You win when Thor reaches the light of power
///  
/// Lose Conditions
/// Thor moves outside the map
/// 
/// The program must first read the initialization data from the standard input, then, in an infinite loop, provides on the standard output the instructions to move Thor.
/// 
/// Initialization input
/// Line 1: 4 integers lightX lightY initialTX initialTY. (lightX, lightY) indicates the position of the light. (initialTX, initialTY) indicates the initial position of Thor.
/// 
/// Input for a game round
/// Line 1: the number of remaining moves for Thor to reach the light of power: remainingTurns. You can ignore this data but you must read it.
/// 
/// Output for a game round
/// A single line providing the move to be made: N NE E SE S SW W ou NW
/// 
/// Constraints
/// 0 ≤ lightX < 40
/// 0 ≤ lightY < 18
/// 0 ≤ initialTX < 40
/// 0 ≤ initialTY < 18
/// 
/// Response time for a game round ≤ 100ms

// Solution Code by dgoldaraz:
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/
int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    cin >> lightX >> lightY >> initialTX >> initialTY; cin.ignore();
    
    int distanceX = lightX - initialTX;
    int distanceY = lightY - initialTY;

    char* dir = "N";
    // game loop
    while (1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        cin >> remainingTurns; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
       
        if(distanceX == 0)
        {
            //Go south/North
            if(distanceY < 0)
            {
                dir = "N";
                distanceY++;
            }
            else
            {
                dir = "S";
                distanceY--;
            }
        }
        else if( distanceX < 0)
        {
            if(distanceY == 0)
            {
                dir = "W";
                distanceX++;
            }
            else if( distanceY < 0)
            {
                dir = "NE";
                distanceX--;
                distanceY--;
            }
            else
            {
                dir = "SW";
                distanceX++;
                distanceY--;
            }
        }
        else
        {
            if(distanceY == 0)
            {
                dir = "E";
                distanceX--;
            }
            else if( distanceY < 0)
            {
                dir = "NE";
                distanceX--;
                distanceY++;
            }
            else
            {
                dir = "SE";
                distanceX--;
                distanceY--;
            }
        }
        // A single line providing the move to be made: N NE E SE S SW W or NW
        cout << dir << endl;
    }
}