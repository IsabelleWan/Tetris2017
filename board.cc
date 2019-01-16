#include "board.h"
#include "block.h"
#include <iostream>
#include <vector>
#include <string>
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "cell.h"
using namespace std;

Board::Board():theBoard{},curScore{0},hiScore{0},curLevel{nullptr},
       blocks{nullptr},td{make_shared<TextDisplay>()},curBlock{nullptr},nextBlock{nullptr},
       gd{make_shared<GraphicsDisplay>()}, posHint{0}, dirHint{0}, height{} {

          for (int i = 0; i < 11; ++i){
                height[i] = 0;
            }
 }

int Board::getHigh() {return hiScore;}

void Board::printHigh() {
gd->printcurScore(curScore);
gd->printhiScore(hiScore);
gd->printLevel(curLevel->getValue());}

void Board::setHigh(int hs) {hiScore = hs;}

void Board::removegraphics() {
    if (!(gd == nullptr)) {
        gd = nullptr;
    }
}

void Board::setObserver() {
    for (int r = 0; r < 18; ++r) {
	for (int c = 0; c < 11; ++c) {
	    theBoard[r][c].attach(gd);
	}
    }
}

void Board::unsetCurBlock() {
	for (int i = 0; i<4; ++i) {
		curBlock->getCell(i)->unsetState();
	}
}


//NEW : check if the set the block be can be done. Return 1 if true, 0 otherwise
bool Board::setCheck(shared_ptr<Block> b, int c, int r) {//check if the curBlock can be moved to position c, r
	string type = b->getName();
	int dir = b->getDir();

	if (type == "TBlock" && dir == 0) {
		if (theBoard[r - 1][c].getState() != "None" || theBoard[r - 1][c + 1].getState() != "None" ||
			theBoard[r - 1][c + 2].getState() != "None" || theBoard[r][c + 1].getState() != "None") {
			return 0;
		}
	}
	else if (type == "SBlock" && dir == 0) {
		if (theBoard[r + 1][c + 1].getState() != "None" || theBoard[r + 1][c + 2].getState() != "None" ||
			theBoard[r][c].getState() != "None" || theBoard[r][c + 1].getState() != "None") {
			return 0;
		}
	}
	else if (type == "ZBlock" && dir == 0) {
		if (theBoard[r - 1][c].getState() != "None" || theBoard[r - 1][c + 1].getState() != "None" ||
			theBoard[r][c + 1].getState() != "None" || theBoard[r][c + 2].getState() != "None") {
			return 0;
		}
	}
	else if (type == "LBlock" && dir == 0) {
		if (theBoard[r - 1][c + 2].getState() != "None" || theBoard[r][c].getState() != "None" ||
			theBoard[r][c + 1].getState() != "None" || theBoard[r][c + 2].getState() != "None") {
			return 0;
		}
	}
	else if (type == "JBlock" && dir == 0) {
		if (theBoard[r - 1][c].getState() != "None" || theBoard[r][c].getState() != "None" ||
			theBoard[r][c + 1].getState() != "None" || theBoard[r][c + 2].getState() != "None") {
			return 0;
		}
	}
	else if (type == "IBlock" && dir == 0) {
		if (theBoard[r][c].getState() != "None" || theBoard[r][c + 1].getState() != "None" ||
			theBoard[r][c + 2].getState() != "None" || theBoard[r][c + 3].getState() != "None") {
			return 0;
		}
	}
	else if (type == "OBlock" && dir == 0) {
		if (theBoard[r - 1][c].getState() != "None" || theBoard[r - 1][c + 1].getState() != "None" ||
			theBoard[r][c].getState() != "None" || theBoard[r][c + 1].getState() != "None") {
			return 0;
		}
	}
	else if (type != "EBlock") { cout <<  "check: I didn't recongnize this block!"<< endl; }
	return 1;
}

