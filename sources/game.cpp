#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

Game::Game(Player& p1,Player& p2): p1(p1) , p2(p2){
    winner = "";
    this->gameOver =false;
    this->p1 = p1;
    this->p2 = p2;
    deck = createDeck();
};

vector<Card> Game::createDeck(){
    vector<Card> deck;
    for (int i = 1; i <= 13; i++)
    {
            deck.push_back(Card(i,1));
            deck.push_back(Card(i,2));
            deck.push_back(Card(i,3));
            deck.push_back(Card(i,4));
    }
    shuffle(deck);
    vector<Card> dackP1;
    vector<Card> dackP2;
    for (size_t i = 1; i <= 52; i+2)
    {
        dackP1.push_back(deck[i]);
        dackP2.push_back(deck[i+1]);
    }
    this->p1.setDeck(dackP1);
    this->p2.setDeck(dackP2);
    //cout<<to_string(dackP1.size());
};

//resouce : "https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector"
void shuffle(vector<Card> dack){
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(dack), std::end(dack), rng);
}

void Game::playTurn()
{
    if (this->gameOver == true)
    {
        return;
    }
    this->p1.nextCard();
    this->p2.nextCard();
    Card p1Card = this->p1.getLastCard();
    Card p2Card = this->p2.getLastCard();
    int cardsInHeap = 2; //each player put 1 card in the heap.
    while (p1Card.getVal() == p2Card.getVal() && this->gameOver == false) //loop for draws.
    {
        this->logGame.push_back("" + p1.getName() + "played: " + to_string(p1Card.getVal()) + "Of" + to_string(p1Card.getSha()) +"."+
        p2.getName() + "played " + to_string(p2Card.getVal()) + "of " + to_string(p2Card.getSha())+"." + " draw");
        for (int i = 0; i < 2; i++)
        {
            if (p1.getDeck().empty() || p2.getDeck().empty())
            {
                this->gameOver = true;
                break;
            }
            cardsInHeap+=2; //each draw 1 cards from each player join the heap.
            this->p1.nextCard();
            this->p2.nextCard();
        } 
        p1Card = this->p1.getLastCard();
        p2Card = this->p2.getLastCard();
    }

    if (p1Card.getVal() == 1) //player1 pull ace
    {
        if (p2Card.getVal() == 2) //player2 won
        {
            this->logGame.push_back("" + p1.getName() + "played: " + to_string(p1Card.getVal()) + "Of" + to_string(p1Card.getSha()) +"."+
            p2.getName() + "played " + to_string(p2Card.getVal()) + "of " + to_string(p2Card.getSha())+ " "+ p2.getName()+" win.");
            this->p2.addCardsWon(cardsInHeap);
        }
        else //player 1 won
        {
            this->logGame.push_back("" + p1.getName() + "played: " + to_string(p1Card.getVal()) + "Of" + to_string(p1Card.getSha()) +"."+
            p2.getName() + "played " + to_string(p2Card.getVal()) + "of " + to_string(p2Card.getSha())+ " "+ p1.getName()+" win.");
            this->p1.addCardsWon(cardsInHeap);
        }
        return;
    }

    if (p2Card.getVal() == 1) //player2 pull ace
    {
        if (p1Card.getVal() == 2) //player1 won
        {
            this->logGame.push_back("" + p1.getName() + "played: " + to_string(p1Card.getVal()) + "Of" + to_string(p1Card.getSha()) +"."+
            p2.getName() + "played " + to_string(p2Card.getVal()) + "of " + to_string(p2Card.getSha())+ " "+ p1.getName()+" win.");  
            this->p1.addCardsWon(cardsInHeap);
        }
        else //player2 won
        {
            this->logGame.push_back("" + p1.getName() + "played: " + to_string(p1Card.getVal()) + "Of" + to_string(p1Card.getSha()) +"."+
            p2.getName() + "played " + to_string(p2Card.getVal()) + "of " + to_string(p2Card.getSha())+ " "+ p1.getName()+" win.");
            this->p2.addCardsWon(cardsInHeap);
        }
        return;
    }
    
    
    if (p1Card.getVal() > p2Card.getVal()) //player1 won 
    {
        this->logGame.push_back("" + p1.getName() + "played: " + to_string(p1Card.getVal()) + "Of" + to_string(p1Card.getSha()) +"."+
        p2.getName() + "played " + to_string(p2Card.getVal()) + "of " + to_string(p2Card.getSha())+ " "+ p1.getName()+" win.");
        this->p1.addCardsWon(cardsInHeap);
    }
    else //player2 won
    {
        this->logGame.push_back("" + p1.getName() + "played: " + to_string(p1Card.getVal()) + "Of" + to_string(p1Card.getSha()) +"."+
        p2.getName() + "played " + to_string(p2Card.getVal()) + "of " + to_string(p2Card.getSha())+ " "+ p2.getName()+" win.");
        this->p2.addCardsWon(cardsInHeap);
    }
};

void Game::printLastTurn()
{
    std::cout << this->logGame.back();
    this->logGame.pop_back();
};

void Game::playAll()
{
    while(this->gameOver == false)
    {
       this->playTurn();
    } 
}

void Game::printWiner()
{
    cout << this->winner;
}

void Game::printLog()
{
    while(!this->logGame.empty())
    {
        cout << logGame.back();
        logGame.pop_back();
    }
}

void Game::printStats()
{
    cout << "Stats player " << this->p1.getName() << "cards won : " << to_string(this->p1.getCardsWon()) << "last card : " << to_string(this->p1.getLastCard().getVal()) << " " << to_string(this->p1.getLastCard().getVal()) << endl;
    cout << "Stats player " << this->p2.getName() << "cards won : " << to_string(this->p2.getCardsWon()) << "last card : " << to_string(this->p2.getLastCard().getVal()) << " " << to_string(this->p2.getLastCard().getVal()) << endl;
}


