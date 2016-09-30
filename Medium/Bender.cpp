/// Bender is a depressed robot who heals his depression by partying and drinking alcohol. To save him from a life of debauchery, his creators have reprogrammed the control system with a more rudimentary intelligence. Unfortunately, he has lost his sense of humor and his former friends have now rejected him.
/// 
/// Bender is now all alone and is wandering through the streets of Futurama with the intention of ending it all in a suicide booth.
/// 
/// To intercept him and save him from almost certain death, the authorities have given you a mission: write a program that will make it possible to foresee the path that Bender follows. To do so, you are given the logic for the new intelligence with which Bender has been programmed as well as a map of the city.
/// 
///  	Rules
/// 
/// The 9 rules of the new Bender system:
/// 
/// Bender starts from the place indicated by the @ symbol on the map and heads SOUTH.
/// Bender finishes his journey and dies when he reaches the suicide booth marked $.
/// Obstacles that Bender may encounter are represented by # or X.
/// When Bender encounters an obstacle, he changes direction using the following priorities: SOUTH, EAST, NORTH and WEST. So he first tries to go SOUTH, if he cannot, then he will go EAST, if he still cannot, then he will go NORTH, and finally if he still cannot, then he will go WEST.
/// Along the way, Bender may come across path modifiers that will instantaneously make him change direction. The S modifier will make him turn SOUTH from then on, E, to the EAST, N to the NORTH and W to the WEST.
/// The circuit inverters (I on map) produce a magnetic field which will reverse the direction priorities that Bender should choose when encountering an obstacle. Priorities will become WEST, NORTH, EAST, SOUTH. If Bender returns to an inverter I, then priorities are reset to their original state (SOUTH, EAST, NORTH, WEST).
/// Bender can also find a few beers along his path (B on the map) that will give him strength and put him in “Breaker” mode. Breaker mode allows Bender to destroy and automatically pass through the obstacles represented by the character X (only the obstacles X). When an obstacle is destroyed, it remains so permanently and Bender maintains his course of direction. If Bender is in Breaker mode and passes over a beer again, then he immediately goes out of Breaker mode. The beers remain in place after Bender has passed.
/// 2 teleporters T may be present in the city. If Bender passes over a teleporter, then he is automatically teleported to the position of the other teleporter and he retains his direction and Breaker mode properties.
/// Finally, the space characters are blank areas on the map (no special behavior other than those specified above).
/// Your program must display the sequence of moves taken by Bender according to the map provided as input.
/// 
/// The map is divided into lines (L) and columns (C). The contours of the map are always unbreakable # obstacles. The map always has a starting point @ and a suicide booth $.
/// 
/// If Bender cannot reach the suicide booth because he is indefinitely looping, then your program must only display LOOP.
///  	Example
/// 
/// Let the map below:
/// 
/// ######
/// #@E $#
/// # N  #
/// #X   #
/// ######
/// In this example, Bender will follow this sequence of moves:
/// 
/// SOUTH (initial direction)
/// EAST (because of the obstacle X)
/// NORTH (change of direction caused by N)
/// EAST (change of direction caused by E)
/// EAST (current direction, until end point $)
///  	Game Input
/// 
/// Input
/// Line 1: the number of lines L and columns C on the map, separated by a space.
/// 
/// The following L lines: a line of the length C representing a line on the map. A line can contain the characters #, X, @, $, S, E, N, W, B, I, T and space character.
/// 
/// Output
/// If Bender can reach $, then display the sequence of moves he has taken. One move per line: SOUTH for the South, EAST for the East, NORTH for the North and WEST for the west.
/// If Bender cannot reach $, then only display LOOP.
/// Constraints
/// 4 ≤ C ≤ 100
/// 4 ≤ L ≤ 100
/// 
/// Example
/// 
/// Input
/// 10 10
/// ##########
/// #        #
/// #  S   W #
/// #        #
/// #  $     #
/// #        #
/// #@       #
/// #        #
/// #E     N #
/// ##########
/// 
/// Output
/// SOUTH
/// SOUTH
/// EAST
/// EAST
/// EAST
/// EAST
/// EAST
/// EAST
/// NORTH
/// NORTH
/// NORTH
/// NORTH
/// NORTH
/// NORTH
/// WEST
/// WEST
/// WEST
/// WEST
/// SOUTH
/// SOUTH

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
 
class Game
{
    struct state
    {
        int x;
        int y;
        int times;
        bool iOn;
        bool bOn;
        char cDir;
        char nDir;
        
        state( int xx, int yy, bool isIOn, bool isBOn, char userCDir, char userNDir)
        {
            x = xx;
            y = yy;
            iOn = isIOn;
            bOn = isBOn;
            cDir = userCDir;
            nDir = userNDir;
            times = 1;
        }
        
