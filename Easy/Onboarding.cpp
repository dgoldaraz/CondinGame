/// Your program must destroy the enemy ships by shooting the closest enemy on each turn.
///  	Rules
/// 
/// On each start of turn (within the game loop), you obtain information on the two closest enemies:
/// enemy1 and dist1: the name and the distance to enemy 1.
/// enemy2 and dist2: the name and the distance to enemy 2.
/// Before your turn is over (end of the loop), output the value of either enemy1 or enemy2 to shoot the closest enemy.

// Solution Code by dgoldaraz:

#include <iostream>

using namespace std;

int main()
{

    // game loop
    while (1) {
        string enemy1; // name of enemy 1
        cin >> enemy1; cin.ignore();
        int dist1; // distance to enemy 1
        cin >> dist1; cin.ignore();
        string enemy2; // name of enemy 2
        cin >> enemy2; cin.ignore();
        int dist2; // distance to enemy 2
        cin >> dist2; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"

        // Enter the code here
        
        if (dist1 < dist2) {
            cout << enemy1 << endl;
        }  else {
            cout << enemy2 << endl;
        }

    }
}