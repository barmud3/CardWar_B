#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "player.hpp"
#include "game.hpp"

using namespace std;

Player::Player(std::string name): 
name(name) , deck({}) , cardsWon(0) , numOfWons(0) , lastCard(Card()){
};

void Player::nextCard()
{
    if(!this->deck.empty())
    {
        this->lastCard = this->deck.back();
        this->deck.pop_back();
    }
};

int Player::stacksize()
{
    return this->deck.size();
};

int Player::cardesTaken()
{
    cout << "Player : " << this->name << " won until now : " << this->cardsWon << " cards." << endl;
    return this->cardsWon;
};

void Player::setDeck(vector<Card> deck)
{
    for (auto i=deck.begin(); i!=deck.end(); i++) 
    {
        this->deck.push_back(*i);
    }
}
