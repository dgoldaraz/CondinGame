/// Upon discovering a new Maya site, hundreds of mathematics, physics and astronomy books have been uncovered.
/// 
/// The end of the world might arrive sooner than we thought, but we need you to be sure that it doesn't!
/// 
/// Thus, in order to computerize the mayan scientific calculations, you're asked to develop a program capable of performing basic arithmetical operations between two mayan numbers.
///  	Rules
/// 
/// The mayan numerical system contains 20 numerals going from 0 to 19. Here's an ASCII example of their representation:
/// 0	1	2	3	4	5	6	7	8	9
/// .oo.
/// o..o
/// .oo.
/// ....	o...
/// ....
/// ....
/// ....	oo..
/// ....
/// ....
/// ....	ooo.
/// ....
/// ....
/// ....	oooo
/// ....
/// ....
/// ....	....
/// ----
/// ....
/// ....	o...
/// ----
/// ....
/// ....	oo..
/// ----
/// ....
/// ....	ooo.
/// ----
/// ....
/// ....	oooo
/// ----
/// ....
/// ....
/// 10	11	12	13	14	15	16	17	18	19
/// ....
/// ----
/// ----
/// ....	o...
/// ----
/// ----
/// ....	oo..
/// ----
/// ----
/// ....	ooo.
/// ----
/// ----
/// ....	oooo
/// ----
/// ----
/// ....	....
/// ----
/// ----
/// ----	o...
/// ----
/// ----
/// ----	oo..
/// ----
/// ----
/// ----	ooo.
/// ----
/// ----
/// ----	oooo
/// ----
/// ----
/// ---- A mayan number is divided into vertical sections. Each section contains a numeral (from 0 to 19) representing a power of 20. The lowest section corresponds to 200, the one above to 201 and so on.
/// 
/// Thereby, the example below is : (12 x 20 x 20) + (0 x 20) + 5 = 4805
/// 
/// 
/// 
/// To spice the problem up, the mayans used several dialects, and the graphical representation of the numerals could vary from one dialect to another.
///  
/// The representation of the mayan numerals will be given as the input of your program in the form of ASCII characters. You will have to display the result of the operation between the two given mayan numbers. The possible operations are *, /, +, -
///  	Game Input
/// 
/// Input
/// Line 1: the width L and height H of a mayan numeral.
/// 
/// H next lines: the ASCII representation of the 20 mayan numerals. Each line is (20 x L) characters long.
/// 
/// Next line: the amount of lines S1 of the first number.
/// 
/// S1 next lines: the first number, each line having L characters.
/// 
/// Next line: the amount of lines S2 of the second number.
/// 
/// S2 next lines: the second number, each line having L characters.
/// 
/// Last line: the operation to carry out: *, /, +, or -
/// 
/// Output
/// The result of the operation in mayan numeration, H lines per section, each line having L characters.
/// Constraints
/// 0 < L, H < 100
/// 0 < S1, S2 < 1000
/// The remainder of a division is always 0.
/// The mayan numbers given as input will not exceed 263.

/// Example

/// Input
/// 4 4
/// .oo.o...oo..ooo.oooo....o...oo..ooo.oooo____o...oo..ooo.oooo____o...oo..ooo.oooo
/// o..o................____________________________________________________________
/// .oo.........................................____________________________________
/// ................................................................________________
/// 4
/// o...
/// ....
/// ....
/// ....
/// 4
/// o...
/// ....
/// ....
/// ....
/// +

/// Output
/// oo..

// Solution code by dgoldaraz:
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
class MayanDictionary
{
    private:
        //width and height of one maya numeral
        int m_w;
        int m_h;
        
        //We'll have a double map for numbers/maya signs
        map<string, int> mayaToNumber;
        map<int,string> numberToMaya;
        
    public:
        MayanDictionary(int W, int H)
        {
            m_w = W;
            m_h = H;
        }
        ~MayanDictionary()
        {
            mayaToNumber.clear();
            numberToMaya.clear();
        }
        
        void addMayaDictionary(string n)
        {
            int lineSize = n.size() / m_h;
            int numberInD = lineSize /m_w;
            for(int i = 0; i < numberInD; i++)
            {
                string mNumber;
                for(int j = 0; j < m_h; j++)
                {
                    mNumber += n.substr(i * m_w + j*lineSize, m_w);
                }
                
                mayaToNumber[mNumber] = i;
                numberToMaya[i] = mNumber;
            }
        }
        
