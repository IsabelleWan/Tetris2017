#ifndef _CELL_H
#define _CELL_H
#include "subject.h"
#include <string>
#include<memory> 
class Block;

class Cell: public Subject {
  int row;
  int col;
  std::shared_ptr<Block> BlockInCell;
  bool IamHint;
public:
  Cell(int row, int col);
  std::shared_ptr<Block> getBlock();
  void setState(std::shared_ptr<Block> b);
  void unsetState();
  int getRow();
  int getCol();
  std::string getState();
  bool getHint();
};
#endif

