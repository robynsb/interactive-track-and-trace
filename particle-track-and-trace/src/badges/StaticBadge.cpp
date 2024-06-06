#include "StaticBadge.h"
#include <vtkGlyph2D.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkTransformFilter.h>
#include <vtkPNGReader.h>
#include <vtkPlaneSource.h>
#include <vtkTexture.h>
#include <vtkTextureMapToPlane.h>
#include <vtkTransform.h>
#include <vtkProperty.h>
#include <vtkImageData.h>

vtkSmartPointer<vtkActor> StaticBadge::getActor() {
  return texturedPlane;
}

StaticBadge::StaticBadge(const std::string &datapath, double size) : datapath(datapath) {

  position->InsertPoint(0, 0, initY, 0);

  vtkNew<vtkPolyData> data;
  data->SetPoints(position);

  vtkNew<vtkPNGReader> pngReader;
  pngReader->SetFileName(datapath.c_str());
  pngReader->Update();

  int dimensions[3];
  pngReader->GetOutput()->GetDimensions(dimensions);
  int width = dimensions[0];
  int height = dimensions[1];
  double aspectRatio = static_cast<double>(width) / static_cast<double>(height);

  // Create a plane
  vtkNew<vtkPlaneSource> plane;
  plane->SetCenter(0.0, 0.0, 0.0);
  plane->SetNormal(0.0, 0.0, 1.0);

  // Apply the texture
  vtkNew<vtkTexture> texture;
  texture->SetInputConnection(pngReader->GetOutputPort());

  vtkNew<vtkTextureMapToPlane> texturePlane;
  texturePlane->SetInputConnection(plane->GetOutputPort());

  vtkNew<vtkTransform> scaler;
  scaler->Scale(size*aspectRatio, size, 1.0);

  vtkNew<vtkTransformFilter> scaleFilter;
  scaleFilter->SetTransform(scaler);
  scaleFilter->SetInputConnection(texturePlane->GetOutputPort());

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(scaleFilter->GetOutputPort());
  glyph2D->SetInputData(data);
  glyph2D->OrientOn();
  glyph2D->ClampingOn();
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper>mapper;
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();

  texturedPlane->SetMapper(mapper);
  texturedPlane->SetTexture(texture);

  setVisible(false);
}

void StaticBadge::setVisible(bool visible) {
  texturedPlane->SetVisibility(visible);
  if(visible) moving = true;
  texturedPlane->Modified();
}

void StaticBadge::reset() {
  Badge::reset();
  setVisible(false);
  texturedPlane->GetProperty()->SetOpacity(1);
  moving = false;
  fadingOut = false;
  movingProgress = 0;
}
double easeOutQuint(double x) {
  return 1 - pow(1 - x, 5);
}

void StaticBadge::updateData(int t) {
  if(moving) {
    double point[3];
    position->GetPoint(0, point);
    point[1] = initY + (targetY-initY)*easeOutQuint(movingProgress);
    position->SetPoint(0, point);
    position->Modified();
    movingProgress += 0.01;
    if (movingProgress > 1) {
      moving = false;
      fadingOut = true;
    }
  }
  if(fadingOut) {
    movingProgress += 0.01;
    if (movingProgress > fadeOutIn) {
      texturedPlane->GetProperty()->SetOpacity(1+ fadeOutIn - movingProgress);
      if (1 + fadeOutIn - movingProgress < 0) {
        fadingOut = false;
      }
    }
  }
}

void StaticBadge::setZ(double z) {
  double point[3];
  position->GetPoint(0, point);
  point[2] = z;
  position->SetPoint(0, point);
  position->Modified();
}