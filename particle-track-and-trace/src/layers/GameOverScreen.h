#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H


#include "Layer.h"

class GameOverScreen : public Layer {
private:
  vtkSmartPointer<vtkActor> texturedPlane;
public:
  void setVisibility(bool visible);
  GameOverScreen(std::string datapath);

  void setCamera(vtkCamera *camera) override;
};


#endif //GAMEOVERSCREEN_H
