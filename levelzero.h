#ifndef ZERO_H
#define ZERO_H
#include <vector>
#include <string>
#include "level.h"

class LevelZero: public Level {
    int value;
    std::vector<std::string> order;
public:
    LevelZero(std::string name = "sequence.txt");
    void setRandom(bool) override;
    int getValue() override;
    std::shared_ptr<Block> createBlock() override;
};

#endif

