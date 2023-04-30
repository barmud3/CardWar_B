#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace ariel{}
using namespace ariel;


enum values {Ace=1 ,Two ,Three ,Four ,Five ,Six ,Seven ,Eight ,Nine ,Ten ,Jack ,Queen ,King };
enum shape {Diamond=1 ,Heart ,Spade ,Club };

class Card{
    private:
    values val;
    shape sha;
    public:
    //resource : https://stackoverflow.com/questions/11452920/how-to-cast-int-to-enum-in-c
    //Card(int val , int sha){this->val = static_cast<values>(val);  this->sha = static_cast<shape>(sha);}
    Card(values val , shape sha):val(val) , sha(sha){}
    Card():val(Ace) , sha(Diamond){}
    values getVal(){return this->val;}
    shape getSha(){return this->sha;}
};

#endif