        void addTimes()
        {
            times++;
        }
        
        bool isEqual(const state& s)
        {
            return s.x == x && s.y == y && s.iOn == iOn && s.bOn == bOn && s.cDir == cDir && s.nDir == nDir;
        }
        
    };
    
    enum grid_type { nothing, obstacle,goal, teleporter};
    private:
        vector<vector<char>> m_grid;
        int m_x;
        int m_y;
        char m_Dir;
        char m_newDir;
        bool m_InverterOn;
        bool m_BreakerOn;
        int m_height;
        int m_width;
        int m_endX;
        int m_endY;
        int m_t1X;
        int m_t1Y;
        int m_t2X;
        int m_t2Y;
        bool m_finish;
        bool m_loop;
        vector<state> m_changes;
        
    public:
        Game(int H, int W):
        m_x(0),m_y(0),
        m_endX(0), m_endY(0),
        m_t1X(-1), m_t1Y(-1),
        m_t2X(-1), m_t2Y(-1),
        m_height(H),m_width(W),
        m_Dir('S'),m_newDir(' '),
        m_InverterOn(false),
        m_BreakerOn(false),
        m_finish(false),
        m_loop(false)
        {
            // Set up sizes. (HEIGHT x WIDTH)
            m_grid.resize(H);
            for (int i = 0; i < H; ++i)
            {
                m_grid[i].resize(W);
            } 
        }
        
        ~Game()
        {
            for (int i = 0; i < m_height; ++i)
            {
                m_grid[i].clear();
            } 
            
            m_grid.clear();
            m_changes.clear();
        }
        
        //Add mapUnit
        
        void addLineToMap(int i, string line )
        {
             for(int j = 0; j < m_width; j++)
            {
                //char c = row[j];
                addToMap(i, j, line[j]);
            }
        }
        
        void addToMap(int i, int j, char c)
        {
            if(c == '@')
            {
                //Initial point
                m_x = i;
                m_y = j;
            }
            if(c == '$')
            {
                m_endX = i;
                m_endY = j;
            }
            if(c == 'T')
            {
                if(m_t1X == -1)
                {
                    m_t1X = i;
                    m_t1Y = j;
                }
                else
                {
                    m_t2X = i;
                    m_t2Y = j;
                }
            }
            
            m_grid[i][j] = c;
        }

        void printMap(bool showCPos = false)
        {
            for(int i = 0; i < m_height; ++i)
            {
                for(int j = 0; j < m_width; ++j)
                {
                    if(showCPos && i == m_x && j == m_y)
                    {
                        cerr << "P";
                    }
                    else
                    {
                        cerr << m_grid[i][j];
                    }
                }
                cerr << endl;
            }
        }
  
        void getNextPosition(int &i, int &j, char dir )
        {
            switch(dir)
            {
                case 'S':
                     i = m_x + 1;
                     j = m_y;
                break;
                case 'N':
                    i = m_x - 1;
                    j = m_y;
                break;
                case 'E':
                    j = m_y + 1;
                    i = m_x;
                break;
                case 'W':
                    j = m_y - 1;
                    i = m_x;
                break;
            }
        }
        
        string dirToString()
        {
            switch(m_Dir)
            {
                case 'S':
                    return "SOUTH";
                break;
                case 'N':
                    return "NORTH";
                break;
                case 'E':
                    return "EAST";
                break;
                case 'W':
                    return "WEST";
                break;
                default:
                    return "ERROR";
                break;
            }
        }
        grid_type readMap(int i, int j)
        {
            //This function read the map and return if there is an obstacle or the user can move
            //Also updates the current state of the game
            char p = m_grid[i][j];
            switch(p)
            {
                case '#':
                    return obstacle;
                    break;
                case '$':
                    return goal;
                    break;
                case 'X':
                {
                    //check if we are in breaker mode
                    if(m_BreakerOn)
                    {
                        //delete this obstacle
                        m_grid[i][j] = ' ';
                        return nothing;
                    }
                    else
                    {
                        return obstacle;
                    }
                    break;
                }
                case 'E':
                {
                    //Update my dir 
                    m_newDir = 'E';
                    addChange(m_x, m_y, m_InverterOn, m_BreakerOn, m_Dir, m_newDir);
                    return nothing;
                    break;
                }
                case 'S':
                {
                    m_newDir = 'S';
                    addChange(m_x, m_y, m_InverterOn, m_BreakerOn, m_Dir, m_newDir);
                    return nothing;
                    break;
                }
                case 'N':
                {
                    m_newDir = 'N';
                    addChange(m_x, m_y, m_InverterOn, m_BreakerOn, m_Dir, m_newDir);
                    return nothing;
                    break;
                }
                case 'W':
                {
                    m_newDir = 'W';
                    addChange(m_x, m_y, m_InverterOn, m_BreakerOn, m_Dir, m_newDir);
                    return nothing;
                    break;
                }
                case 'I':
                {
                    m_InverterOn = !m_InverterOn;
                    return nothing;
                    break;
                }
                case 'B':
                {
                    m_BreakerOn = !m_BreakerOn;
                    return nothing;
                    break;
                }
                case 'T':
                {
                    return teleporter;
                    break;
                }
                default:
                    return nothing;
                    break;
            }
            
        }
        
