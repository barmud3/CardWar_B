#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

Game::Game(Player& player1,Player& player2): p1(player1) , p2(player2){    
    this->gameOver = false;
    this->numOfRounds = 0;
    deckDistribution();
};

const string enumToString (Card c) 
{
   string card = "";
   switch (c.getVal()) 
   { 
        case Ace: case Two: case Three: case Four: case Five: 
        case Six: case Seven: case Eight: case Nine: case Ten:
        card += to_string(c.getVal()); break;
        case Jack:  card += "Jack"; break;
        case Queen: card += "Queen"; break;
        case King:  card += "King"; break;
   }
    card += " of ";
   switch (c.getSha())
   {
        case Diamond: card+= "Diamnod"; break;
        case Heart:   card+= "Heart"; break;
        case Spade:   card+= "Spade"; break;
        case Club:    card+= "Club"; break;
   }
   return card;
}

void Game::deckDistribution(){
    vector<Card> gameDeck;
    //create game deck
    for (int i = Ace; i <= King; i++)
    {
        gameDeck.push_back(Card(static_cast<values>(i) , Diamond));
        gameDeck.push_back(Card(static_cast<values>(i) , Heart));
        gameDeck.push_back(Card(static_cast<values>(i) , Spade));
        gameDeck.push_back(Card(static_cast<values>(i) , Club));
    }
    //shuffle game deck.
    gameDeck = this->shuffle(gameDeck);

    vector<Card> deckP1;
    vector<Card> deckP2;
    //distribute game deck
    for (size_t i = 0; i < 52; i+=2)
    {
        deckP1.push_back(gameDeck[i]);
        deckP2.push_back(gameDeck[i+1]);
    }

    this->p1.setDeck(deckP1);
    this->p2.setDeck(deckP2);
};

//resouce : "https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector"
//shuffle the given deck.
vector<Card> Game::shuffle(vector<Card> deck){
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(deck.begin(), deck.end(), rng);
    return deck;
}

