#include "SplashScreen.h"

#include "../commands/DisplaySplashScreenCommand.h"
#include "../CartographicTransformation.h"

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

using namespace std;

SplashScreen::SplashScreen(string datapath) {
  ren = vtkSmartPointer<vtkRenderer>::New();
  ren->SetLayer(3);
  vtkSmartPointer<vtkPolyData> data;

  vtkSmartPointer<vtkPoints> position;
  position = vtkSmartPointer<vtkPoints>::New();
  position->InsertPoint(0, 0, 0, 0);

  data = vtkSmartPointer<vtkPolyData>::New();
  data->SetPoints(position);

  vtkNew<vtkPNGReader> pngReader;
  pngReader->SetFileName((datapath + "/simpleSplash.png").c_str());

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
  scaler->Scale(1*16.0/9, 1, 1.0);

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

  texturedPlane = vtkSmartPointer<vtkActor>::New();
  texturedPlane->SetMapper(mapper);
  texturedPlane->SetTexture(texture);

  setVisibility(true);

  ren->AddActor(texturedPlane);
}

void SplashScreen::setCamera(vtkCamera *camera) {
  getLayer()->SetActiveCamera(createNormalisedCamera());
}

void SplashScreen::setVisibility(bool visible) {
  texturedPlane->SetVisibility(visible);
  texturedPlane->Modified();
  if(ren->GetRenderWindow()) ren->GetRenderWindow()->Render();
}

void SplashScreen::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  vtkNew<DisplaySplashScreenCommand> controller;
  controller->setToggle(bind(&SplashScreen::toggle, this));
  interactor->AddObserver(vtkCommand::KeyPressEvent, controller);
}

void SplashScreen::toggle() {
  setVisibility(!texturedPlane->GetVisibility());
}