//NEW returns 0 if the set failed, returns 1 if success
void Board::setCurBlock(shared_ptr<Block> b, int c, int r) {//Put the left bottom of the block b points at at position (c, r)
	string type = b->getName();
	int dir = b->getDir();
    if (type == "TBlock" && dir == 0) {
			theBoard[r - 1][c].setState(b);
			theBoard[r - 1][c + 1].setState(b);
			theBoard[r - 1][c + 2].setState(b);
			theBoard[r][c + 1].setState(b);
			Cell *c0 = &theBoard[r - 1][c];
			b->setCell(0, c0);
			Cell *c1 = &theBoard[r - 1][c + 1];
			b->setCell(1, c1);
			Cell *c2 = &theBoard[r - 1][c + 2];
			b->setCell(2, c2);
			Cell *c3 = &theBoard[r][c + 1];
			b->setCell(3, c3);
	}
	else if (type == "SBlock" && dir == 0) {
			theBoard[r - 1][c + 1].setState(b);
			theBoard[r - 1][c + 2].setState(b);
			theBoard[r][c].setState(b);
			theBoard[r][c + 1].setState(b);
			Cell *c0 = &theBoard[r - 1][c + 1];
			b->setCell(0, c0);
			Cell *c1 = &theBoard[r - 1][c + 2];
			b->setCell(1, c1);
			Cell *c2 = &theBoard[r][c];
			b->setCell(2, c2);
			Cell *c3 = &theBoard[r][c + 1];
			b->setCell(3, c3);
	}
	else if (type == "ZBlock" && dir == 0) {
			theBoard[r -1][c].setState(b);
			theBoard[r -1][c + 1].setState(b);
			theBoard[r][c + 1].setState(b);
			theBoard[r][c + 2].setState(b);
			Cell *c0 = &theBoard[ r - 1][c];
			b->setCell(0, c0);
			Cell *c1 = &theBoard[r - 1][c + 1];
			b->setCell(1, c1);
			Cell *c2 = &theBoard[r][c + 1];
			b->setCell(2, c2);
			Cell *c3 = &theBoard[r][c + 2];
			b->setCell(3, c3);
	}
	else if (type == "LBlock" && dir == 0) {
			theBoard[r - 1][c + 2].setState(b);
			theBoard[r][c].setState(b);
			theBoard[r][c + 1].setState(b);
			theBoard[r][c + 2].setState(b);
			Cell *c0 = &theBoard[r - 1][c + 2];
			b->setCell(0, c0);
			Cell *c1 = &theBoard[r][c];
			b->setCell(1, c1);
			Cell *c2 = &theBoard[r][c + 1];
			b ->setCell(2, c2);
			Cell *c3 = &theBoard[r][c + 2];
			b->setCell(3, c3);
	}
	else if (type == "JBlock" && dir == 0) {
			theBoard[r - 1][c].setState(b);
			theBoard[r][c].setState(b);
			theBoard[r][c + 1].setState(b);
			theBoard[r][c + 2].setState(b);
			Cell *c0 = &theBoard[r - 1][c];
			b->setCell(0, c0);
			Cell *c1 = &theBoard[r][c];
			b->setCell(1, c1);
			Cell *c2 = &theBoard[r][c + 1];
			b->setCell(2, c2);
			Cell *c3 = &theBoard[r][c + 2];
			b->setCell(3, c3);
	}
	else if (type == "IBlock" && dir == 0) {
			theBoard[r][c].setState(b);
			theBoard[r][c + 1].setState(b);
			theBoard[r][c + 2].setState(b);
			theBoard[r][c + 3].setState(b);
			Cell *c0 = &theBoard[r][c];
			b->setCell(0, c0);
			Cell *c1 = &theBoard[r][c + 1];
			b ->setCell(1, c1);
			Cell *c2 = &theBoard[r][c + 2];
			b->setCell(2, c2);
			Cell *c3 = &theBoard[r][c + 3];
			b ->setCell(3, c3);
	}
	else if (type == "OBlock" && dir == 0) {
			theBoard[r - 1][c].setState(b);
			theBoard[r - 1][c + 1].setState(b);
			theBoard[r][c].setState(b);
			theBoard[r][c + 1].setState(b);
			Cell *c0 = &theBoard[r - 1][c];
			b->setCell(0, c0);
			Cell *c1 = &theBoard[r - 1][c + 1];
			b ->setCell(1, c1);
			Cell *c2 = &theBoard[r][c];
			b->setCell(2, c2);
			Cell *c3 = &theBoard[r][c + 1];
			b->setCell(3, c3);
	}
	else if (type == "EBlock") {
		theBoard[r][c].setState(b);
		Cell *c0 = &theBoard[r][c];
		b->setCell(0, c0);
	}
	else {cout <<  "I didn't recongnize this block!"<< endl;}
}

// Put a new block on the board
void Board::puton() {
	string type = curBlock->getName();
  bool stop = false;
	if (type == "IBlock") {
		if (!setCheck(curBlock, 0, 3))  {
      throw 0;
      stop = true;
    }
    /*if (!(stop == true) && (!(gd == nullptr))) {
  gd->printcurScore(curScore);
  gd->printhiScore(hiScore);
  gd->printLevel(curLevel->getValue());
}*/
               setCurBlock(curBlock, 0, 3);
	}else if (type == "EBlock") {
          int whereTo;
          if (theBoard[3][5].getState() != "None") return;
          for(whereTo = 3; whereTo < 18; ++whereTo) {
              if (theBoard[whereTo][5].getState() != "None") break;
          }
          setCurBlock(curBlock, 5, whereTo - 1);
        }
	else {
		if (!setCheck(curBlock, 0, 4)) throw 0;
		setCurBlock(curBlock, 0, 4);
	}
}

