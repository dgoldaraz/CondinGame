/// You need to help Marvin and his clones (or is it the other way round?) reach the exit in order to help them escape the inside of the Infinite Improbability Drive.
///  	Rules
/// The drive has a rectangular shape of variable size. It is composed of several floors (0 = lower floor) and each floor has several possible positions that the clones can occupy (0 = leftmost position, width - 1 = rightmost position).
/// 
/// The goal is to save at least one clone in a limited amount of rounds.
/// 
/// The details:
/// Clones appear from a unique generator at regular intervals, every three game turns. The generator is located on floor 0. Clones exit the generator heading towards the right.
/// 
/// Clones move one position per turn in a straight line, moving in their current direction.
/// 
/// A clone is destroyed by a laser if it is goes below position 0 or beyond position width - 1.
/// 
/// Elevators are scattered throughout the drive and can be used to move from one floor to the one above. When a clone arrives on the location of an elevator, it moves up one floor. Moving up one floor takes one game turn. On the next turn, the clone continues to move in the direction it had before moving upward.
/// 
/// On each game turn you can either block the leading clone - meaning the one that got out the earliest - or do nothing.
/// 
/// Once a clone is blocked, you can no longer act on it. The next clone in line takes the role of "leading clone" and can be blocked at a later time.
/// 
/// When a clone moves towards a blocked clone, it changes direction from left to right or right to left. It also changes direction when getting out of the generator directly on a blocked clone or when going up an elevator onto a blocked clone.
/// 
/// If a clone is blocked in front of an elevator, the elevator can no longer be used.
/// 
/// When a clone reaches the location of the exit, it is saved and disappears from the area.
/// 
/// Note: For the first simple question, there is at most one elevator per floor.
/// 
/// Victory Conditions
/// You win if at least one clone reaches the exit location in a limited amount of game rounds
///  	Note
/// Don’t forget to run the tests by launching them from the “Test cases” window.
/// 
/// The tests provided are similar to the validation tests used to compute the final score but are slightly different.
///  	Game Input
/// The program must first read the initialization data from standard input. Then, within an infinite loop, read the contextual data (location of leading clone) from the standard input and provide the next instruction to standard output.
/// Initialization input
/// Line 1: 8 integers:
/// nbFloors : number of floors in the area. A clone can move between floor 0 and floor nbFloors - 1
/// width : the width of the area. The clone can move without being destroyed between position 0 and position width - 1
/// nbRounds : maximum number of rounds before the end of the game
/// exitFloor : the floor on which the exit is located
/// exitPos : the position of the exit on its floor
/// nbTotalClones : the number of clones that will come out of the generator during the game
/// nbAdditionalElevators : not used for this first question, value is always 0
/// nbElevators : number of elevators in the area
/// nbElevators next lines: 2 integers elevatorFloor elevatorPos providing the floor and position of an elevator.
/// Input for one game turn
/// Line 1: 2 integers cloneFloor clonePos and one string direction. cloneFloor and clonePos are the coordinates of the leading unblocked clone. direction indicates the current direction of the leading clone:
/// LEFT the clone is moving towards the left
/// RIGHT the clone moving towards the right
/// If there is no leading clone, the line values are: -1 -1 NONE. This can happen only when the clones which are already outside are all blocked and the next clone is not out yet. In this case, you may output action WAIT.
/// Output for one game turn
/// A single line (including newline character) to indicate which action to take:
/// Either the keyword WAIT to do nothing.
/// or the keyword BLOCK to block the leading clone.
/// Constraints
/// 1 ≤ nbFloors ≤ 15
/// 5 ≤ width ≤ 100
/// 10 ≤ nbRounds ≤ 200
/// 0 ≤ exitFloor, elevatorFloor < nbFloors
/// 0 ≤ exitPos , elevatorPos < width
/// -1 ≤ cloneFloor < nbFloors
/// -1 ≤ clonePos < width
/// 2 ≤ nbTotalClones ≤ 50
/// 0 ≤ nbElevators ≤ 100
/// Duration of one game turn: 100 ms

// Solution Code by dgoldaraz

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
 
string checkExit(int clonePos, int exitPos, string direction)
{
    //check the direction to block the minion
    if(exitPos < clonePos )
    {
        if(direction == "RIGHT")
        {
            //wrong dir, block
            return "BLOCK";
        }
    }
    else if(exitPos > clonePos)
    {
        if(direction == "LEFT")
        {
            return "BLOCK";
        }
    }
    
    return "WAIT";
}
int main()
{
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
   
    cerr << "Floors: " << nbFloors << endl;
    cerr << "Width: " << width << endl;
    cerr << "Rounds: " << nbRounds << endl;
    cerr << "ExitFloor: " << exitFloor <<" Exit Position: " << exitPos <<  endl;
    cerr << "Number of clones: " << nbTotalClones << endl;
    cerr << "Number of elevators: " << nbElevators << endl;
    
    map<int,vector<int>> elevatorsGraph;
    map<int,vector<int>>::iterator it;
    
    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        
        cerr << "Elevator " << i << " floor: " << elevatorFloor << " pos: " << elevatorPos << endl;
        
        //Save elevator info in a map. Each key will be the floor and a vector<int> for the different positions
        it = elevatorsGraph.find(elevatorFloor);
        if (it != elevatorsGraph.end())
        {
            it->second.push_back(elevatorPos);
        }
        else
        {   
            vector<int> positions(1,elevatorPos);
            elevatorsGraph[elevatorFloor] = positions;
        }
    }
    
    //Sort the positions from less to higher
    for(it = elevatorsGraph.begin(); it != elevatorsGraph.end(); ++it)
    {
        sort (it->second.begin(), it->second.end());
    }
    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();

        cerr << "Leader Floor: " << cloneFloor << " pos: " << clonePos << " Dir: " << direction << endl;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        string answer = "WAIT";
        if(cloneFloor != -1)
        {
       
            if(exitFloor == cloneFloor)
            {
                answer = checkExit(clonePos, exitPos, direction);
            }
            else
            {
                //check elevators
                map<int,vector<int>>::iterator floorIt = elevatorsGraph.find(cloneFloor);
                if(floorIt != elevatorsGraph.end())
                {
                    //Get vector, search closest elevator
                    
                    vector<int> elevatorPositions = floorIt->second; 
                    if(elevatorPositions.size() > 1)
                    {
                        //Use this only if there is more than one elevator
                        auto const it = lower_bound(elevatorPositions.begin(), elevatorPositions.end(), clonePos);
                        if (it != elevatorPositions.end())
                        {
                            answer = checkExit(clonePos, *it, direction);
                        }
                        
                        else
                        {
                            answer = checkExit(clonePos, elevatorPositions[0], direction);
                        }
                    }
                    else
                    {
                        answer = checkExit(clonePos, elevatorPositions[0], direction);
                    }
                }
            }
        }
       
        
        cout << answer << endl; // action: WAIT or BLOCK
    }
}