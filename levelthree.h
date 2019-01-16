#ifndef THREE_H
#define THREE_H
#include "level.h"
#include <vector>
#include <string>

class LevelThree: public Level {
    int value;
    bool random;
    std::vector<std::string> order;
public:
    LevelThree(std::string name = "sequence.txt");
    int getValue() override;
    void setRandom(bool) override;
    std::shared_ptr<Block> createBlock() override;
};

#endif

