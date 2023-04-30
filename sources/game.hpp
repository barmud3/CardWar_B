#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "card.hpp"
#include "player.hpp"
using namespace std;

class Game{
    
    private:
    Player& p1;
    Player& p2;
    int numOfRounds;
    bool gameOver;
    ///vector<Card> gameDeck;
    vector<std::string> logGame;
    public:
    Game(Player& player1 , Player& players2);
    void deckDistribution();
    vector<Card> shuffle(vector<Card> deck);
    void playTurn();
    void printLastTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
};

#endif