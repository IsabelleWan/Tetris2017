#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include<memory>
class Observer;

class Subject {
  std::vector<std::shared_ptr<Observer>> observers;
public:
  void attach(std::shared_ptr<Observer> ob);
  void notifyObservers();
  virtual ~Subject() = 0;
};

#endif

