/// The goal for your program is to safely land the "Mars Lander" shuttle, the landing ship which contains the Opportunity rover. Mars Lander is guided by a program, and right now the failure rate for landing on the NASA simulator is unacceptable.
/// 
/// This puzzle is the second level of the "Mars Lander" trilogy. The controls are the same as the previous level but you must now control the angle in order to succeed.
///  	Rules
/// 
/// Built as a game, the simulator puts Mars Lander on a limited zone of Mars sky.
/// 
/// 	The zone is 7000m wide and 3000m high.
/// 
/// There is a unique area of flat ground on the surface of Mars, which is at least 1000 meters wide.Every second, depending on the current flight parameters (location, speed, fuel ...), the program must provide the new desired tilt angle and thrust power of Mars Lander:
/// 	Angle goes from -90° to 90° . Thrust power goes from 0 to 4 .
///   The game simulates a free fall without atmosphere. Gravity on Mars is 3.711 m/s² . For a thrust power of X, a push force equivalent to X m/s² is generated and X liters of fuel are consumed. As such, a thrust power of 4 in an almost vertical position is needed to compensate for the gravity on Mars.
/// 
/// For a landing to be successful, the ship must:
/// land on flat ground
/// land in a vertical position (tilt angle = 0°)
/// vertical speed must be limited ( ≤ 40m/s in absolute value)
/// horizontal speed must be limited ( ≤ 20m/s in absolute value)
///  	Note
/// 
/// Tests and validators are only slightly different. A program that passes a given test will pass the corresponding validator without any problem.
///  	Game Input
/// 
/// The program must first read the initialization data from standard input. Then, within an infinite loop, the program must read the data from the standard input related to Mars Lander's current state and provide to the standard output the instructions to move Mars Lander.
/// Initialization input
/// Line 1: the number surfaceN of points used to draw the surface of Mars.
/// Next surfaceN lines: a couple of integers landX landY providing the coordinates of a ground point. By linking all the points together in a sequential fashion, you form the surface of Mars which is composed of several segments. For the first point, landX = 0 and for the last point, landX = 6999
/// Input for one game turn
/// A single line with 7 integers: X Y hSpeed vSpeed fuel rotate power
/// X,Y are the coordinates of Mars Lander (in meters).
/// hSpeed and vSpeed are the horizontal and vertical speed of Mars Lander (in m/s). These can be negative depending on the direction of Mars Lander.
/// fuel is the remaining quantity of fuel in liters. When there is no more fuel, the power of thrusters falls to zero.
/// rotate is the angle of rotation of Mars Lander expressed in degrees.
/// power is the thrust power of the landing ship.
/// Output for one game turn
/// A single line with 2 integers: rotate power :
/// rotate is the desired rotation angle for Mars Lander. Please note that for each turn the actual value of the angle is limited to the value of the previous turn +/- 15°.
/// power is the desired thrust power. 0 = off. 4 = maximum power. Please note that for each turn the value of the actual power is limited to the value of the previous turn +/- 1.
/// Constraints
/// 2 ≤ surfaceN < 30
/// 0 ≤ X < 7000
/// 0 ≤ Y < 3000
/// -500 < hSpeed, vSpeed < 500
/// 0 ≤ fuel ≤ 2000
/// -90 ≤ rotate ≤ 90
/// 0 ≤ power ≤ 4
/// Response time per turn ≤ 100ms

/// Example

/// Initialization input
/// 6         	(surfaceN) Surface made of 6 points
/// 0 1500      	(landX landY)
/// 1000 2000	(landX landY)
/// 2000 500	(landX landY) Start of flat ground
/// 3500 500	(landX landY) End of flat ground
/// 5000 1500	(landX landY)
/// 6999 1000	(landX landY)
/// No output expected
/// You can ignore this but you need to read the values.

/// Input for turn 1
/// 5000 2500 -50 0 1000 90 0	(X Y hSpeed vSpeed fuel rotate power)

/// Output for turn 1
/// -45 4 (rotate power)
/// Requested rotation to the right, maximum thrust power

