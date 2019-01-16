#ifndef FOUR_H
#define FOUR_H
#include "level.h"
#include <vector>
#include <string>

class LevelFour : public Level {
	int value;
	bool random;
	std::vector<std::string> order;
public:
	LevelFour(std::string name = "sequence.txt");
	int getValue() override;
	void setRandom(bool) override;
	std::shared_ptr<Block> createBlock() override;
};

#endif


