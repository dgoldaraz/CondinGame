/// Here at Teads we know that to maximize the impact of an advertisement, the message needs to spread far and quickly.
///  
/// You are given data to calculate viral potential, represented by a network of people ready to relay a message to more people.
/// We can assume this network contains no cyclic relation. 
/// For example, if person #1 has a relation with person #2 and if person #2 has a relation with person #3, then it is impossible for #3 to have a direct relation with #1.
///  
/// When an individual broadcasts a message, it is counted as a single step, meaning that the time it takes to broadcast the message is independant from the amount of people in direct relation with the individual. We will consider that this event will always take 1 hour.
///  
/// Here is an example with persons #1, #2, #3, #4, #5, #6, #7 and #8 linked like so:
///  
/// 							1
///								|
///								2
///								|
///								3
///								/ \
///							   4   7
///							  / \   |
///							  5  6  8
///  
/// Here, by choosing to start propagation of the message with person #1, 4 hours will be needed to share the message to the entire network:
///  
/// 
///  
/// 1.   #1 relays the message to #2
/// 2.   #2 then relays it to #3
/// 3.   #3 relays it to #4 and #7.
/// 4.   #4 relays it to #5 and #6, while #7 relays it to #8
///  
/// If we decide now to start the propagation with person #3, then only 2 hours are needed:
///  
/// 
///  
/// 1.   #3 relays the message to #2, #4 and #7
/// 2.   #2 relays it to #1 ; #4 relays it to #5 and #6 ; #7 relays it to #8
///  
/// In this exercice, your mission consists in finding the minimal amount of hours it would take for a message to propagate across the entire network given to you as input.
///  	Game Input
/// 
/// Input
/// Line 1: N the number of adjacency relations.
/// 
/// N next lines: an adjancency relation between two people, expressed as X (space) Y, meaning that X is adjacent to Y.
/// 
/// Output
/// The minimal amount of steps required to completely propagate the advertisement.
/// 
/// Contraints
/// 0 < N< 150000
/// 0 ≤ X,Y < 200000
/// 
/// Examples
/// 
/// Input
/// 7
/// 1 2
/// 2 3
/// 3 4
/// 3 7
/// 4 5
/// 4 6
/// 7 8
/// 
/// Output
/// 2
/// 
/// Input
/// 7
/// 1 2
/// 2 3
/// 2 4
/// 3 5
/// 3 6
/// 4 7
/// 4 8
/// 
/// Output
/// 2

// Solution Code by dgoldaraz:

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
class Node
{
    private:
        vector<Node*> m_conexions;
        int m_id;
        Node* m_parent;
    
    public:
    
    Node(int id)
    {
        m_id = id;
        m_parent = nullptr;
    }
    
    ~Node()
    {
       m_conexions.clear();
    }
    
    int getId()
    {
        return m_id;
    }
    
    Node* getParent()
    {
        return m_parent;
    }
    
    bool isLeaf()
    {
        /*
        if(m_parent)
        {
            return m_conexions.size() == 0;
        }
        else
        */
        {
            return m_conexions.size() <= 1;
        }
    }
    
    void removeMe()
    {
        for(int i = 0; i < m_conexions.size(); ++i)
        {
            m_conexions[i]->removeChild(this);
        }
        delete(this);
    }

    void removeChild( Node* child)
    {
        vector<Node*>::iterator it = find(m_conexions.begin(), m_conexions.end(), child);
        if(it != m_conexions.end())
        {
            m_conexions.erase(it);
        }
    }

    void addConexion(Node* child)
    {
        if(!isConnected(child))
        {
            //child->setParent(this);
            m_conexions.push_back(child);
        }
    }
    
    void setParent(Node* parent)
    {
        if(m_parent)
        {
            cerr << "MORE THAN ONE PARENT!!" << endl;
        }
        
        m_parent = parent;
    }
    
    bool isConnected(Node* c)
    {
        return find(m_conexions.begin(), m_conexions.end(), c) != m_conexions.end();
    }
    
    void printNode( bool showConexions = false)
    {
       
        cerr << "Node:" << m_id << "    ";
        if(m_parent)
        {
            cerr << "Parent Node: " << m_parent->getId() << endl; 
            cerr << "  ";
        }
        if(showConexions)
        {
            cerr <<endl<< " Conexions:" << endl;
            for(int i = 0; i < m_conexions.size(); ++i)
            {
                cerr << "  ";
                m_conexions[i]->printNode(false);
            }
        }
        cerr << endl;
    }
};
 
void printGraph(map<int,Node*>& graph, bool moreInfo = false, bool showConexions = false)
{
    for (std::map<int,Node*>::iterator it=graph.begin(); it!=graph.end(); ++it)
    {
        //cerr << it->first << " => "<< endl;
        Node* node = it->second;
        node->printNode(showConexions);
    }
}

Node* getNode(map<int,Node*>& graph,int key)
{
     map<int,Node*>::iterator it = graph.find(key);
     if( it != graph.end())
     {
         return it->second;
     }
     else
     {
         Node* newNode = new Node(key);
         graph[key] = newNode;
         return newNode;
     }
}

void insertConexion( map<int,Node*>& graph, int key, int value)
{
    Node* kNode = getNode(graph,key);
    Node* vNode = getNode(graph, value);
    
    kNode->addConexion(vNode);
    vNode->addConexion(kNode);
}


int main()
{
    int n; // the number of adjacency relations
    cin >> n; cin.ignore();
    map<int,Node*> graph;
    
    vector<vector<int>> conexionsToDo;
    for (int i = 0; i < n; i++) {
        int xi; // the ID of a person which is adjacent to yi
        int yi; // the ID of a person which is adjacent to xi
        cin >> xi >> yi; cin.ignore();
        insertConexion(graph, xi, yi);
    }
    
    int depth = 0;
    while( graph.size() > 1)
    {
        //get Leafs
        cerr << "Depth: "<< depth << " Nodes: " << graph.size() << endl; 
        vector<int> leafsKeys;
        for (map<int,Node*>::iterator it=graph.begin(); it!=graph.end(); ++it)
        {
            if(it->second->isLeaf())
            {
                
                leafsKeys.push_back(it->first);
            }
        }
        //remove them
        if(leafsKeys.size() == 0)
        {
            for (map<int,Node*>::iterator it=graph.begin(); it!=graph.end(); ++it)
            {
                cerr << "Id " << it->first << endl;
                it->second->printNode(true);
            }
            cerr << "Something goes wrong" << endl;
            break;
        }
        
        for( int i = 0; i < leafsKeys.size(); ++i)
        {
            //Get Node, remove it 
            map<int,Node*>::iterator leafIt = graph.find(leafsKeys[i]);
            if( leafIt != graph.end())
            {
                Node* leaf = leafIt->second;
                if(leaf)
                {
                    graph.erase(leafIt);
                    leaf->removeMe();
                }
            }
        }
        depth++;
    }
    // The minimal amount of steps required to completely propagate the advertisement
    //simulate(graph,hNode)
    cout << depth  << endl;
}