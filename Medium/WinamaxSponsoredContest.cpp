/// Before playing poker at Winamax, let's go back to basics with this simple card game: war!
/// 
/// Your goal is to write a program which finds out which player is the winner for a given card distribution of the "war" game.
///  	Rules
/// 
/// War is a card game played between two players. Each player gets a variable number of cards of the beginning of the game: that's the player's deck. Cards are placed face down on top of each deck.
///  
/// Step 1 : the fight
/// At each game round, in unison, each player reveals the top card of their deck – this is a "battle" – and the player with the higher card takes both the cards played and moves them to the bottom of their stack. The cards are ordered by value as follows, from weakest to strongest:
/// 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A.
///  
/// Step 2 : war
/// If the two cards played are of equal value, then there is a "war". First, both players place the three next cards of their pile face down. Then they go back to step 1 to decide who is going to win the war (several "wars" can be chained). As soon as a player wins a "war", the winner adds all the cards from the "war" to their deck.
///  
/// Special cases:
/// If a player runs out of cards during a "war" (when giving up the three cards or when doing the battle), then the game ends and both players are placed equally first.
/// The test cases provided in this puzzle are built in such a way that a game always ends (you do not have to deal with infinite games)
/// Each card is represented by its value followed by its suit: D, H, C, S. For example: 4H, 8C, AS.
/// 
/// When a player wins a battle, they put back the cards at the bottom of their deck in a precise order. First the cards from the first player, then the one from the second player (for a "war", all the cards from the first player then all the cards from the second player).
/// 
/// For example, if the card distribution is the following:
/// Player 1 : 10D 9S 8D KH 7D 5H 6S
/// Player 2 : 10H 7H 5C QC 2C 4H 6D
/// Then after one game turn, it will be:
/// Player 1 : 5H 6S 10D 9S 8D KH 7D 10H 7H 5C QC 2C
/// Player 2 : 4H 6D
///  
/// Victory Conditions
/// A player wins when the other player no longer has cards in their deck.
///  	Game Input
/// 
/// Input
/// Line 1: the number N of cards for player one.
/// 
/// N next lines: the cards of player one.
/// 
/// Next line: the number M of cards for player two.
/// 
/// M next lines: the cards of player two.
/// 
/// Output
/// If players are equally first: PAT
/// Otherwise, the player number (1 or 2) followed by the number of game rounds separated by a space character. A war or a succession of wars count as one game round.
/// Constraints
/// 0 < N, M < 1000
/// Example

/// Input
/// 3
/// AD
/// KC
/// QC
/// 3
/// KH
/// QS
/// JC

/// Output
/// 1 3

/// Solution Code by dgoldaraz:

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
struct Card
{
    string cardS;
    int value;
    
    Card(const Card& c)
    {
        cardS = c.cardS;
        value = c.value;
    }
    Card(string c)
    {
        cardS = c;
        
        //search for J,Q,K,A
        size_t found = cardS.find("J");
        if(found != string::npos)
        {
            value = 11;
            return;
        }
        
        found = cardS.find("Q");
        if(found != string::npos)
        {
            value = 12;
            return;
        }
        
        found = cardS.find("K");
        if(found != string::npos)
        {
            value = 13;
            return;
        }
        
        found = cardS.find("A");
        if(found != string::npos)
        {
            value = 14;
            return;
        }
        
        value = atoi(cardS.c_str());
    }
};
 
 
int main()
{
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    
    list<Card*> p1Cards;
    list<Card*> p2Cards;
    
    for (int i = 0; i < n; i++) {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
        
        Card* c = new Card(cardp1);
        p1Cards.push_back(c);  
    }
    cerr << endl;
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();
        
        Card* c =  new Card(cardp2);
        p2Cards.push_back(c);  
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    vector<Card*> cardsInGame;
    int gameIterations = 0;
    int winner = 0;
    
    Card* pl1CGame = nullptr;
    Card* pl2CGame = nullptr;
    while( winner == 0)
    {
       
        if( p1Cards.empty())
        {
            winner = 2;
            break;
        }
        if(p2Cards.empty())
        {
            winner = 1;
            break;
        }
        
        //Put cards in game
        pl1CGame = p1Cards.front();
        pl2CGame = p2Cards.front();
        //Add Cards to the deck
        p1Cards.pop_front();
        p2Cards.pop_front();
        int pl1Index = 0;
        if(cardsInGame.size() > 0)
        {
            //Add the cards in correct order
            pl1Index = cardsInGame.size() * 0.5f;
        }
        
        cardsInGame.insert(cardsInGame.begin() + pl1Index, pl1CGame);
        cardsInGame.push_back(pl2CGame);
         
        if(pl1CGame->value > pl2CGame->value)
        {
            //player 1 wins
            p1Cards.insert(p1Cards.end(), cardsInGame.begin(), cardsInGame.end());
            gameIterations++;
            cardsInGame.clear();
        }
        else if (pl1CGame->value < pl2CGame->value)
        {
            //player2 wins
            p2Cards.insert(p2Cards.end(), cardsInGame.begin(), cardsInGame.end());
            gameIterations++;
            cardsInGame.clear();
        }
        else
        {
            //Add 3 cards to the deck and then get the cards
            int pl1Index = 0;
            if(p1Cards.size() < 4 || p2Cards.size() < 4)
            {
                winner = 3;
                break;
            }
            if(cardsInGame.size() > 0)
            {
                //Add the cards in correct order
                pl1Index = cardsInGame.size() * 0.5f;
            }
            
            //Insert pl1 and pl2
            for(int d = 0; d < 3; d++)
            {
                Card* p1CToInsert = p1Cards.front();
                Card* p2CToInsert = p2Cards.front();
                cardsInGame.insert(cardsInGame.begin() + pl1Index + d, p1CToInsert);
                cardsInGame.push_back(p2CToInsert);
                p1Cards.pop_front();
                p2Cards.pop_front();
            }
        }
        
    }
    
    if(winner == 3)
    {
        //Draw
         cout << "PAT"<< endl;
    }
    else
    {
        cout << winner << " " << gameIterations << endl;
    }
}