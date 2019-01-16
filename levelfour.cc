#include <iostream>
#include "level.h"
#include "levelfour.h"
#include <vector>
#include <string>
#include <fstream>
#include "block.h"
#include <cstdlib>
using namespace std;

LevelFour::LevelFour(string name) : value { 4 }, random{ true }, order{} {
	ifstream f{ name };
	string s;
	while (f >> s) {
		order.emplace_back(s);
	}
}

void LevelFour::setRandom(bool now) { random = now; }

int LevelFour::getValue() { return value; }

shared_ptr<Block> LevelFour::createBlock() {
	int rng = rand() % 9;
	if (random == true) {
		if (count == 4) { 
                   count = 0;
                   return make_shared<Block>("EBlock", 4); 
                }
		if (rng < 1) { ++count; 
                  return make_shared<Block>("TBlock", 4); }
		else if (rng < 2) { ++ count;
                  return make_shared<Block>("IBlock", 4); }
		else if (rng < 3) { ++count;
                  return make_shared<Block>("JBlock", 4); }
		else if (rng < 4) { ++count;
                  return make_shared<Block>("LBlock", 4); }
		else if (rng < 5) { ++count;
                  return make_shared<Block>("OBlock", 4); }
		else if (rng < 7) { ++count;
                  return make_shared<Block>("SBlock", 4); }
		else { ++count;
                  return make_shared<Block>("ZBlock", 4); }
	}
	else {
		if (order.size() > 0) {
			string s = order[0];
			order.erase(order.begin());
			if (s == "I") { ++count;
                           return make_shared<Block>("IBlock", 4); }
			else if (s == "J") { ++count;
                           return make_shared<Block>("JBlock", 4); }
			else if (s == "S") { ++count;
                           return make_shared<Block>("SBlock", 4); }
			else if (s == "Z") { ++count;
                           return make_shared<Block>("ZBlock", 4); }
			else if (s == "O") { ++count;
                           return make_shared<Block>("OBlock", 4); }
			else if (s == "T") { ++count;
                           return make_shared<Block>("TBlock", 4); }
			else if (s == "L") { ++count;
                           return make_shared<Block>("LBlock", 4); }
			if (count == 5) { 
                           count = 0;
                           return make_shared<Block>("EBlock", 4); 
                        }
			else { throw "WOW YOU WROTE YOUR OWN SEQUENCE WRONG?!!"; }
                        
		}
	}
}


