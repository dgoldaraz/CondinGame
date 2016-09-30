///What will I practice?

///Loops
///This puzzles shows that sometimes, the simplest solution is not performant enough. You will also learn to handle large arrays and experience with their processing time.
///External resources SortingLists
///Statement

///In this problem you have to find the two numbers that are closest to each other among a list of numbers. The list might be really large and force you to search for the best possible algorithmic complexity for your solution.

///Input
///Line 1: Number N of horses

///The N following lines: the strength Pi of each horse. Pi is an integer.

///Output
///The difference D between the two closest strengths. D is an integer greater than or equal to 0.
///Constraints
///1 < N  < 100000
///0 < Pi ≤ 10000000
///Example
///Input
///3
///5
///8
///9
///    Output
///      1

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
    int N;
    cin >> N; cin.ignore();
    vector<int> positions;
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
        positions.push_back(Pi);
    }
    sort(positions.begin(), positions.begin() + positions.size());
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    int distance = 100;
    for(int i = 0; i < positions.size()-1; ++i)
    {
        int nD = positions[i+1] - positions[i];
        if(nD < distance)
        {
            distance = nD;
        }
    }
	
    cout << distance << endl;
}