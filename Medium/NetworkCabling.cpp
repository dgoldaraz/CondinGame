/// An internet operator plans to connect a business park to the optical fiber network. The area to be covered is large and the operator is asking you to write a program that will calculate the minimum length of optical fiber cable required to connect all buildings.
///  	Rules
/// 
/// For the implementation of the works, the operator has technical constraints whereby it is forced to proceed in the following manner:
/// A main cable will cross through the park from the West to the East (from the position x of the most westerly building to the position x of the most easterly building).
/// 
/// For each building, a dedicated cable will connect from the building to the main cable by a minimal path (North or South), as shown in the following example:
///  
/// 	In this example, the green lines represent the cables.  
/// The minimum length will therefore depend on the position of the main cable.
/// 
///  	Game Input
/// 
/// Input
/// Line 1: The number N of buildings that need to be connected to the optical fiber network
/// 
/// On the N following lines: The coordinates x and y of the buildings
/// 
/// Output
/// 
/// The minimum length L of cable required to connect all of the buildings. In other words, the length of the main cable plus the length of the cables dedicated to all the buildings.
/// 
/// Note: the buildings with the same position x should not in any case share the same dedicated cable.
/// 
/// Constraints
/// 0 < N ≤ 100000
/// 0 ≤ L ≤ 263
/// -230 ≤ x ≤ 230
/// -230 ≤ y ≤ 230
/// 
/// Example 1
/// 
/// Input
/// 3
/// 0 0
/// 1 1
/// 2 2
/// 
/// Output
/// 4
/// 
/// Example 2
/// 
/// Input
/// 3
/// 1 2
/// 0 0
/// 2 2
/// 
/// Output
/// 4

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
 class House
 {
     private:
        int m_x;
        int m_y;
    
    public:
    
     House(int x, int y)
     {
        m_x = x;
        m_y = y;
     }
     
     int getX()
     {
         return m_x;
     }
     int getY()
     {
         return m_y;
     }
     
     void print()
     {
         cerr << "House on " << m_x << "," << m_y << endl;
     }
 };
 
long long calculateDistance(int Y, vector<House*> h)
{
    //Calculate the aacumulateDistance from all the houses to the Y poosition
    long long acD = 0;
    for(int i = 0; i < h.size(); ++i)
    {   
        acD += abs(Y - h[i]->getY());
    }
    return abs(acD);
}

int getBestY(vector<House*> h)
{
    vector<int> yes;
    for(int i = 0; i < h.size(); i++)
    {
        yes.push_back(h[i]->getY());
    }
    sort (yes.begin(), yes.end());
    
    return yes[ceil(yes.size() *0.5) -1];
}

long long findSmallDistances( int minY, int maxY, vector<House*> houses)
{
    int bestY = getBestY(houses);
    
    return calculateDistance(bestY, houses);
}

int main()
{
    int N;
    cin >> N; cin.ignore();
    vector<House*> houses;
    House* lHouse = nullptr;
    House* rHouse = nullptr;
    int upY = 0;
    int downY = 1000;
    
    for (int i = 0; i < N; i++) {
        int X;
        int Y;
        cin >> X >> Y; cin.ignore();
        House* cH = new House(X,Y);
        houses.push_back(cH);
        if(!lHouse)
        {
            lHouse = cH;
        }
        else
        {
            if(X < lHouse->getX())
            {
                lHouse = cH;
            }
        }
        if(!rHouse)
        {
            rHouse = cH;
        }
        else
        {
            if(X > rHouse->getX())
            {
                rHouse = cH;
            }
        }
        if(Y > upY )
        {
            upY = Y;
        }
        if(Y < downY )
        {
            downY = Y;
        }
    }
    
    long long length = 0;
    if(houses.size() > 1)
    {
        length = abs(rHouse->getX() - lHouse->getX());
        long long smallDistance = findSmallDistances(downY, upY, houses);
        length += smallDistance;
    }
    
    cout << length << endl;
}