/// Input for turn 2
/// 4950 2498 -51 -3 999 75 1	(X Y hSpeed vSpeed fuel rotate power)
/// Tilt angle changed only by 15° and thrust power only by 1

/// Output for turn 2
/// -45 4 (rotate power)
/// Same request as previous turn

/// Input for turn 3
/// 4898 2493 -53 -6 997 60 2	(X Y hSpeed vSpeed fuel rotate power)

/// Output for turn 3
/// -45 4 (rotate power)
/// Same request as previous turn

/// Solution Code by dgoldaraz

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
    int surfaceN; // the number of points used to draw the surface of Mars.
    cin >> surfaceN; cin.ignore();
    
    int lY = 0;
    int lXmin,lXmax = 0;
    for (int i = 0; i < surfaceN; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> landX >> landY; cin.ignore();
        
        if(lXmax == 0)
        {
            if(landY == lY)
            {
                lXmax = landX;
            }
            else
            {
                lY = landY;
                lXmin = landX;
            }
        }
        //cerr << landX << "," << landY << endl;
    }
    
    cerr << "Landing: " << lXmin<< "-" << lXmax << " Altitude: " << lY << endl;
    
    // game loop
    while (1) {
        int X;
        int Y;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cerr << "Position: " << X << "," << Y << " hSpeed:" << hSpeed << " vSpeed:" << vSpeed << endl;
        cerr << "Fuel:" << fuel << " Rotation:" << rotate << " Power: " << power << endl; 
        
        int cRotate = rotate;
        int cPower = power;
        
        //This is the landing zone, try to avoid big speeds and have a rotation 0
        if( X > lXmin && X <= lXmax)
        {
            
            //If the vertical speed is bigger than min, try to reduce power and rotation 0
            if(vSpeed < 40 && vSpeed > -40)
            {
                cRotate = 0;
                cPower = Y / 600;
            }
            //If the hSpeed is more than 0, try to reduce it by rotating the ship
            if (hSpeed < 0)
            {
                cRotate = -15;
            }
            else if(hSpeed > 0)
            {
                cRotate = 15;
            }
            
            //If we are close to the floor => Rotaton 0
            if( Y - lY < 50)
            {
                cRotate = 0;
            }
        }
        else
        {
            //Approach the landing zone moving the ship to the right
            if( X < lXmin)
            {
                //we need to rotate to reach the point!
                int distance = (lXmin - X) * 0.5;
                float ratio = distance / 7000.0f;
                //Don't go to extreme rotations (more than 45) per turn
                cRotate += -45 * ratio;
                //Never pass the 70 degree (safety)
                if(cRotate < -70)
                {
                    cRotate = -70;
                }
            }
            //Approach the landing zone moving the ship to the Left
            if (X > lXmax)
            {
                int distance = (X - lXmax) * 0.5;
                float ratio = distance / 7000.0f;
                cRotate += 45 * ratio;
                if(cRotate > 70)
                {
                    cRotate = 70;
                }
            }
            //Try to increase the power to reach the position
            if(cPower < 3)
            {
                cPower++;
            }
            else if (abs(hSpeed) > 50)
            {
                cPower = 4;
            }
            
        }
        
        //If hVelocity increase, try to rotate and avoid extreme cases
        if(hSpeed > 40)
        {
            cRotate = 20 * (hSpeed / 40);
        }
        else if (hSpeed < -40)
        {
            cRotate = 20 * (hSpeed / 40);
        }
        
        //If we are too high, slow down the power
        if( Y > 2800 )
        {
            cPower = 1;
        }
            
        //Maintain a good velocity always(using power), avoiding extreme velocities
        
        if(vSpeed >= 40)
        {
            if(cPower > 0)
            {
                cPower--;
            }
        }
        
        if(vSpeed <= -40 )
        {
            if(cPower < 4)
            {
                cPower++;
            }
        }
        // rotate power. rotate is the desired rotation angle. power is the desired thrust power.
        cout << cRotate << " " << cPower << endl;
    }
}