void Game::playTurn()
{
    //playTurn func called but game arleady finish.
    if (this->gameOver == true)
    {
        throw std::invalid_argument("game arleady over , can't play another turn");
    }
    if (&(this->p1) == &(this->p2))
    {
        throw std::invalid_argument("a player can't play against himself");
    }
    //each player take card from his deck.
    this->p1.nextCard();
    this->p2.nextCard();
    Card p1Card = this->p1.getLastCard();
    Card p2Card = this->p2.getLastCard();
    string draw = "";

    int jackPot = 2; //each player put 1 card in the heap. 
    while (p1Card.getVal() == p2Card.getVal() && this->gameOver == false) //loop for draws.
    {
        draw  += "" + p1.getName() + " played: " + enumToString(p1Card) +". "+
        p2.getName() + " played " + enumToString(p2Card) +"." + " draw. "; 
        for (int i = 0; i < 2; i++)
        {
            //deck of one the players is empty.
            if (p1.stacksize() == 0 || p2.stacksize() == 0)
            {
                this->gameOver = true;
                break;
            }
            this->p1.nextCard();
            this->p2.nextCard();
            jackPot+=2; //each draw 1 cards from each player join the heap.
        } 
        p1Card = this->p1.getLastCard();
        p2Card = this->p2.getLastCard();
    }
    
    if (p1.stacksize() == 0 || p2.stacksize() == 0)
    {
        //if the tie breaker end in tie , jackpot been divide bettwen players.
        if(p1.stacksize() == 0 && p2.stacksize() == 0)
        {
            this->p1.addCardsWon(jackPot/2);
            this->p2.addCardsWon(jackPot/2);
            this->logGame.push_back(draw + p1.getName() + " played: " + enumToString(p1Card) +". "+
            p2.getName() + " played " + enumToString(p2Card) + " draw\n");
            this->gameOver = true;
            return;
        }
        else{
            this->gameOver = true;
        }
    }

    if (p1Card.getVal() == Ace) //player1 pull ace
    {
        if (p2Card.getVal() == Two) //player2 pull 2 , player2 won.
        {
            this->logGame.push_back(draw + p1.getName() + " played: " + enumToString(p1Card) +". "+
            p2.getName() + " played " + enumToString(p2Card) + " "+ p2.getName()+" win.\n");
            this->p2.addCardsWon(jackPot);
            this->p2.increaseNumWinning();
        }
        else //player 1 won
        {
            this->logGame.push_back(draw + p1.getName() + " played: " + enumToString(p1Card) +" ."+
            p2.getName() + " played " + enumToString(p2Card) + " "+ p1.getName()+" win.\n");
            this->p1.addCardsWon(jackPot);
            this->p1.increaseNumWinning();
        }
        this->numOfRounds++;
        return;
    }

    if (p2Card.getVal() == Ace) //player2 pull ace
    {
        if (p1Card.getVal() == Two) //player1 pull 2 , player1 won
        {
            this->logGame.push_back(draw + p1.getName() + " played: " + enumToString(p1Card) +" ."+
            p2.getName() + " played " + enumToString(p2Card) + " "+ p1.getName()+" win.\n");  
            this->p1.addCardsWon(jackPot);
            this->p1.increaseNumWinning();
        }
        else //player2 won
        {
            this->logGame.push_back(draw + p1.getName() + " played: " + enumToString(p1Card) +" ."+
            p2.getName() + " played " + enumToString(p2Card) + " "+ p1.getName()+" win.\n");
            this->p2.addCardsWon(jackPot);
            this->p2.increaseNumWinning();
        }
        this->numOfRounds++;
        return;
    }
    
    
    if (p1Card.getVal() > p2Card.getVal()) //player1 won 
    {
        this->logGame.push_back(draw + p1.getName() + " played: " + enumToString(p1Card) +". "+
        p2.getName() + " played " + enumToString(p2Card) + " "+ p1.getName()+" win.\n");
        this->p1.addCardsWon(jackPot);
        this->p1.increaseNumWinning();
    }
    else //player2 won
    {
        this->logGame.push_back(draw + p1.getName() + " played: " + enumToString(p1Card) +". "+
        p2.getName() + " played " + enumToString(p2Card) + " "+ p2.getName()+" win.\n");
        this->p2.addCardsWon(jackPot);
        this->p2.increaseNumWinning();
    }

    this->numOfRounds++;
};

void Game::printLastTurn()
{
    if (!this->logGame.empty())
    {
        cout << this->logGame.back();
    }
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
    if (this->gameOver == true)
    {
        if (this->p1.getCardsWon() > this->p2.getCardsWon())
        {
            cout << "The winner is : " <<  this->p1.getName() << endl;
        }
        else if (this->p1.getCardsWon() < this->p2.getCardsWon())
        {
            cout << "The winner is : " <<  this->p2.getName() << endl;
        }
        else
        {
            cout << "The winner is : none - game finish in draw" << endl;
        }
    }
    else
    {
        cout << "The game isn't over yet." << endl;
    }
    
    
}

void Game::printLog()
{
    int round = 1;
    for (auto i = logGame.begin(); i != logGame.end(); ++i)
    {
        cout << "Round num [" << round << "] stats: " << *i << endl;
        round++;
    }
}

void Game::printStats()
{
    cout << "Stats Game : " << endl;
    this->printWiner();
    cout <<"num of rounds : " << to_string(this->numOfRounds) << endl; 
    cout << "Stats player " << this->p1.getName() << "[cards won : " << to_string(this->p1.getCardsWon()) << "], [num of wons : "<< to_string(this->p1.getNumOfWons()) << "], [num of lose : "<< to_string((this->numOfRounds - this->p1.getNumOfWons())) << "], [last card : " << enumToString(this->p1.getLastCard()) << "]"<< endl;
    cout << "Stats player " << this->p2.getName() << "[cards won : " << to_string(this->p2.getCardsWon()) << "], [num of wons : "<< to_string(this->p2.getNumOfWons()) << "], [num of lose : "<< to_string((this->numOfRounds - this->p2.getNumOfWons())) << "], [last card : " << enumToString(this->p2.getLastCard()) << "]" << endl;
}


