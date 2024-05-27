#include "Camera.h"

#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>


using namespace std;

double Camera::getScreenShakeOffset() {
  double maxOffset = screenShakeProgress * MAXSCREENSHAKE / MAXSCREENSHAKEDURATION;
  return maxOffset * dis(gen);
}

void Camera::clampCamera(double pos[3]) {
  pos[0] += getScreenShakeOffset();
  pos[1] += getScreenShakeOffset();

  auto cam = ren->GetActiveCamera();
  double ogpos[3];
  cam->GetPosition(ogpos);

  cam->SetParallelScale(0.4);
  double scale = cam->GetParallelScale();

  // only check the x,y coords of the camera; we don't care about z
  for (int i=0; i < 2; i++) {
    //boundary cond: scale+|pos| < 1.
    if (abs(pos[i])+scale >= 1.0) {
      if (pos[i] >= 0) {
        pos[i] = 1 - scale;
      } else {
        pos[i] = scale - 1;
      }
    }
  }

  cam->SetPosition(pos[0], pos[1], ogpos[2]);
  cam->SetFocalPoint(pos[0], pos[1], 0);
}

Camera::Camera(): gen(rd()), dis(0.0, 1.0) {
}

void Camera::updateData(int t) {
  if( screenShakeProgress > 0) screenShakeProgress--;
}

void Camera::shakeScreen() {
  screenShakeProgress = MAXSCREENSHAKEDURATION;
}