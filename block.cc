#include<iostream>
#include "block.h"
#include <vector>
#include <string>
#include "cell.h"
using namespace std;

Block::Block(string name, int genLevel): name{name}, genLevel{genLevel}, remain{4}, dir{0}, cells{}{
    for (int i=0; i<4; ++i) {
	cells.emplace_back(nullptr);
    }
}

 int Block::getRange(string getWhat) {
	         if (getWhat == "xmin") {
		                 int xmin = cells.at(0)->getCol();
		                 for (auto n : cells) {
			                         if (xmin > n->getCol()) xmin = n->getCol();
			
		}
		               return xmin;
		
	}
	       else if (getWhat == "xmax") {
		                 int xmax = cells.at(0)->getCol();
		                 for (auto n : cells) {
			                         if (xmax < n->getCol()) xmax = n->getCol();
			
		}
		               return xmax;
		
	}
	         else if (getWhat == "ymin") {
		                 int ymin = cells.at(0)->getRow();
		               for (auto n : cells) {
		                         if (ymin > n->getRow()) ymin = n->getRow();
			
		}
		               return ymin;
		
	}
	         else {
                int ymax = cells.at(0)->getRow();
                 for (auto n : cells) {
                         if (ymax < n->getRow()) ymax = n->getRow();
		}
                return ymax;
	}
}

int Block::getLevel() {return genLevel;}

void Block::setRemain(int i) {remain = i;}

string Block::getName() {
return name;}

int Block::getRemain() {return remain;}

void Block::setCell(int i, Cell *c) {cells[i] = c;}

Cell *Block::getCell(int i) {return cells[i];}

int Block::getDir() {return dir;}

void Block::setDir(bool cw) {
    if (cw) {
      if (dir == 3) dir = 0;
      else ++dir;
    } else {
      if (dir == 0) dir = 3;
      else --dir;
    }
}


