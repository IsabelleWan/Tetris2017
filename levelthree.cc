#include "level.h"
#include "levelthree.h"
#include <vector>
#include <string>
#include <fstream>
#include "block.h"
#include <cstdlib>
using namespace std;

LevelThree::LevelThree(string name):value{3},random{true},order{}{
    ifstream f{name};
    string s;
    while (f >> s) {
	order.emplace_back(s);
    }
}

void LevelThree::setRandom(bool now) {random = now;}

int LevelThree::getValue() {return value;}

shared_ptr<Block> LevelThree::createBlock() {
    int rng = rand()%9;
    if (random == true) {
	if (rng < 1) {return make_shared<Block>("TBlock",3);}
	else if (rng < 2) {return make_shared<Block>("IBlock",3);}
	else if (rng < 3) {return make_shared<Block>("JBlock",3);}
	else if (rng < 4) {return make_shared<Block>("LBlock",3);}
	else if (rng < 5) {return make_shared<Block>("OBlock",3);}
	else if (rng < 7) {return make_shared<Block>("SBlock",3);}
	else {return make_shared<Block>("ZBlock",3);}
    } else {
	if (order.size() > 0) {
	    string s = order[0];
	    order.erase(order.begin());
	    if (s == "I") {return make_shared<Block>("IBlock",3);}
	    else if (s == "J") {return make_shared<Block>("JBlock",3);}
	    else if (s == "S") {return make_shared<Block>("SBlock",3);}
	    else if (s == "Z") {return make_shared<Block>("ZBlock",3);}
	    else if (s == "O") {return make_shared<Block>("OBlock",3);}
	    else if (s == "T") {return make_shared<Block>("TBlock",3);}
	    else if (s == "L") {return make_shared<Block>("LBlock",3);}
	    else {throw "WOW YOU WROTE YOUR OWN SEQUENCE WRONG?!!";}
	}
    }
}

