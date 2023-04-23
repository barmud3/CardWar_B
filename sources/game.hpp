#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Game{
    
    private:
    Player& p1;
    Player& p2;
    std::string winner;
    bool gameOver;
    vector<Card> deck;
    vector<std::string> logGame;
    public:
    Game(Player& p1 , Player& p2);
    vector<Card> createDeck();
    void playTurn();
    void printLastTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
};