void Board::init(int startLevel, string scriptName){
    // attach Cells to the Board
    for (int i=0; i<18; ++i) {
        vector<Cell> temp;
	for (int j=0; j<11; ++j) {
	    temp.emplace_back(Cell(i,j));
	}
	theBoard.emplace_back(temp);
    }
    //
    // now add TextDisplay to each Cell as observer
    for (int i=0; i<18; ++i) {
	for (int j=0; j<11; ++j) {
	    theBoard[i][j].attach(td);
	}
    }
	if (startLevel == 0) curLevel = make_shared<LevelZero>(scriptName);
	else if (startLevel == 1) curLevel = make_shared<LevelOne>();
	else if (startLevel == 2) curLevel = make_shared<LevelTwo>();
	else if (startLevel == 3) curLevel = make_shared<LevelThree>();
	else if (startLevel == 4) curLevel = make_shared<LevelFour>();
    // generate a block, put it at the top left position and set to current block
    // cout << "check4" << endl;
    // generate a block, put it at the top left position and set to current block
    curBlock = curLevel->createBlock();
      if (!(gd == nullptr)) {
	setObserver();
	gd->printcurScore(curScore);
	gd->printhiScore(hiScore);
	gd->printLevel(curLevel->getValue());
}
    // cout << "check5" << endl;
    puton();
    // cout << "check6" << endl;
    nextBlock = curLevel->createBlock();
        if (!(gd == nullptr)) {
    gd->printnext(nextBlock->getName());
  }
//cout <<"end init"<<endl;
}

int Board::left(){
    // create a temporary Block pointer to hold the current Block
    shared_ptr<Block> temp = curBlock->getCell(0)->getBlock();
    // for each cell pointer in the current block, set their Block pointers to nullptr
    for (int i=0; i<4; ++i) {
	curBlock->getCell(i)->unsetState();
    }
    // set an accumulator
    int count = 0;
    for (int i=0; i<4; ++i) {
        // first get the new potential position
	int nRow = curBlock->getCell(i)->getRow();
        int nCol = curBlock->getCell(i)->getCol()-1;
        // if nCol < 1 or occupied, increase the count by 1
	if (nCol < 0 || theBoard[nRow][nCol].getState()!="None") ++count;
    }
    if (count > 0) {//illegal move
	for (int i=0; i<4; ++i) {
	    curBlock->getCell(i)->setState(temp);
	}
        return 0;
    } else {
	for (int i=0; i<4; ++i) {
	    int nRow = curBlock->getCell(i)->getRow();
	    int nCol = curBlock->getCell(i)->getCol()-1;
	    Cell *tc = &theBoard[nRow][nCol];
	    curBlock->setCell(i,tc);
	    theBoard[nRow][nCol].setState(temp);
	}
        return 1;
    }
}

int Board::right(){
    // create a temporary Block pointer to hold the current Block
    shared_ptr<Block> temp = curBlock->getCell(0)->getBlock();
    // for each cell pointer in the current block, set their Block pointers to nullptr
    for (int i=0; i<4; ++i) {
	curBlock->getCell(i)->unsetState();
    }
    // set an accumulator
    int count = 0;
    for (int i=0; i<4; ++i) {
        // first get the new potential position
	int nRow = curBlock->getCell(i)->getRow();
        int nCol = curBlock->getCell(i)->getCol()+1;
        // if nCol < 1 or occupied, increase the count by 1
	if (nCol > 10 || theBoard[nRow][nCol].getState()!= "None") ++count;
    }
    if (count > 0) {//illegal move
	for (int i=0; i<4; ++i) {
	    curBlock->getCell(i)->setState(temp);
	}
        return 0;
    } else {
	for (int i=0; i<4; ++i) {
	    int nRow = curBlock->getCell(i)->getRow();
	    int nCol = curBlock->getCell(i)->getCol()+1;
	    Cell *tc = &theBoard[nRow][nCol];
	    curBlock->setCell(i,tc);
	    theBoard[nRow][nCol].setState(temp);
	}
       return 1;
    }
}

int Board::down(){
    // create a temporary Block pointer to hold the current Block
    shared_ptr<Block> temp = curBlock->getCell(0)->getBlock();
    // for each cell pointer in the current block, set their Block pointers to nullptr
    for (int i=0; i<4; ++i) {
	curBlock->getCell(i)->unsetState();
    }
    // set an accumulator
    int count = 0;
    for (int i=0; i<4; ++i) {
        // first get the new potential position
	int nRow = curBlock->getCell(i)->getRow()+1;
        int nCol = curBlock->getCell(i)->getCol();
        // if nCol < 1 or occupied, increase the count by 1
	if (nRow > 17 || theBoard[nRow][nCol].getState()!= "None") ++count;
    }
    if (count > 0) {
	for (int i=0; i<4; ++i) {
	    curBlock->getCell(i)->setState(temp);
	}
	return 0;
    } else {
	for (int i=0; i<4; ++i) {
	    int nRow = curBlock->getCell(i)->getRow()+1;
	    int nCol = curBlock->getCell(i)->getCol();
	    Cell *tc = &theBoard[nRow][nCol];
	    curBlock->setCell(i,tc);
	    theBoard[nRow][nCol].setState(temp);
	}
        return 1;
    }
}

