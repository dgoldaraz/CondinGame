/// By joining the iDroid smartphone development team, you have been given the responsibility of developing the contact manager. Obviously, what you were not told is that there are strong technical constraints for iDroid: the system doesn’t have much memory and the processor is as fast as a Cyrix from the 90s...
/// 
/// In the specifications, there are two points in particular that catch your attention:
/// 
/// 1. Intelligent Assistance for entering numbers
/// The numbers corresponding to the first digits entered will be displayed to the user almost instantly.
///  
/// 
/// 
/// 2. Number storage optimization
/// First digits which are common to the numbers should not be duplicated in the memory.
/// 
/// Fortunately, the specifications also have this little chart to guide you in the implementation:
///  
///   			- 5 - 7 - 8 - 4 - 4 - 0 Bill
/// 0-4 - 1 - 2 - 1 - 9 - 9 - 8 - 0 - 3 James
/// 	- 6 - 8 - 8 - 9 - 2 - 0 - 1 - 1 John
/// 	
/// 1 - 1 - 2 Urgences
///   - 5 S.A.M.U.
/// 
/// Fig 1. Structure of data to stock phone numbers on iDroid
/// 
/// Your task is to write a program that displays the number of items (which are numbers) required to store a list of telephone numbers with the structure presented above.
///  	Game Input
/// 
/// Input
/// Line 1: The number N of telephone numbers.
/// 
/// N following lines: Each line contains a phone number, with a maximum length L. Telephone numbers consist of only the digits 0 to 9 included, without any spaces.
/// 
/// Output
/// The number of elements (referencing a number) stored in the structure.

/// Constraints
/// 0 ≤ N ≤ 10000
/// 2 ≤ L ≤ 20

/// Examples

/// Input
/// 1
/// 0467123456
/// Output
/// 10

/// Input
/// 2
/// 0123456789
/// 1123456789
/// Output
/// 20

/// Input
/// 2
/// 0123456789
/// 0123

/// Output
/// 10

/// Input
/// 5
/// 0412578440
/// 0412199803
/// 0468892011
/// 112
/// 15

/// Output
/// 28

// Solution Code by dgoldaraz:

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
 
class Node
{
    private:
        string m_number;
        Node* m_parent;
        vector<Node*> m_children;
        int m_totalSize;
        
    public:
        Node(string number)
        {
            m_number = number;
            m_children.clear();
            m_totalSize = number.size();
        }
        ~Node()
        {
            m_children.clear();
        }
        
        void setParent(Node* p)
        {
            m_parent = p;
        }
        
        Node* addChild(string c)
        {
            Node* n = new Node(c);
            n->setParent(this);
            m_children.push_back(n);
            return n;
        }
        
        void addChildNode(Node* n)
        {
            n->setParent(this);
            m_children.push_back(n);
        }
        
        int getTotalChildrenNumber()
        {
            return m_totalSize;
        }
        
        void addToTotalSize(int i)
        {
            m_totalSize += i;
        }
        
        int updateGraph(string newN)
        {
            //This functions check wich numbers are equal and try to search in childs if not, create a new child
            int diffCharacter = -1;
            cerr << "Comparing " << m_number << " whith " << newN << endl;
            for(int i = 0; i < m_number.size(); i++)
            {
                //Search for a character different
                if(newN[i] != m_number[i])
                {
                    //Found, 
                    diffCharacter = i;
                    break;
                }
            }
            
            if(diffCharacter != -1)
            {
                 //Change the parent string
                 string oldChild = m_number.substr(diffCharacter);
                 string newChild = newN.substr(diffCharacter);
                 
                 m_number = m_number.substr(0, diffCharacter);
                 
                 //Create two childs
                 Node* reNode = new Node(oldChild);
                 for(int k = 0; k < m_children.size(); ++k)
                 {      
                    reNode->addChildNode(m_children[k]);
                    reNode->addToTotalSize(m_children[k]->getTotalChildrenNumber());
                 }
                 m_children.clear();
                 
                 m_children.push_back(reNode);
                 addChild(newChild);
                 
                 m_totalSize += newChild.size();
                 cerr << m_number << " -o " << oldChild << " -n " << newChild << endl;
                 return newChild.size();
            }
            else if(newN.size() > m_number.size())
            {
                string newC = newN.substr(m_number.size());
                cerr << "Search in childs " << newC << endl;
                for(int j = 0; j < m_children.size(); ++j)
                {
                    if(m_children[j]->getId() == newC[0])
                    {
                        //update the child
                        cerr << "Continue on children "<< m_children[j]->getId() << endl;
                        int newAmount = m_children[j]->updateGraph(newC);
                        m_totalSize += newAmount;
                        return  newAmount;
                    }
                }
                
                addChild(newC);
                m_totalSize += newC.size();
                return newC.size();
            }
        }
        
        char getId()
        {
            return m_number[0];
        }
        
        void printNodeWithChild(int j = 1)
        {
            cerr << m_number<<" - " <<  m_totalSize << endl;
            for(int i = 0; i < m_children.size(); ++i)
            {
                for(int k = 0; k < j; k++)
                {
                    cerr << "  ";
                }
                m_children[i]->printNodeWithChild(j+1);
            }
        }
};


Node* getNode(map<char, Node*> graph, char key)
{
    map<char,Node*>::iterator it = graph.find(key);
    
    if(it != graph.end())
    {
        return it->second;
    }
    
    return nullptr;
}


int main()
{
    int N;
    cin >> N; cin.ignore();
    
    int count = 0;
    
    //map<string, string> graph;
    map<char, Node*> graph;
    
    for (int i = 0; i < N; i++) {
        string telephone;
        cin >> telephone; cin.ignore();
        cerr << telephone << endl;
        char newNumber = telephone[0];
        Node* gNode = getNode(graph, newNumber);
        if(gNode == nullptr)
        {
            //insert a new node
            Node* newNode = new Node(telephone);
            graph[newNumber] = newNode;
        }
        else
        {
            //add integers
            gNode->updateGraph(telephone);
        }
    }

    for(map<char,Node*>::iterator it = graph.begin(); it != graph.end(); ++it)
    {
        count += it->second->getTotalChildrenNumber();
    }

    // The number of elements (referencing a number) stored in the structure.
    //45512
    cout <<  count << endl;
}
