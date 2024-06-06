#include "GameOverScreen.h"

#include "../CartographicTransformation.h"
#include "../commands/DismissGameoverScreen.h"

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

GameOverScreen::GameOverScreen(string datapath) {

  vtkSmartPointer<vtkPolyData> data;

  vtkSmartPointer<vtkPoints> position;
  position = vtkSmartPointer<vtkPoints>::New();
  position->InsertPoint(0, 0, 0, 0);

  data = vtkSmartPointer<vtkPolyData>::New();
  data->SetPoints(position);

  vtkNew<vtkPNGReader> pngReader;
  pngReader->SetFileName((datapath + "/gameover.png").c_str());

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
  scaler->Scale(1.5*1.77, 1.5, 1.0);

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

//  actor->GetProperty()->SetColor(0, 0, 0);
//  actor->GetProperty()->SetOpacity(0.2);

  setVisibility(false);

  renderer->AddActor(texturedPlane);
}

void GameOverScreen::setCamera(vtkCamera *camera) {
  getLayer()->SetActiveCamera(createNormalisedCamera());
}

void GameOverScreen::setVisibility(bool visible) {
  if (visible) {
    texturedPlane->SetVisibility(true);
  } else {
    texturedPlane->SetVisibility(false);
  }
  texturedPlane->Modified();
  if(renderer->GetRenderWindow()) renderer->GetRenderWindow()->Render();
}

void GameOverScreen::handleGameOver() {
  setVisibility(true);
}

void GameOverScreen::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  vtkNew<DismissGameoverScreen> controller;
  controller->setDismiss(bind(&GameOverScreen::dismiss, this));
  interactor->AddObserver(vtkCommand::KeyPressEvent, controller);
}

void GameOverScreen::dismiss() {
  setVisibility(false);
}