void Board::IRotateDest(vector<vector <int>> *dest) {
	int xmin = curBlock->getRange("xmin");
	int xmax = curBlock->getRange("xmax");
	int ymin = curBlock->getRange("ymin");
	int ymax = curBlock->getRange("ymax");

	if (ymin == ymax) {//IBlock is horizontal
		for (int x = xmin; x <= xmax; ++x) {
			vector <int> temp{ xmin, ymin - x + xmin };
			dest->emplace_back(temp);
		}
	}
	else {//IBlock is vertical
		for (int y = ymin; y <= ymax; ++y) {
			vector <int> temp{ xmin + y - ymin , ymax };
			dest->emplace_back(temp);
		}
	}
}

void Board::counterRotateDest(vector<vector <int>> *dest) {//curBlock should not be OBlock and IBlock
//generate potential position for the Block with specific type on the board and put it in dest;
	int xmin = curBlock->getRange("xmin");
	int xmax = curBlock->getRange("xmax");
	int ymin = curBlock->getRange("ymin");
	int ymax = curBlock->getRange("ymax");
	if (ymax - ymin < xmax - xmin) {//the smallest rectangle of the block is 2 * 3
			for (int i = 0; i < 4; ++i) {
				int x = curBlock->getCell(i)->getCol();
				int y = curBlock->getCell(i)->getRow();
				if (x == xmin && y == ymin) {
					vector <int> temp{ xmin, ymin + 1 };
					dest->emplace_back(temp);
				}
				else if (x == xmin + 1 && y == ymin) {
					vector <int> temp{ xmin, ymin };
					dest->emplace_back(temp);
				}
				else if (x == xmax && y == ymin) {
					vector <int> temp{ xmin, ymin - 1 };
					dest->emplace_back(temp);
				}
				else if (x == xmin && y == ymax) {
					vector <int> temp{ xmin + 1, ymin + 1 };
					dest->emplace_back(temp);
				}
				else if (x == xmin + 1 && y == ymax) {
					vector <int> temp{ xmin + 1, ymin };
					dest->emplace_back(temp);
				}
				else {
					vector <int> temp{ xmin + 1, ymin - 1 };
					dest->emplace_back(temp);
				}
			}
		}
		else {//the smallest rectangle of the block is 3 * 2
			for (int i = 0; i < 4; ++i) {
				int x = curBlock->getCell(i)->getCol();
				int y = curBlock->getCell(i)->getRow();
				if (x == xmin && y == ymin) {
					vector <int> temp{ xmin, ymin + 2 };
					dest->emplace_back(temp);
				}
				else if (x == xmin + 1 && y == ymin) {
					vector <int> temp{ xmin, ymin + 1 };
					dest->emplace_back(temp);
				}
				else if (x == xmin && y == ymin + 1) {
					vector <int> temp{ xmin + 1, ymin + 2 };
					dest->emplace_back(temp);
				}
				else if (x == xmin + 1 && y == ymin + 1) {
					vector <int> temp{ xmin + 1, ymin + 1 };
					dest->emplace_back(temp);
				}
				else if (x == xmin && y == ymax) {
					vector <int> temp{ xmin + 2, ymin + 2 };
					dest->emplace_back(temp);
				}
				else {
					vector <int> temp{ xmin + 2, ymin + 1 };
					dest->emplace_back(temp);
				}
			}
		}
}

