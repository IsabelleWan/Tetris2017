#include "leveltwo.h"
#include "level.h"
#include <cstdlib>
#include "block.h"
#include <string>
using namespace std;

LevelTwo::LevelTwo():value{2}{}

int LevelTwo::getValue(){return value;}

void LevelTwo::setRandom(bool now){}

shared_ptr<Block> LevelTwo::createBlock() {
	int rng = rand()%7;
    if (rng < 1) {
	auto toReturn = make_shared<Block>("TBlock", 2);
        return toReturn;
	}
    else if (rng < 2) {
        auto toReturn = make_shared<Block>("IBlock", 2);
        return toReturn;
	}
    else if (rng < 3) {
        auto toReturn = make_shared<Block>("JBlock", 2);
        return toReturn;
	}
    else if (rng < 4) {
        auto toReturn = make_shared<Block>("LBlock", 2);
        return toReturn;
	}
    else if (rng < 5) {
        auto toReturn = make_shared<Block>("OBlock", 2);
        return toReturn;
	}
    else if (rng < 6) {
        auto toReturn = make_shared<Block>("SBlock", 2);
        return toReturn;
	}
    else {
        auto toReturn = make_shared<Block>("ZBlock", 2);
        return toReturn;
	}
}

