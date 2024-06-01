#ifndef BADGE_H
#define BADGE_H


#include <vtkActor.h>

class Badge {
private:
  bool collected = false;
public:

  void collect();

  bool isCollected();

  virtual void reset();
  virtual vtkSmartPointer<vtkActor> getActor() = 0;

  virtual void setVisible(bool visible) = 0;

  virtual void updateData(int t);

  virtual ~Badge() = default;

};


#endif //BADGE_H
