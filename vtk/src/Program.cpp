#include <vtkRenderWindow.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkGlyphSource2D.h>
#include <vtkRegularPolygonSource.h>
#include <vtkGlyph2D.h>
#include <vtkActor2D.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkVertexGlyphFilter.h>
#include <netcdf>
#include <vtkArrowSource.h>
#include <vtkNew.h>
#include <vtkCallbackCommand.h>
#include <vtkInteractorStyleUser.h>

#include "Program.h"
#include "commands/TimerCallbackCommand.h"
#include "CartographicTransformation.h"
#include "commands/CameraMoveCallback.h"

void Program::setWinProperties() {
  this->win->SetWindowName("Simulation");
  this->win->SetSize(661, 661);
  this->win->SetDesiredUpdateRate(60);

  this->interact->SetRenderWindow(this->win);
  this->interact->Initialize();

  vtkNew<vtkInteractorStyleUser> style;
  interact->SetInteractorStyle(style);
}

void Program::setupTimer() {
  auto callback = vtkSmartPointer<TimerCallbackCommand>::New(this);
  callback->SetClientData(this);
  this->interact->AddObserver(vtkCommand::TimerEvent, callback);
  this->interact->CreateRepeatingTimer(17); // 60 fps == 1000 / 60 == 16.7 ms per frame
}

void Program::setupCameraCallback() {
  auto callback = vtkSmartPointer<CameraMoveCallback>::New(this->cam);
  this->interact->AddObserver(vtkCommand::MouseWheelForwardEvent, callback);
  this->interact->AddObserver(vtkCommand::MouseWheelBackwardEvent, callback);
  this->interact->AddObserver(vtkCommand::KeyPressEvent, callback);
}

Program::Program() {
  this->win = vtkSmartPointer<vtkRenderWindow>::New();
  this->interact = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  this->cam = createNormalisedCamera();

  this->win->SetNumberOfLayers(0);
  setWinProperties();
  setupTimer();
  setupCameraCallback();
}


void Program::addLayer(Layer *layer) {
  layer->setCamera(this->cam);

  this->layers.push_back(layer);
  this->win->AddRenderer(layer->getLayer());
  this->win->SetNumberOfLayers(this->win->GetNumberOfLayers() + 1);
}

void Program::removeLayer(Layer *layer) {
  this->win->RemoveRenderer(layer->getLayer());

  auto it = std::find(this->layers.begin(), this->layers.end(), layer);
  if (it != this->layers.end()) {
    this->layers.erase(it);
    this->win->SetNumberOfLayers(this->win->GetNumberOfLayers() - 1);
  }
}


void Program::updateData(int t) {
  win->Render();
  for (Layer *l: layers) {
    l->updateData(t);
  }
}

void Program::setupInteractions() {
  for (Layer *l: layers) {
    l->addObservers(interact);
  }
}

void Program::render() {
  setupInteractions();
  win->Render();
  interact->Start();
}
