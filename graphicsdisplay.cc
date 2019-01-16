#include <iostream>
#include <sstream>
#include "graphicsdisplay.h"
#include "subject.h"
#include "board.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay():
 width{495}, height{810}, winSize{500}, xw{495, 810}, hint{false}{
  xw.fillRectangle(0, 0, width, height, Xwindow::Black);
}


void GraphicsDisplay::notify(Subject &whoNotified) {
  Cell &info = dynamic_cast<Cell &>(whoNotified);
  int cellSize = 45;
  string curBlock = info.getState();
  if (curBlock == "IBlock") {
    xw.fillRectangle(info.getCol() * cellSize, info.getRow() * cellSize, cellSize, cellSize, Xwindow::Cyan);
  } else if (curBlock == "JBlock") {
    xw.fillRectangle(info.getCol() * cellSize, info.getRow() * cellSize, cellSize, cellSize, Xwindow::Brown);
  } else if (curBlock == "LBlock") {
    xw.fillRectangle(info.getCol() * cellSize, info.getRow() * cellSize, cellSize, cellSize, Xwindow::Red);
  } else if (curBlock == "OBlock") {
    xw.fillRectangle(info.getCol() * cellSize, info.getRow() * cellSize, cellSize, cellSize, Xwindow::Green);
  } else if (curBlock == "SBlock") {
    xw.fillRectangle(info.getCol() * cellSize, info.getRow() * cellSize, cellSize, cellSize, Xwindow::Blue);
  } else if (curBlock == "ZBlock") {
    xw.fillRectangle(info.getCol() * cellSize, info.getRow() * cellSize, cellSize, cellSize, Xwindow::Orange);
  } else if (curBlock == "TBlock") {
    xw.fillRectangle(info.getCol() * cellSize, info.getRow() * cellSize, cellSize, cellSize, Xwindow::Magenta);
  } else if (curBlock == "EBlock") {
    xw.fillRectangle(info.getCol() * cellSize, info.getRow() * cellSize, cellSize, cellSize, Xwindow::Yellow);
  } else {
    xw.fillRectangle(info.getCol() * cellSize, info.getRow() * cellSize, cellSize, cellSize, Xwindow::Black);
  }
  if (hint == true) {
    xw.fillRectangle(info.getCol() * cellSize, info.getRow() * cellSize, cellSize, cellSize, Xwindow::White);}
}

void GraphicsDisplay::printnext(string next) {
  int cellSize = 45;
  xw.drawString(315,35,"Next Block:", Xwindow::White);
  xw.fillRectangle(10 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(9 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(8 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(7 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(10 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(9 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(8 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(7 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::Black);
  if (next == "IBlock") {
    xw.fillRectangle(10 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(8 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(7 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
  } else if (next == "JBlock") {
    xw.fillRectangle(7 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(7 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(8 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
  } else if (next == "LBlock") {
    xw.fillRectangle(7 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(8 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
  } else if (next == "OBlock") {
    xw.fillRectangle(8 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(8 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
  } else if (next == "SBlock") {
    xw.fillRectangle(8 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(10 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
  } else if (next == "ZBlock") {
    xw.fillRectangle(8 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(10 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
  } else if (next == "TBlock") {
    xw.fillRectangle(8 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(9 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::White);
    xw.fillRectangle(10 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::White);
  } else {
    xw.fillRectangle(0,0, cellSize, cellSize, Xwindow::Black);
  }
}

void GraphicsDisplay::printhiScore(int n) {
  ostringstream ss;
  ss << "Hiscore: " << n;
  xw.drawString(40,55, ss.str(), Xwindow::Yellow);
}

void GraphicsDisplay::printcurScore(int n) {
  int cellSize = 45;
  xw.fillRectangle(2 * cellSize, 0 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(2 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(2 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(3 * cellSize, 0 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(3 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(3 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(4 * cellSize, 0 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(4 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(4 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(5 * cellSize, 0 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(5 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(5 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(6 * cellSize, 0 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(6 * cellSize, 1 * cellSize, cellSize, cellSize, Xwindow::Black);
  xw.fillRectangle(6 * cellSize, 2 * cellSize, cellSize, cellSize, Xwindow::Black);
  ostringstream ss;
  ss << "Current Score: " << n;
  xw.drawString(40,70, ss.str(), Xwindow::White);
}

void GraphicsDisplay::printLevel(int n) {
  ostringstream ss;
  ss << "Current Level: " << n;
  xw.drawString(40,40, ss.str(), Xwindow::Yellow);
}

void GraphicsDisplay::setHint() {
 hint = true;
}

void GraphicsDisplay::unsetHint() {
 hint = false;
}

