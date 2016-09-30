/// The saying "Dwarfs standing on the shoulders of giants" refers to the importance of being able to build upon the work of our predecessors.
///  
/// When we read texts, we often only get a small glance of this dependence: this person influenced that person. Thereafter, we learn that the second person, in turn influenced a third and so on. In this exercise we’re interested in the chain of influence and more precisely in finding the longest possible chain.​
///  	Rules
/// 
/// We choose to represent each person by a distinct integer. If person #1 has influenced persons #2 and #3 and person #3 has influenced #4 then there is a succession of thoughts between #1, #3 and #4. In this case, it’s the longest succession and the expected result will be 3, since it involves 3 people.
/// 
/// 
///  
/// If we were to complete this example when we learn that person #2 also influenced persons #4 and #5, then the longest succession will still have a length of 3, but there will now be several of them.
/// 
/// 
///  
/// If we now add that person #10 influenced person #11, the result remains 3. However, as soon as we learn that #10 also influenced #1 and #3, then the result becomes 4, since there is now a succession involving 4 people, which is #10, #1, #2, #5. 
/// 
///  
/// Note: It takes time for a thought to influence others. So, we will suppose that it is not possible to have a mutual influence between people, i.e. If A influences B (even indirectly through other people), then B will not influence A (even indirectly). Also, you can not influence yourself.
/// 
///  	Game Input
/// 
/// Input
/// 
/// Line 1: The number N of relationships of influence.
/// 
/// N following lines: a relationship of influence between two people in the form of X (whitespace) Y, which indicates that X influences Y. The relationships of influence are listed in any order.
/// 
/// Output
/// The number of people involved in the longest succession of influences.
/// 
/// Constraints
/// 0 < N < 10000
/// 0 < X, Y < 10000
/// 
/// Examples
/// 
/// Input
/// 3
/// 1 2
/// 1 3
/// 3 4
/// 
/// Output
/// 3
/// 
/// Input
/// 8
/// 1 2
/// 1 3
/// 3 4
/// 2 4
/// 2 5
/// 10 11
/// 10 1
/// 10 3
/// 
/// Output
/// 4
/// 
/// Input
/// 4
/// 2 3
/// 8 9
/// 1 2
/// 6 3
/// 
/// Output
/// 3

//Solution Code by dgoldaraz:

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 //Class to handle Nodes
class Node
{
    private:
        int m_id;
        int m_influencers;
        vector<Node*> m_parents;
        
    public:
    
        Node(int id)
        {
            m_id = id;
            m_influencers = 0;
        }
        
        ~Node()
        {
            m_parents.clear();
        }
        
        void print()
        {
            cerr << "Node " << m_id << " Influencers " << m_influencers<< endl;
        }
        //Return the number of influencers
        int getInfluencer()
        {
            return m_influencers;
        }
        //Add a child to the Node, Update the influencers depending of the child (if they are bigger, the parent need to use the child influencers, and update the parents)
        void addChild(Node* child)
        {
            if(child->getInfluencer() + 1 > m_influencers)
            {
                m_influencers = child->getInfluencer() + 1;
                for(int i = 0; i < m_parents.size(); ++i)
                {
                    m_parents[i]->updateInfluencers(m_influencers);
                }
            }
            child->setParent(this);
        }
        
        void updateInfluencers(int cInfluencer)
        {
            if(cInfluencer + 1 > m_influencers)
            {
                m_influencers = cInfluencer + 1;
                for(int i = 0; i < m_parents.size(); ++i)
                {
                    m_parents[i]->updateInfluencers(m_influencers);
                }
            }
        }
        
        int getMaxInfluencers()
        {
            return m_influencers + 1;
        }
        
        void setParent(Node* p)
        {
           m_parents.push_back(p);
        }
};

// Search for the node with value 'key' in the map, if it can't find it, it will be created
Node* getNode(map<int, Node*>& nodeGraph, int key)
{
    map<int,Node*>::iterator it = nodeGraph.find(key);
    if(it != nodeGraph.end())
    {
        return it->second;
    }

    //Create node and store
    Node* n = new Node(key);
    nodeGraph[key] = n;
    
    return n;
}


int main()
{
    int n; // the number of relationships of influence
    cin >> n; cin.ignore();
    map<int, Node*> nodeGraph;
    
    for (int i = 0; i < n; i++) {
        int x; // a relationship of influence between two people (x influences y)
        int y;
        cin >> x >> y; cin.ignore();
        Node* xNode = getNode(nodeGraph,x);
        Node* yNode = getNode(nodeGraph,y);
        xNode->addChild(yNode);
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    int answer = 0;
    for(map<int, Node*>::iterator it = nodeGraph.begin(); it != nodeGraph.end(); ++it)
    {
        answer = max(answer,it->second->getMaxInfluencers());
    }
    // The number of people involved in the longest succession of influences
    cout << answer << endl;
}