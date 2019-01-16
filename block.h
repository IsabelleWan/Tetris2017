#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
class Cell;

class Block {                                  // abstract class that manages seven types of blocks
    std::string name;                          // name of the Block(TBlock, ZBlock)
    int genLevel;                              // at which level is this block generated;
    int remain;                                // how many pieces of the block is on the board(4 means completely on board, 0 means not on board anymore)
    int dir;                                   // the direction of the block is the block with dir's value times of rotation.
    std::vector<Cell *> cells;                 // a vector of cell points to point at Cell's on the Board
public:
    int getRange(std::string getWhat);     //getWhat needs to be one of "xmin", "xmax", "ymin", "ymax"
    Cell *getCell(int i);                  // fetch the ith element in the Cell pointer vector 
    void setCell(int i, Cell *c);          // change the ith element in the Cell pointer vector to c
    int getRemain();                       // return the value of remain
    void setRemain(int i);                 // set the value of remain to i
    int getLevel();                        // return the value of the genLevel
    std::string getName();                 // return the name of the Block
    Block(std::string name, int genLevel);      // constructor
    int getDir();
    void setDir(bool cw);
};    



















#endif


