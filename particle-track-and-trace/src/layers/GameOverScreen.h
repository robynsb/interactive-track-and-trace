#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "Layer.h"
#include <vtkSmartPointer.h>

class GameOverScreen : public Layer {
public:
  void setVisibility(bool visible);
  GameOverScreen(std::string datapath);

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;

  void setCamera(vtkCamera *camera) override;

  void handleGameOver() override;
private:
  vtkSmartPointer<vtkActor> texturedPlane;
  void dismiss();
};

#endif //GAMEOVERSCREEN_H
