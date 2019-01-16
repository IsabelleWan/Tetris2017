#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "subject.h"
#include "cell.h"
using namespace std;

TextDisplay::TextDisplay(): theDisplay{}, width{11}, height{18}, IamHint{false}{
    for (int i = 0; i < height; ++i) {
	vector<char> temp;
        for (int j = 0; j < width; ++j) {
            temp.emplace_back(' ');
        }
	theDisplay.emplace_back(temp);
    }
}

void TextDisplay::notify(Subject &whoNotified) {
    Cell &cr = dynamic_cast<Cell &>(whoNotified);
    int rpos = cr.getRow();
    int cpos = cr.getCol();
    string curBlock;//CHANGES FOR HINT
    if (!IamHint) curBlock = cr.getState();//CHANGES FOR HINT 
    if (IamHint) { theDisplay[rpos][cpos] = '?'; }//NEWLY ADDED FOR HINT
    else if (curBlock == "IBlock") {theDisplay[rpos][cpos] = 'I';}//CHANGES FOR HINT
    else if (curBlock == "JBlock") {theDisplay[rpos][cpos] = 'J';}
    else if (curBlock == "LBlock") {theDisplay[rpos][cpos] = 'L';}
    else if (curBlock == "OBlock") {theDisplay[rpos][cpos] = 'O';}
    else if (curBlock == "SBlock") {theDisplay[rpos][cpos] = 'S';}
    else if (curBlock == "ZBlock") {theDisplay[rpos][cpos] = 'Z';}
    else if (curBlock == "TBlock") {theDisplay[rpos][cpos] = 'T';}
    else if (curBlock == "EBlock") {theDisplay[rpos][cpos] = 'E';}
    else {theDisplay[rpos][cpos] = ' ';}
}

ostream &operator<<(ostream &out, TextDisplay &td) {
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 11; ++j) {
            out <<td.theDisplay[i][j];
            if (!td.IamHint && td.theDisplay[i][j] == '?') {
              td.resetIamHint(i, j);
            }
        }
        out << "|" << endl;
    }
    return out;
}

void TextDisplay::setHint() {
   IamHint = true;
}

void TextDisplay::unsetHint() {
  IamHint = false;
}

void TextDisplay::resetIamHint(int i, int j) {
  theDisplay[i][j] = ' ';
}

