#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"

class Cell;

class GraphicsDisplay: public Observer {
  const int width, height, winSize;
  Xwindow xw;
  bool hint;

 public:
  GraphicsDisplay();

  void notify(Subject &whoNotified) override;

  void printhiScore(int n);

  void printcurScore(int n);

  void printLevel(int n);

  void setHint();

  void unsetHint();
  void printnext(std::string);
};
#endif


