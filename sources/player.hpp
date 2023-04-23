#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Player
{
    private:
    string name;
    std::vector<Card> deck;
    int cardsWon;
    Card lastCard;
    public:
    Player(std::string name);
    int nextCard();
    int stacksize();
    int cardesTaken();
    vector<Card> getDeck(){return this->deck;}
    vector<Card> setDeck(vector<Card> deck){this->deck = deck;}
    Card getLastCard(){return this->lastCard;}
    void setLastCard(Card c){this->lastCard = c;}
    string getName(){return this->name;}
    int getCardsWon(){return this->cardsWon;}
    void addCardsWon(int add){this->cardsWon+add;}
};