        char getNextDirection( char direction)
        {
            //Check the current dir and try to get the next one
            if(m_InverterOn)
            {
                switch(direction)
                {
                    case 'W':
                    {
                        return 'N';
                        break;
                    }
                    case 'N':
                    {
                        return 'E';
                        break;
                    }
                    case 'E':
                    {
                        return 'S';
                    }
                    case 'S':
                    {
                        // We can't move
                        return 'L';
                    }
                }
            }
            else
            {
                switch(direction)
                {
                    case 'S':
                    {
                        return 'E';
                        break;
                    }
                    case 'E':
                    {
                        return 'N';
                        break;
                    }
                    case 'N':
                    {
                        return 'W';
                    }
                    case 'W':
                    {
                        // We can't move
                        return 'L';
                    }
                }
            }
            
        }
        
        void dealWithObstacle()
        {
            //Check the inverter
            char tryDir = ' ';
            
            if(m_InverterOn)
            {
                tryDir = m_Dir != 'W' ? 'W': 'N';
            }
            else
            {
                tryDir = m_Dir != 'S' ? 'S': 'E';
            }
            while(tryDir != 'L')
            {
                int nextX,nextY;
                getNextPosition(nextX,nextY, tryDir);
                //cerr << "Obstacle try " << tryDir << "=" << nextX << "," << nextY << endl;
                grid_type next = readMap(nextX,  nextY);
                if(next != obstacle )
                {
                    addChange(m_x, m_y, m_InverterOn, m_BreakerOn, m_Dir, tryDir);
                    m_Dir = tryDir;
                    eval(next, nextX, nextY);
                    break;
                }
                else
                {
                    tryDir = getNextDirection(tryDir);
                }
            }
            
            if(tryDir == 'L')
            {
                m_loop = true;
            }
            
        }
        
        void eval(grid_type next, int nextX, int nextY)
        {
            switch(next)
            {
                case goal:
                {
                    m_finish = true;
                    break;
                }
                case nothing:
                {
                    m_x = nextX;
                    m_y = nextY;
                    break;
                }
                case teleporter:
                {
                    if(nextX == m_t1X )
                    {
                        //We are in teleporter 1 move to 2
                        m_x = m_t2X;
                        m_y = m_t2Y;
                    }
                    else
                    {
                         //We are in teleporter 2 move to 1
                        m_x = m_t1X;
                        m_y = m_t1Y;
                    }
                    break;
                }
                case obstacle:
                {
                    dealWithObstacle();
                    break;
                }
            }
        }
        void updateDir()
        {
            if(m_newDir != ' ')
            {
                m_Dir = m_newDir;
                m_newDir = ' ';
            }
        }
        //This function move the robot and return the direction chosen
        string move()
        {
            int nextX,nextY;
            getNextPosition(nextX,nextY, m_Dir);
            //cerr << nextX << "," << nextY << endl;
            grid_type next = readMap(nextX,  nextY);
            //nothing, obstacle,goal, teleporter
            eval(next, nextX, nextY);
            string dir = dirToString();
            updateDir();
            return dir;
        }
        
        void addChange(int xx, int yy, bool isIOn, bool isBOn, char userCDir, char userNDir)
        {
            state t(xx,yy,isIOn,isBOn,userCDir,userNDir);
            bool found = false;
            for(int i = 0; i < m_changes.size(); ++i)
            {
                if(m_changes[i].isEqual(t))
                {
                    m_changes[i].addTimes();
                    if(m_changes[i].times > 3)
                    {
                        m_loop = true;
                    }
                }
            }
            if(!found)
            {
                m_changes.push_back(t);
            }
        }
        string evaluateGame()
        {
            string chainOfActions = "";
            while(!m_finish)
            {
                string m = move();
                chainOfActions += m;
                chainOfActions += "\n";
                if(m_loop)
                {
                    chainOfActions = "LOOP";
                    break;
                }
            }
            
            return chainOfActions;
        }
};
 
int main()
{
    int L;
    int C;
    cin >> L >> C; cin.ignore();
    Game* myGame = new Game(L,C);
    for (int i = 0; i < L; i++) {
        string row;
        getline(cin, row);
        myGame->addLineToMap(i,row);
    }
    cerr << endl;
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << myGame->evaluateGame()<< endl;
}