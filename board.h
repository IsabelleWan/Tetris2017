#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <memory>
#include "cell.h"
#include "graphicsdisplay.h"

class Block;
class Level;
class TextDisplay;

class Board {
  std::vector<std::vector<Cell>> theBoard; // 2D vector of Cells
  int curScore;  // current score
  int hiScore;   // high score
  std::shared_ptr<Level>curLevel; // a pointer to a Level, representing the current level the game is in
  std::vector<std::shared_ptr<Block>> blocks; // keep track of all the blocks
  std::shared_ptr<TextDisplay> td;
  std::shared_ptr<Block> curBlock;  // a pointer to the currently block that we are manipulating
  std::shared_ptr<Block> nextBlock;  // a pointer to the next Block
  std::shared_ptr<GraphicsDisplay> gd;
  int posHint;
  int dirHint;
  int height[11];
  //private methods
  void IRotateDest(std::vector<std::vector<int>> *);
  void RotateDest(std::vector<std::vector<int>> *);
  void counterRotateDest(std::vector<std::vector<int>> *);
  void setCellHint(int dir, int pos, int cost);//NEWLY ADDED
  int consequence(int i, std::string type, int dir);//NEWLY ADDED
  int findMax(int first, int second, int third = 0, int fourth = 0);//NEWLY ADDED
  bool checkReachable(std::string type, int pos);
  void setBest(int *cost, int *costPos, int *costDir);
  //methods for set and unset current Block
  bool setCheck(std::shared_ptr<Block>, int, int);
  void setCurBlock(std::shared_ptr<Block>, int, int);
  void unsetCurBlock(); 
public:
  Board();
  void puton();   // Takes a pointer to a Block(nextBlock), place it at top left possible if possible
  void init(int, std::string);
  int getHigh();
  void setHigh(int);
  int left();
  int right();
  int down();
  int Rotate(bool);
  void drop();
  void levelup();
  void leveldown();
  void norandom(std::string);
  void random();
  void replace(std::string);
  friend std::ostream &operator<<(std::ostream &, Board &);
  void setObserver();
  void hint();//ADDED FOR HINT
  void removegraphics();
  int curlevel();
  void printHigh();
};

#endif