void Board::RotateDest(vector<vector <int>> *dest) {//curBlock should not be OBlock and IBlock
     //generate potential position for the Block with specific type on the board and put it in dest;
        int xmin = curBlock->getRange("xmin");
        int xmax = curBlock->getRange("xmax");
        int ymin = curBlock->getRange("ymin");
        int ymax = curBlock->getRange("ymax");
		if (ymax - ymin < xmax - xmin) {//the smallest rectangle of the block is 2 * 3
			for (int i = 0; i < 4; ++i) {
				int x = curBlock->getCell(i)->getCol();
				int y = curBlock->getCell(i)->getRow();
				if (x == xmin && y == ymin) {
					vector <int> temp{ xmin + 1, ymin - 1 };
					dest->emplace_back(temp);
				}
				else if (x == xmin + 1 && y == ymin) {
					vector <int> temp{ xmin + 1, ymin };
					dest->emplace_back(temp);
				}
				else if (x == xmax && y == ymin) {
					vector <int> temp{ xmin + 1, ymin + 1 };
					dest->emplace_back(temp);
				}
				else if (x == xmin && y == ymax) {
					vector <int> temp{ xmin, ymin - 1 };
					dest->emplace_back(temp);
				}
				else if (x == xmin + 1 && y == ymax) {
					vector <int> temp{ xmin, ymin };
					dest->emplace_back(temp);
				}
				else {
					vector <int> temp{ xmin, ymin + 1 };
					dest->emplace_back(temp);

				}
			}
		}
		else {//the smallest rectangle of the block is 3 * 2
			for (int i = 0; i < 4; ++i) {
				int x = curBlock->getCell(i)->getCol();
				int y = curBlock->getCell(i)->getRow();
				if (x == xmin && y == ymin) {
					vector <int> temp{ xmin + 2, ymin + 1 };
					dest->emplace_back(temp);
				}
				else if (x == xmin + 1 && y == ymin) {
					vector <int> temp{ xmin + 2, ymin + 2 };
					dest->emplace_back(temp);
				}
				else if (x == xmin && y == ymin + 1) {
					vector <int> temp{ xmin + 1, ymin + 1 };
					dest->emplace_back(temp);
				}
				else if (x == xmin + 1 && y == ymin + 1) {
					vector <int> temp{ xmin + 1, ymin + 2 };
					dest->emplace_back(temp);
				}
				else if (x == xmin && y == ymax) {
					vector <int> temp{ xmin, ymin + 1 };
					dest->emplace_back(temp);
				}
				else {
					vector <int> temp{ xmin, ymin + 2 };
					dest->emplace_back(temp);
				}
			}
		}
}

int Board::Rotate(bool cw) {//if cw is true, rotate clockwise. Otherwise counterclockwise
        if (curBlock->getName()== "OBlock") return 1;
	vector<vector <int>> dest;
	vector<vector <int>> *pdest = &dest;
        if (curBlock->getName() == "IBlock") IRotateDest(pdest);
	else if (cw) RotateDest(pdest);
        else counterRotateDest(pdest);

	//check if destination is full
	for (auto n : dest) {
		int x = n.at(0);
		int y = n.at(1);
		if (theBoard[y][x].getState() != "None") {
			if (theBoard[y][x].getBlock() != curBlock) {
				cout << theBoard[y][x].getState() << endl;
				return 0;
			}
		}
	}
	for (int i = 0; i < 4; ++i) {
		curBlock->getCell(i)->unsetState();
	}
	int i = 0;
	for (auto n : dest) {
		int x = n.at(0);
		int y = n.at(1);
		Cell * temp = &theBoard[y][x];
		curBlock->setCell(i, temp);
		theBoard[y][x].setState(curBlock);
		++i;
	}
        curBlock->setDir(cw);
        return 1;
}

void Board::drop(){
  // first task is to move the current block to the lowest position possible
  while (1) {
    if (!down()) break;
  }
  // check to see if any row has been filled completely
  int lineClear = 0;    // how many lines we clear with this drop
  for (int i=0; i<18; ++i) {
	int count = 0;
	for (int j=0; j<11; ++j) {
	    if (theBoard[i][j].getState()!="None") ++count;
	}
	// if a row is completely filled
	if (count == 11) {
	// first increment the number of lines cleared
	    ++lineClear;
        // now for every Cell in this row, check if its correponding Block has a remain of 1, if so, add score
	    for (int j=0; j<11; ++j) {
		int remainB = theBoard[i][j].getBlock()->getRemain();
		if (remainB == 1) {
		curScore+=(theBoard[i][j].getBlock()->getLevel()+1)*(theBoard[i][j].getBlock()->getLevel()+1);
		if (curScore >= hiScore) hiScore = curScore;
		}
		// after updating the removing Block scores, we decrease this Cell's Block's remain by 1
		theBoard[i][j].getBlock()->setRemain(remainB-1);
		// now we change all Cells(in this row or above) to point to what their up neighbour points to
		for (int k=i; k>0; --k) {
		    auto b = theBoard[k-1][j].getBlock();
		    theBoard[k][j].setState(b);
		}
		theBoard[0][j].unsetState();
	    }
	}
  }
  if (lineClear > 0) curScore+=(lineClear+curLevel->getValue())*(lineClear+curLevel->getValue());
  if (curScore > hiScore) hiScore = curScore;
  curBlock = nextBlock;
  puton();
  nextBlock = curLevel->createBlock();
    if (curBlock->getName() == "EBlock") {
     curBlock = nextBlock;
     puton();
     nextBlock = curLevel->createBlock();
}
  if (!(gd == nullptr)) {
  gd->printnext(nextBlock->getName());
}
}

void Board::levelup() {
    // first get the current level
    int cl = curLevel->getValue();
    int nl = cl+1;
    if (nl == 1) {curLevel = make_unique<LevelOne>();}
    else if (nl == 2) {curLevel = make_unique<LevelTwo>();}
    else if (nl == 3) {curLevel = make_unique<LevelThree>();}
    else if (nl == 4) {curLevel = make_unique<LevelFour>();}
    if (!(gd == nullptr)) {
      gd->printcurScore(curScore);
      gd->printhiScore(hiScore);
	gd->printLevel(curLevel->getValue());
    }
}

