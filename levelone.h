#ifndef ONE_H
#define ONE_H
#include "level.h"

class LevelOne: public Level {
    int value;
public:
    LevelOne();
    void setRandom(bool) override;
    int getValue() override;
    std::shared_ptr<Block> createBlock() override;
};

#endif

