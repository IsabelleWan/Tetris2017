#include "levelone.h"
#include <cstdlib>
#include "block.h"
#include <string>
using namespace std;

LevelOne::LevelOne():value{1}{}

int LevelOne::getValue(){return value;}
 
void LevelOne::setRandom(bool now){}

shared_ptr<Block> LevelOne::createBlock() {
	int rng = rand()%12;
    if (rng < 2) {
	auto toReturn = make_shared<Block>("TBlock", 1);
        return toReturn;
	}
    else if (rng < 4) {
        auto toReturn = make_shared<Block>("IBlock", 1);
        return toReturn;
	}
    else if (rng < 6) {
        auto toReturn = make_shared<Block>("JBlock", 1);
        return toReturn;
	}
    else if (rng < 8) {
        auto toReturn = make_shared<Block>("LBlock", 1);
        return toReturn;
	}
    else if (rng < 10) {
        auto toReturn = make_shared<Block>("OBlock", 1);
        return toReturn;
	}
    else if (rng == 10) {
        auto toReturn = make_shared<Block>("SBlock", 1);
        return toReturn;
	}
    else {
        auto toReturn = make_shared<Block>("ZBlock", 1);
        return toReturn;
	}
}


