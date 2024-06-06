#include <vtkPolyDataMapper2D.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkActor2D.h>
#include <vtkProperty.h>
#include <vtkPNGReader.h>
#include <vtkPlaneSource.h>
#include <vtkTexture.h>
#include <vtkTextureMapToPlane.h>
#include <vtkPolyDataMapper.h>
#include <vtkGlyph2D.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>

#include "../CartographicTransformation.h"

#include "Vessels.h"

using namespace std;

Vessels::Vessels(std::shared_ptr<UVGrid> uvGrid, string path):
    uvGrid(uvGrid), deposition(nullptr), particlesBeached(nullptr) {
  // Read the image which will be the texture
  vtkNew<vtkPNGReader> pngReader;
  pngReader->SetFileName((path + "/vessel.png").c_str());

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
  scaler->Scale(0.05, 0.05, 1.0);

  vtkNew<vtkTransformFilter> scaleFilter;
  scaleFilter->SetTransform(scaler);
  scaleFilter->SetInputConnection(texturePlane->GetOutputPort());

  position = vtkSmartPointer<vtkPoints>::New();

  data = vtkSmartPointer<vtkPolyData>::New();
  data->SetPoints(position);

  vtkSmartPointer<vtkTransformFilter> latLonCoordinates = createCartographicTransformFilter(*uvGrid);
  latLonCoordinates->SetInputData(data);
  latLonCoordinates->Update();

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(scaleFilter->GetOutputPort());
  glyph2D->SetInputConnection(latLonCoordinates->GetOutputPort());
  glyph2D->SetScaleModeToDataScalingOff();
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper> planeMapper;
  planeMapper->SetInputConnection(glyph2D->GetOutputPort());

  vtkNew<vtkActor> texturedPlane;
  texturedPlane->SetMapper(planeMapper);
  texturedPlane->SetTexture(texture);

  renderer->AddActor(texturedPlane);
}

void Vessels::addRoute(std::shared_ptr<VesselRoute> route) {
  auto [x, y] = route->getPosition(0);
  position->InsertPoint(routes.size(), x, y, 0);
  routes.push_back(route);
}

void Vessels::updateData(int t) {
  for (int i = 0; i < routes.size(); i++) {
    auto route = routes.at(i);
    auto [x,y] = route->getPosition(t);
    position->SetPoint(i, x, y, 0);
    position->Modified();
    if (deposition != nullptr and route->isWrecking(t)) {
      deposition->InsertNextPoint(x, y, 0);
      deposition->Modified();
      particlesBeached->InsertNextValue(0);
      particlesBeached->Modified();
    }
  }
}

void Vessels::setDepositAndBeached(vtkSmartPointer<vtkPoints> deposit, vtkSmartPointer<vtkIntArray> particlesBeached) {
  deposition = deposit;
  this->particlesBeached = particlesBeached;
}
