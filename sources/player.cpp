#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "player.hpp"
#include "game.hpp"

using namespace std;

Player::Player(std::string name){
    this->name = name;
    this->cardsWon = 0;
};

int Player::nextCard()
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
    cout << "Player : " << this->name << "won until now : " << this->cardsWon << " cards.";
};
