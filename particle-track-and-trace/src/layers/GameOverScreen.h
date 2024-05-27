#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H


#include <vtkPoints.h>
#include "Layer.h"

class GameOverScreen : public Layer {
private:
  vtkSmartPointer<vtkActor> texturedPlane;
  void dismiss();
public:
  void setVisibility(bool visible);
  GameOverScreen(std::string datapath);

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;

  void setCamera(vtkCamera *camera) override;

  void handleGameOver() override;
};


#endif //GAMEOVERSCREEN_H
