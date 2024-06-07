#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Layer.h"

class SplashScreen : public Layer {
public:
  void setVisibility(bool visible);
  SplashScreen(std::string datapath);

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;

  void setCamera(vtkCamera *camera) override;

  void handleGameOver() override;
private:
  vtkSmartPointer<vtkActor> texturedPlane;
  void toggle();
  bool gameOver {false};
};


#endif //SPLASHSCREEN_H
