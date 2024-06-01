#include "Camera.h"

#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>

using namespace std;

double Camera::getScreenShakeOffset() {
  double maxOffset = screenShakeProgress * maxScreenShake / maxScreenShakeDuration;
  return maxOffset * dis(gen);
}

double Camera::getZoomOffset() {
  if (zoomIn) return 1 + zoomProgress * zoomProgress * (maxZoom - 1)/(maxZoomDuration*maxZoomDuration);
  else return 1 + zoomProgress * (maxZoom - 1) / maxZoomDuration;
}

void Camera::clampCamera(double pos[3]) {
  pos[0] += getScreenShakeOffset();
  pos[1] += getScreenShakeOffset();

  auto cam = ren->GetActiveCamera();
  double ogpos[3];
  cam->GetPosition(ogpos);

  cam->SetParallelScale(zoomLevel * getZoomOffset());
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

  int* size = ren->GetRenderWindow()->GetSize();
  if(size[0] != size[1]) {
    int newSize = (size[0] < size[1]) ? size[0] : size[1]; // Choose the smaller dimension
    ren->GetRenderWindow()->SetSize(newSize, newSize);
  }
}

Camera::Camera(): gen(rd()), dis(0.0, 1.0) {
}

void Camera::updateData(int t) {
  if( screenShakeProgress > 0) screenShakeProgress--;
  if (zoomIn) zoomProgress += 3;
  if (zoomProgress > maxZoomDuration) {
    zoomProgress = maxZoomDuration;
    zoomIn = false;
  }
  if (zoomProgress > 0 and !zoomIn) zoomProgress -= 1;

  if (zoomProgress < 0) zoomProgress = 0;
}

void Camera::shakeScreen() {
  screenShakeProgress = maxScreenShakeDuration;
}

void Camera::zoomScreen() {
  zoomIn = true;
}

void Camera::handleGameOver() {
  screenShakeProgress = 0;
  zoomProgress = 0;
  zoomIn = false;
}
