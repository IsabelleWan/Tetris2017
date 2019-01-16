#ifndef LEVEL_H
#define LEVEL_H
#include <memory>
class Block;

class Level {
protected:
        int count = 0;
    public:
	virtual void setRandom(bool) = 0;
	virtual int getValue() = 0;
        virtual std::shared_ptr<Block> createBlock() = 0;
};

#endif
