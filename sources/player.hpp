#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "card.hpp"

using namespace std;

class Player
{
    private:
    std::string name;
    std::vector<Card> deck;
    int cardsWon;
    int numOfWons;
    Card lastCard;
    public:
    Player(std::string name);
    void nextCard();
    int stacksize();
    int cardesTaken();
    vector<Card> getDeck(){return this->deck;}
    void setDeck(vector<Card> deck);
    Card getLastCard(){return this->lastCard;}
    void setLastCard(Card card){this->lastCard = card;}
    string getName(){return this->name;}
    int getCardsWon() const{return this->cardsWon;}
    void addCardsWon(int add){this->cardsWon+=add;}
    int getNumOfWons() const{return this->numOfWons;}
    void increaseNumWinning(){this->numOfWons++;}
    
};

#endif
