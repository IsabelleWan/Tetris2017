#include<iostream>
#include "levelzero.h"
#include "block.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

LevelZero::LevelZero(string name):value{0},order{}{
    ifstream f{name};
    string s;
    while (f >> s) {
	order.emplace_back(s);
    }
}

int LevelZero::getValue(){return value;}

void LevelZero::setRandom(bool now){}

shared_ptr<Block> LevelZero::createBlock() {
//out <<"creating Block" <<endl;
    if (order.size() > 0) {
	string s = order[0];
        order.erase(order.begin());
	if (s == "I") {
//cout <<"creating I" <<endl;
return make_shared<Block>("IBlock",0);}
	else if (s == "L") {return make_shared<Block>("LBlock",0);}
	else if (s == "J") {return make_shared<Block>("JBlock",0);}
	else if (s == "S") {return make_shared<Block>("SBlock",0);}
	else if (s == "Z") {return make_shared<Block>("ZBlock",0);}
	else if (s == "O") {return make_shared<Block>("OBlock",0);}
	else if (s == "T") {return make_shared<Block>("TBlock",0);}
        else {throw "WOW YOU WROTE YOUR OWN SEQUENCE WRONG?!!!";}	
    }
//cout<< "end of creating" <<endl;

}