        long convertToNumber(string mayaN)
        {
            //Get substrings based on H
            int lineSize = (m_h*m_w);
            int nNumbers = mayaN.size() / lineSize;
            
            //cerr << "Numbers : " << nNumbers << endl;
            //cerr <<"Initial " << mayaN << endl;
            long result = 0;
            for(int i = nNumbers; i > 0; --i)
            {
                string mNumber = mayaN.substr((nNumbers - i) * lineSize, lineSize);
                //cerr << "Search " << mNumber << endl;
                map<string,int>::iterator it = mayaToNumber.find(mNumber);
                if( it != mayaToNumber.end())
                {
                    result += it->second * pow(20, i-1);
                }
                else
                {
                    cerr << "number not found " <<  mNumber << endl;
                    return -1;
                }
            }
            return result;
        }
        
        int intlog(double base, double x) 
        {
            return (int)(log(x) / log(base));
        }

        string convertToMaya(long number)
        {
            //Get maya numbers on base 20
            string mayaN = "";
            if(number > numberToMaya.size() - 1)
            {
                long digit = number;
                int maxN = intlog(20, number);
                cerr << maxN << endl;
                for(int i = maxN; i > -1; i--)
                {
                    if(i > 0)
                    {
                        int poww = pow(20, i);
                        digit = number / poww;
                        //cerr << "Number "<< number << " = 20^" << i << " * " << digit << endl;
                        number = number % poww;
                    }
                    else
                    {
                        digit = number;
                        //cerr << "Last one " << digit << endl;
                    }
                    
                    //cerr << "search for " << digit << endl;
                    map<int,string>::iterator it = numberToMaya.find(digit);
                    if( it != numberToMaya.end())
                    {
                        mayaN += it->second;
                    }
                    else
                    {
                        return "";
                    }
                }
            }
            else
            {
                map<int,string>::iterator it = numberToMaya.find(number);
                if( it != numberToMaya.end())
                {
                    mayaN += it->second;
                }
            }
            return mayaN;  
        }
        
        void printDictionary()
        {
            cerr << "Maya Dictionary " << endl << endl;
            for(map<string,int>::iterator it = mayaToNumber.begin(); it != mayaToNumber.end(); ++it)
            {
                string mNumber = it->first;
                for(int i = 0; i < mNumber.size(); ++i)
                {
                    if(i % m_h == 0)
                    {
                        cerr << endl;
                    }
                    cerr << mNumber[i];
                }
                
                cerr << " == " << it->second << endl;
            }
        }
};
 
int main()
{
    int L;
    int H;
    cin >> L >> H; cin.ignore();
    cerr << L << " " << H << endl;
    MayanDictionary* mD = new MayanDictionary(L,H);
    string totalDictionary = "";
    for (int i = 0; i < H; i++) {
        string numeral;
        cin >> numeral; cin.ignore();
        totalDictionary += numeral;
    }
    mD->addMayaDictionary(totalDictionary);
    //mD->printDictionary();
    
    int S1;
    cin >> S1; cin.ignore();
    string mfNumber;
    for (int i = 0; i < S1; i++) {
        string num1Line;
        cin >> num1Line; cin.ignore();
        //cerr << num1Line << endl;
        mfNumber += num1Line;
    }
    long long fNumber = mD->convertToNumber(mfNumber);
    
    //cerr << "Second number" << endl;
    int S2;
    cin >> S2; cin.ignore();
    string msNumber;
    for (int i = 0; i < S2; i++) {
        string num2Line;
        cin >> num2Line; cin.ignore();
        //cerr << num2Line << endl;
        msNumber += num2Line; 
    }
    
    long long sNumber = mD->convertToNumber(msNumber);
    
    string operation;
    cin >> operation; cin.ignore();
    
    long long result = -1;
    //cerr << fNumber << operation << sNumber << endl;
    switch(operation[0])
    {
        case '*':
            result = fNumber * sNumber;
            break;
        case '/':
            result = fNumber / sNumber;
            break;
        case '+':
            result = fNumber + sNumber;
            break;
        case '-':
            result = fNumber - sNumber;
            break;
    }
    //cerr << "Result: " << result << endl;
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    string mayaN = mD->convertToMaya(result);
    for(int i = 0; i < (mayaN.size() / H); i++)
    {
        cout << mayaN.substr(i*L, L) << endl;
    }
    
}