void Board::leveldown() {
    // first get the current level
    int cl = curLevel->getValue();
    int nl = cl-1;
    if (nl == 2) {curLevel = make_unique<LevelTwo>();}
    else if (nl == 1) {curLevel = make_unique<LevelOne>();}
    else if (nl == 0) {curLevel = make_unique<LevelZero>();}
    else if (nl == 3) {curLevel = make_unique<LevelThree>();}
    if (!(gd == nullptr)) {
      gd->printcurScore(curScore);
      gd->printhiScore(hiScore);
	gd->printLevel(curLevel->getValue());
    }
}

void Board::random() {
    // if the current level is greater or equal to 2, we set its Boolean field random to true
    if (curLevel->getValue() >  2) {curLevel->setRandom(true);}
}

void Board::norandom(string name) {
    // if the current level is greater or equal to 2, we create a new LevelThree Object and take input from string "name"
    if (curLevel->getValue() == 3) {
	curLevel = make_unique<LevelThree>(name);
	curLevel->setRandom(false);
    }
}

ostream &operator<<(ostream &out, Board &b) {
  out << "Current Score is: " << "     " << b.curScore << endl;
  out << "High Score is     " << "     " << b.hiScore << endl;
  out << "Current Level is: " << "     " << b.curLevel->getValue() << endl;
  out << "------------" << endl;
  out << *(b.td);
  out << "------------" << endl;
  out << "Next Block:" << endl;
  string nextName = b.nextBlock->getName();
  if (nextName == "TBlock") {out << "TTT" << endl; out << " T"; }
  else if (nextName == "SBlock") {out << " SS" << endl; out << "SS";}
  else if (nextName == "ZBlock") {out << "ZZ" << endl; out << " ZZ";}
  else if (nextName == "LBlock") {out << "  L" << endl; out << "LLL";}
  else if (nextName == "JBlock") {out << "J" << endl; out << "JJJ";}
  else if (nextName == "IBlock") {out << "IIII";}
  else if (nextName == "OBlock") {out << "OO" << endl; out << "OO";}
  else if (nextName == "EBlock") {out << "E" << endl;}
  return out;
}

int Board::findMax(int first, int second, int third, int fourth) {//third and fourth is optional
	int max = fourth;
	if (first > max) max = first;
	if (second > max) max = second;
	if (third > max) return third;
	else return max;
}

int Board::consequence(int i, string type, int dir) {
	//return -1 if that position is invalid; i is the column
	int temp;
	if (type == "IBlock" && (dir == 1 || dir == 3)) {
		temp = height[i] + 4;
	}
	else if (type == "IBlock" && (dir == 0 || dir == 2)) {
		if (i > 7) return -1;
		temp = findMax(height[i] + 1, height[i + 1] + 1, height[i + 2] + 1, height[i + 3] + 1);
	}
	else if (type == "JBlock" && dir == 0) {
		if (i > 8) return -1;
		temp = findMax(height[i] + 2, height[i + 1] + 2, height[i + 2] + 2);
	}
	else if (type == "JBlock" && dir == 1) {
		if (i > 9) return -1;
		else temp = findMax(height[i] + 3, height[i + 1] + 1);
	}
	else if (type == "JBlock" && dir == 2) {
		if (i > 8) return -1;
		temp = findMax(height[i] + 1, height[i + 1] + 1, height[i + 2] + 2);
	}
	else if (type == "JBlock" && dir == 3) {
		if (i > 9) return -1;
		temp = findMax(height[i] + 1, height[i + 1] + 3);
	}
	else if (type == "LBlock" && dir == 0) {
		if (i > 8) return -1;
		temp = findMax(height[i] + 2, height[i + 1] + 2, height[i + 2] + 2);
	}
	else if (type == "LBlock" && dir == 1) {
		if (i > 9) return -1;
		temp = findMax(height[i] + 3, height[i + 1] + 3);
	}
	else if (type == "LBlock" && dir == 2) {
		if (i > 8) return -1;
		temp = findMax(height[i] + 2, height[i + 1] + 1, height[i + 2] + 1);
	}
	else if (type == "LBlock" && dir == 3) {
		if (i > 9) return -1;
		temp = findMax(height[i] + 1, height[i + 1] + 3);
	}
	else if (type == "OBlock") {
		if (i > 9) return -1;
		temp = findMax(height[i], height[i + 1]) + 2;
	}
	else if (type == "SBlock" && (dir == 0 || dir == 2)) {
		if (i > 8) return -1;
		temp = findMax(height[i] + 2, height[i + 1] + 2, height[i + 2] + 1);
	}
	else if (type == "SBlock" && (dir == 1 || dir == 3)) {
		if (i > 9) return -1;
		temp = findMax(height[i] + 2, height[i + 1] + 3);
	}
	else if (type == "ZBlock" && (dir == 0 || dir == 2)) {
		if (i > 8) return -1;
		temp = findMax(height[i] + 1, height[i + 1] + 2, height[i + 2] + 2);
	}
	else if (type == "ZBlock" && (dir == 1 || dir == 3)) {
		if (i > 9) return -1;
		temp = findMax(height[i] + 3, height[i + 1] + 2);
	}
	else if (type == "TBlock" && dir == 0) {
		if (i > 8) return -1;
		temp = findMax(height[i] + 1, height[i + 1] + 2, height[i + 2] + 1);
	}
	else if (type == "TBlock" && dir == 1) {
		if (i > 9) return -1;
		temp = findMax(height[i] + 2, height[i + 1] + 3);
	}
	else if (type == "TBlock" && dir == 2) {
		if (i > 8) return -1;
		temp = findMax(height[i] + 2, height[i + 1] + 2, height[i + 2] + 2);
	}
	else if (type == "TBlock" && dir == 3) {
		if (i > 9) return -1;
		temp = findMax(height[i] + 3, height[i + 1]);
	}
	else return -1;
	if (temp > 15) return -1;
	return temp;
}

