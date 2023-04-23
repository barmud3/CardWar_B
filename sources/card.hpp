#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace ariel{}
using namespace ariel;


enum value {Ace=1 ,Two ,Three ,Four ,Five ,Six ,Seven ,Eight ,Nine ,Ten ,Jack ,Queen ,King };
enum shape {Diamond=1 ,Heart,Spade,Club};

class Card{
    private:
    value val;
    shape sha;
    public:
    //resource : https://stackoverflow.com/questions/11452920/how-to-cast-int-to-enum-in-c
    Card(int val , int sha){this->val = static_cast<value>(val);  this->sha = static_cast<shape>(sha);}
    value getVal(){return this->val;}
    void setVal(value val){this->val = val;}
    shape getSha(){return this->sha;}
    void setSha(shape sha){this->sha = sha;}
};

