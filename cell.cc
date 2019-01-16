#include "cell.h"
#include "subject.h"
#include "block.h"
using namespace std;

Cell::Cell(int row, int col):row{row},col{col},BlockInCell{nullptr}, 
IamHint{false}{}

void Cell::setState(shared_ptr<Block> b){
  BlockInCell = b;
  notifyObservers();
}

void Cell::unsetState() {
	BlockInCell = nullptr;
	this->notifyObservers();
}

int Cell::getRow() {
	return row;
}

int Cell::getCol() {
	return col;
}

shared_ptr<Block> Cell::getBlock() {return BlockInCell;}

string Cell::getState() {
	if (BlockInCell == nullptr) {return "None";}
	else {return BlockInCell->getName();}
}
 
bool Cell::getHint(){
    return IamHint;
}