bool Board::checkReachable(string type, int pos) {
	if (type == "IBlock") {
		for (int i = 4; i < pos; ++i) {
			if (height[i] > 14) return false;
		}
	}
	else if (type == "JBlock") {
		for (int i = 3; i < pos; ++i) {
			if (height[i] > 13) return false;
		}
	}
	else if (type == "LBlock") {
		for (int i = 3; i < pos; ++i) {
			if (height[i] > 13) return false;
		}
	}
	else if (type == "OBlock") {
		for (int i = 2; i < pos; ++i) {
			if (height[i] > 13) return false;
		}
	}
	else if (type == "SBlock") {
		for (int i = 3; i < pos; ++i) {
			if (height[i] > 13) return false;
		}
	}
	else if (type == "ZBlock") {
		for (int i = 3; i < pos; ++i) {
			if (height[i] > 13) return false;
		}
	}
	else if (type == "TBlock") {
		for (int i = 3; i < pos; ++i) {
			if (height[i] > 13) return false;
		}
	}
	return true;
}

void Board::setBest(int *cost, int *costPos, int *costDir) {
	int currCost;
	for (int currPos = 0; currPos < 11; ++currPos) {
		for (int currDir = 3; currDir >=0; --currDir) {
			string type = curBlock->getName();
			currCost = consequence(currPos, type, currDir);
			if (currPos == 0 && currDir == 3 && currCost > 0) {
				*cost = currCost;
				*costPos = 0;
				*costDir = 3;
			}
			else if (currPos == 0 && currDir == 3 && currCost < 0) return;
			else if (*cost >= currCost && currCost > 0) {
				if (checkReachable(type, currPos)) {
				*cost = currCost;
				*costPos = currPos;
				*costDir = currDir;
			}
			else return;
			}
		}
	}
}
//can I reuse this algorithm?
void Board::setCellHint(int dir, int pos, int cost) {
        td->setHint();
	if (!(gd == nullptr)) {gd->setHint();}
	string type = curBlock->getName();
	if (type == "IBlock" && (dir == 0 || dir == 2)) {
		td->notify(theBoard[17 - cost  + 1][pos]);
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17  - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 1][pos + 1]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost  + 1][pos]);
  		gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17  - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 1][pos + 1]);
    }
	}
	else if (type == "IBlock" && (dir == 1|| dir == 2)) {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 - cost + 3][pos]);
		td->notify(theBoard[17 - cost + 4][pos]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
  		gd->notify(theBoard[17 - cost + 3][pos]);
  		gd->notify(theBoard[17 - cost + 4][pos]);
    }
	}
	else if (type == "JBlock" && dir == 0) {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos + 2]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
      gd->notify(theBoard[17 - cost + 2][pos]);
      gd->notify(theBoard[17 - cost + 2][pos + 1]);
      gd->notify(theBoard[17 - cost + 2][pos + 2]);
    }
	}
	else if (type == "JBlock" && dir == 1) {
		td->notify(theBoard[17 -  cost + 1][pos]);
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 -cost + 2][pos]);
		td->notify(theBoard[17 - cost + 3][pos]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 -  cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 -cost + 2][pos]);
  		gd->notify(theBoard[17 - cost + 3][pos]);
    }
	}
	else if (type == "JBlock" && dir == 2) {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 1][pos + 2]);
		td->notify(theBoard[17 - cost + 2][pos + 2]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 1][pos + 2]);
  		gd->notify(theBoard[17 - cost + 2][pos + 2]);
    }
	}
	else if (type == "JBlock" && dir == 3) {
		td->notify(theBoard[17 - cost + 3][pos]);
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
		td->notify(theBoard[17 - cost + 3][pos + 1]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 3][pos]);
      gd->notify(theBoard[17 - cost + 1][pos + 1]);
      gd->notify(theBoard[17 - cost + 2][pos + 1]);
      gd->notify(theBoard[17 - cost + 3][pos + 1]);
    }
	}
	else if (type == "LBlock" && dir == 0) {
		td->notify(theBoard[17 - cost + 1][pos + 2]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos + 2]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos + 2]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
  		gd->notify(theBoard[17 - cost + 2][pos + 2]);
    }
	}
	else if (type == "LBlock" && dir == 1) {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 - cost + 3][pos]);
		td->notify(theBoard[17 - cost + 3][pos + 1]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
  		gd->notify(theBoard[17 - cost + 3][pos]);
  		gd->notify(theBoard[17 - cost + 3][pos + 1]);
    }
	}
	else if (type == "LBlock" && dir == 2) {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 1][pos + 2]);
		td->notify(theBoard[17 - cost + 2][pos]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 1][pos + 2]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
    }
	}
	else if (type == "LBlock" && dir == 3) {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
		td->notify(theBoard[17 - cost + 3][pos + 1]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
  		gd->notify(theBoard[17 - cost + 3][pos + 1]);
    }
	}
	else if (type == "OBlock") {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 -  cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
  		gd->notify(theBoard[17 -  cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
    }
	}
	else if (type == "SBlock" && (dir == 0 || dir == 2)) {
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 1][pos + 2]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 1][pos + 2]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
    }
	}
	else if (type == "SBlock" && (dir == 1 || dir == 3)) {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
		td->notify(theBoard[17 - cost + 3][pos + 1]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
  		gd->notify(theBoard[17 - cost + 3][pos + 1]);
    }
	}
	else if (type == "ZBlock" && (dir == 0 || dir == 2)) {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos + 2]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
  		gd->notify(theBoard[17 - cost + 2][pos + 2]);
    }
	}
	else if (type == "ZBlock" && (dir == 1 || dir == 3)) {
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
		td->notify(theBoard[17 - cost + 3][pos]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
  		gd->notify(theBoard[17 - cost + 3][pos]);
    }
	}
	else if (type == "TBlock" && dir == 0) {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 1][pos + 2]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 1][pos + 2]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
    }
	}
	else if (type == "TBlock" && dir == 1) {
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
		td->notify(theBoard[17 - cost + 3][pos + 1]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
  		gd->notify(theBoard[17 - cost + 3][pos + 1]);
    }
	}
	else if (type == "TBlock" && dir == 2) {
		td->notify(theBoard[17 - cost + 1][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
		td->notify(theBoard[17 - cost + 2][pos + 2]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos + 1]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
  		gd->notify(theBoard[17 - cost + 2][pos + 2]);
    }
	}
	else if (type == "TBlock" && dir == 3) {
		td->notify(theBoard[17 - cost + 1][pos]);
		td->notify(theBoard[17 - cost + 2][pos]);
		td->notify(theBoard[17 - cost + 2][pos + 1]);
		td->notify(theBoard[17 - cost + 3][pos]);
    if (!(gd == nullptr)) {
      gd->notify(theBoard[17 - cost + 1][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos]);
  		gd->notify(theBoard[17 - cost + 2][pos + 1]);
  		gd->notify(theBoard[17 - cost + 3][pos]);
    }
	}
	if (!(gd == nullptr)) gd->unsetHint();
       td->unsetHint();
}

