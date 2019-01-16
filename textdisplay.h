#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H

#include "observer.h"
#include <vector>
class Subject;

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
  const int width;
  const int height;
  bool IamHint;
public:
  TextDisplay();
  void notify(Subject &whoNotified) override;
  friend std::ostream &operator<<(std::ostream &out, TextDisplay &td);
  void resetIamHint(int i,  int j);
  void unsetHint();
  void setHint();
};

#endif

