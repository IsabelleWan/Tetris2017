#ifndef TWO_H
#define TWO_H
#include "level.h"

class LevelTwo: public Level {
    int value;
public:
    LevelTwo();
    void setRandom(bool) override;
    int getValue() override;
    std::shared_ptr<Block> createBlock() override;
};

#endif

