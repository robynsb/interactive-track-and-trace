#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Layer.h"

class SplashScreen : public Layer {
public:
  void setVisibility(bool visible);
  SplashScreen(std::string datapath);

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;

  void setCamera(vtkCamera *camera) override;
private:
  vtkSmartPointer<vtkActor> texturedPlane;
  void toggle();
};


#endif //SPLASHSCREEN_H