void Board::hint() {
        for (int i = 0; i < 11; ++i) height[i] = 0;//better way?
        //update the value of height
        for (int c = 0; c < 11; ++c) {
           for (int r = 6; r < 18; ++r) {
              if (theBoard[r][c].getState() != "None") {
                 height[c] = 18 - r;
                 break;
              }

           }
        }
	int leastCost = -1;
	int leastCostPos = -1;
	int leastCostDir = -1;
	setBest(&leastCost, &leastCostPos, &leastCostDir);
	if (leastCostPos == -1) {
		cout << "It seems you lost!" << endl;
		return;
	}
	else {
		setCellHint(leastCostDir, leastCostPos, leastCost);
	}
}

int Board::curlevel() { return curLevel->getValue();}

void Board::replace(string name) {//Name is one of I, J, L, O, S, Z, T
	name += "Block";
	int level = curBlock->getLevel();
	int c = curBlock->getRange("xmin");
	int r = curBlock->getRange("ymax");
        shared_ptr<Block> temp = curBlock->getCell(0)->getBlock();
	auto newBlock = make_shared<Block>(name, level);
        unsetCurBlock();
	if (!setCheck(temp, c, r)) {
		cout << "Illegal replacement";
        for (int i=0; i<4; ++i) {
              curBlock->getCell(i)->setState(temp);
         }
          return;
	}
	curBlock = newBlock;
	setCurBlock(curBlock, c, r);
}

