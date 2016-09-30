/// In this exercise, you have to analyze records of temperature to find the closest to zero.
/// 
/// Sample temperatures
/// Here, -1 is the closest to 0.
///  	
/// 	Rules
/// 
/// Write a program that prints the temperature closest to 0 among input data. If two numbers are equally close to zero, positive integer has to be considered closest to zero (for instance, if the temperatures are -5 and 5, then display 5).
///  	Game Input
/// 
/// Your program must read the data from the standard input and write the result on the standard output.
/// 
/// Input
/// Line 1: N, the number of temperatures to analyze
/// 
/// Line 2: A string with the N temperatures expressed as integers ranging from -273 to 5526
/// 
/// Output
/// 
/// Display 0 (zero) if no temperatures are provided. Otherwise, display the temperature closest to 0.
/// 
/// Constraints
/// 0 ≤ N < 10000
/// 
/// Example
/// 
/// Input
/// 5
/// 1 -2 -8 4 5
/// 
/// Output
/// 1

// Solution Code by dgoldaraz

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    getline(cin, temps);

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    int finalResult = 0;
    
    if( n > 0)
    {
        vector<int> inputs;
        int value;
        stringstream stream(temps);
        
        while( stream >> value)
        {
            if(value < 10000)
            {
                inputs.push_back(value);
            }
        }
        
        int result;
        
        for( int i = 0; i < inputs.size(); i++)
        {
            int cValue = inputs[i];
            if(abs(cValue) < abs(result)) 
            {
                result = cValue;
            }
            else if( abs(cValue) == abs(result))
            {
                if( cValue> result)
                {
                    result = inputs[i];
                }
            }
        }
        finalResult = result;
    }
    
    
    cout << finalResult << endl;
}