/// Your virus has caused a backdoor to open on the Skynet network enabling you to send new instructions in real time.
/// 
/// You decide to take action by stopping Skynet from communicating on its own internal network.
/// 
/// Skynet's network is divided into several smaller networks, in each sub-network is a Skynet agent tasked with transferring information by moving from node to node along links and accessing gateways leading to other sub-networks.
/// 
/// Your mission is to reprogram the virus so it will sever links in such a way that the Skynet Agent is unable to access another sub-network thus preventing information concerning the presence of our virus to reach Skynet's central hub.
///  	Rules
/// 
/// For each test you are given:
/// A map of the network.
/// The position of the exit gateways.
/// The starting position of the Skynet agent.
/// >>> Nodes can only be connected to up to a single gateway. <<<
/// 
/// Each game turn:
/// First off, you sever one of the given links in the network.
/// Then the Skynet agent moves from one Node to another accessible Node.
/// 
/// Skynet agent
/// 
/// Gateway
///  
/// Victory Conditions
/// The Skynet agent cannot reach an exit gateway
///  
/// Lose Conditions
/// The Skynet agent has reached a gateway
///  	Example
/// 
/// 4 4 1
/// 0 1
/// 0 2
/// 1 3
/// 2 3
/// 3
/// Initialization input
///  
/// Text representation of the network used in this example. There are 4 nodes, 4 links and 1 gateway. The next 4 lines describe the links. The last integer is the index of the exit node.
/// 
/// Turn 1
/// The Skynet agent starts at node 0 (SI = 0). Our virus cut the link between the nodes 1 and 3.
/// 
/// Turn 2
/// The Skynet agent moves to node 2 (SI = 2). Our virus cut the link between the nodes 2 and 3.
/// 
/// Turn 3
/// The Skynet agent has been cut off from the exit, you have won !
///  	Note
/// 
/// The tests provided are similar to the validation tests used to compute the final score but remain different.
///  	Game Input
/// 
/// The program must first read the initialization data from standard input. Then, within an infinite loop, read the data from the standard input related to the current state of the Skynet agent and provide to the standard output the next instruction.
/// Initialization input
/// Line 1: 3 integers N L E
/// - N, the total number of nodes in the level, including the gateways.
/// - L, the number of links in the level.
/// - E, the number of exit gateways in the level.
/// 
/// Next L lines: 2 integers per line (N1, N2), indicating a link between the nodes indexed N1 and N2 in the network.
/// 
/// Next E lines: 1 integer EI representing the index of a gateway node.
/// 
/// Input for one game turn
/// Line 1: 1 integer SI, which is the index of the node on which the Skynet agent is positioned this turn.
/// Output for one game turn
/// A single line comprised of two integers C1 and C2 separated by a space. C1 and C2 are the indices of the nodes you wish to sever the link between.
/// Constraints
/// 2 ≤ N ≤ 500
/// 1 ≤ L ≤ 1000
/// 1 ≤ E ≤ 20
/// 0 ≤ N1, N2 < N
/// 0 ≤ SI < N
/// 0 ≤ C1, C2 < N
/// Response time per turn ≤ 150ms

// Solution Code by dgoldaraz:
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

void insertConexion(map<int,vector<int>>& graph, int N1, int N2)
{
    //Get node from the graph and add the conexion
    map<int,vector<int>>::iterator it = graph.find(N1);
    if (it != graph.end())
    {
        it->second.push_back(N2);
    }
    it = graph.find(N2);
    if (it != graph.end())
    {
        it->second.push_back(N1);
    }
}

void printGraph(map<int,vector<int>>& graph)
{
    for (std::map<int,vector<int>>::iterator it=graph.begin(); it!=graph.end(); ++it)
    {
        cerr << it->first << " => ";
        vector<int> conexions = it->second;
        for(int i = 0; i < conexions.size(); ++i)
        {
            cerr << conexions[i] << ",";
        }
        cerr << endl;
    }
}

vector<int> getNodeConexions(map<int,vector<int>>& graph, int nId)
{
    map<int,vector<int>>::iterator it = graph.find(nId);
    if (it != graph.end())
    {
        return it->second;
    }
    vector<int> empty;
    
    return empty;   
}

void deleteConexion(map<int,vector<int>>::iterator& it, int node)
{
    for(int i = 0; i < it->second.size();i++)
    {
        vector<int>::iterator cIt = std::find(it->second.begin(), it->second.end(), node);
        if( cIt != it->second.end())
        {
            it->second.erase(cIt);
        }
    }
}

void breakConexion(map<int,vector<int>>& graph, int N1, int N2)
{
    //search through the conexions and delete it
    map<int,vector<int>>::iterator it = graph.find(N1);
    if (it != graph.end())
    {
       deleteConexion(it, N2);
    }
    it = graph.find(N2);
    if (it != graph.end())
    {
        deleteConexion(it, N1);
    }
}
    
int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();
    
    //cerr << "Nodes: " << N << " Links: " << L << " Exits: " << E << endl;
    
    map<int,vector<int>> graph;
    
    for(int node = 0; node < N; node++)
    {
        vector<int> conexions;
        graph[node] = conexions;
    }
    
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        //cerr << N1 << " links " << N2 << endl;

        insertConexion(graph, N1, N2);
    }
    
   // printGraph(graph);
    
    vector<int> gateways;
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        //cerr << "Exit: " << EI << endl;
        gateways.push_back(EI);
    }
    // game loop
    while (1) 
    {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
        cerr << "Enemy on " << SI << endl;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        string answer;
        // First, get the node of the Skynet and check if the gateway is connected to it.
        //If that's happening, cut that conexion
        
        bool conexionBroken = false;
        vector<int> conexions = getNodeConexions(graph, SI);
        for(int i = 0; i < gateways.size() & !conexionBroken; ++i)
        {
            if(find(conexions.begin(), conexions.end(), gateways[i]) != conexions.end())
            {
                conexionBroken = true;
                cerr<<"Cut Skynet/Gateway"<< endl;
                //there is a conexion between the Skynet and the gateway, cut it!
                answer += to_string(SI);
                answer += " ";
                answer += to_string(gateways[i]);
                breakConexion(graph,SI,gateways[i]);
            }
        }
        
        if(!conexionBroken)
        {
           //get the first gateway with conexions and break it
           for(int i = 0; i < gateways.size() && !conexionBroken; i++)
           {
               conexions = getNodeConexions(graph, gateways[i]);
               if(conexions.size() > 0 )
               {
                    conexionBroken = true;
                    int C = conexions[0];
                    cerr<<"Cut Gateways"<< endl;
                    //Get the first conexion and break it
                    answer += to_string(gateways[i]);
                    answer += " ";
                    answer += to_string(C);
                    breakConexion(graph,gateways[i], C);
               }
           }
           
        }
        //string answer = stream.str();
        // Example: 0 1 are the indices of the nodes you wish to sever the link between
        cout << answer  << endl;
    }
}
