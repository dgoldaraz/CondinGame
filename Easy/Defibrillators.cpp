/// The city of Montpellier has equipped its streets with defibrillators to help save victims of cardiac arrests. The data corresponding to the position of all defibrillators is available online.
/// 
/// Based on the data we provide in the tests, write a program that will allow users to find the defibrillator nearest to their location using their mobile phone.
///  	Rules
/// 
/// The input data you require for your program is provided in text format.
/// This data is comprised of lines, each of which represents a defibrillator. Each defibrillator is represented by the following fields:
/// A number identifying the defibrillator
/// Name
/// Address
/// Contact Phone number
/// Longitude (degrees)
/// Latitude (degrees)
/// These fields are separated by a semicolon (;).
/// 
/// Beware: the decimal numbers use the comma (,) as decimal separator. Remember to turn the comma (,) into dot (.) if necessary in order to use the data in your program.
///  
/// DISTANCE
/// The distance d between two points A and B will be calculated using the following formula:
/// 
/// 
​/// 
/// Note: In this formula, the latitudes and longitudes are expressed in radians. 6371 corresponds to the radius of the earth in km.
/// 
/// The program will display the name of the defibrillator located the closest to the user’s position. This position is given as input to the program.
///  	Game Input
/// 
/// Input
/// Line 1: User's longitude (in degrees)
/// 
/// Line 2: User's latitude (in degrees)
/// 
/// Line 3: The number N of defibrillators located in the streets of Montpellier
/// 
/// N next lines: a description of each defibrillator
/// 
/// Output
/// The name of the defibrillator located the closest to the user’s position. 

/// Constraints
/// 0 < N < 10000

/// Example

/// Entrée
/// 3,879483
/// 43,608177
/// 3
/// 1;Maison de la Prevention Sante;6 rue Maguelone 340000 Montpellier;;3,87952263361082;43,6071285339217
/// 2;Hotel de Ville;1 place Georges Freche 34267 Montpellier;;3,89652239197876;43,5987299452849
/// 3;Zoo de Lunaret;50 avenue Agropolis 34090 Mtp;;3,87388031141133;43,6395872778854

/// Sortie
/// Maison de la Prevention Sante

// Solution Code by dgoldaraz:

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
float stringToFloat(string token)
{
    size_t commaFound = token.find(",");
    if(commaFound != string::npos)
    {
        token.replace(commaFound,1,".");
    }
    
    return stof(token);
}

float degreeToRadians(float deg)
{
    return (deg * pi / 180.0);
}
 
int main()
{
    string LON;
    cin >> LON; cin.ignore();
    string LAT;
    cin >> LAT; cin.ignore();
    int N;
    cin >> N; cin.ignore();
    string answer;
    
    
             
    float LONA = degreeToRadians(stringToFloat(LON));
    float LATA = degreeToRadians(stringToFloat(LAT));
    float distance = 100000;
    for (int i = 0; i < N; i++) 
    {
        string DEFIB;
        getline(cin, DEFIB);
        //cerr << DEFIB << endl;
        size_t found = DEFIB.find_first_of(";");
        int tokenNumber = 1;
        string tokenName;
        float LONB = 0.0f;
        float LATB = 0.0f;
        while (found!=string::npos)
        {
            size_t endToken = DEFIB.find(";",found + 1);
            tokenNumber++;
            size_t length = (endToken -1)- found;
            string newToken = DEFIB.substr(found+1,length);
            if(tokenNumber == 2)
            {
                tokenName = newToken;
            }
            if(tokenNumber == 5)
            {
                //Longitude
                LONB = degreeToRadians(stringToFloat(newToken));
            }
            if(tokenNumber == 6)
            {
                //Latitude
                LATB = degreeToRadians(stringToFloat(newToken));
            }
           
            found = DEFIB.find(";",found + 1);
        }
        //calculate distance
        float x = (LONB - LONA) * (cos((LATA + LATB)*0.5));
        float y = LATB - LATA;
        float newDist = sqrt(pow(x,2) + pow(y,2)) * earthRadiusKm;
        if(newDist < distance)
        {
            distance = newDist;
            answer = tokenName;
        }
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << answer << endl;
}