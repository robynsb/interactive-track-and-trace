#include <vtkRenderWindow.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkGlyph2D.h>
#include <vtkActor2D.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkNew.h>
#include <vtkCallbackCommand.h>
#include <vtkInteractorStyleUser.h>

#include "Program.h"
#include "CartographicTransformation.h"
#include "commands/CameraMoveCallback.h"

using namespace std;

void Program::setWinProperties() {
  this->win->SetWindowName("Simulation");
  this->win->SetSize(661, 661);
  this->win->SetDesiredUpdateRate(60);

  this->interact->SetRenderWindow(this->win);
  this->interact->Initialize();

  vtkNew<vtkInteractorStyleUser> style;
  interact->SetInteractorStyle(style);
}

Program::Program(int timerDT) {
  this->win = vtkSmartPointer<vtkRenderWindow>::New();
  this->interact = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  this->cam = createNormalisedCamera();

  this->win->SetNumberOfLayers(0);
  setWinProperties();
}

void Program::addLayer(shared_ptr<Layer> layer) {
  layer->setCamera(this->cam);
  layer->getLayer()->SetLayer(this->win->GetNumberOfLayers());

  this->layers.push_back(layer);
  this->win->AddRenderer(layer->getLayer());
  this->win->SetNumberOfLayers(this->win->GetNumberOfLayers() + 1);
}

void Program::removeLayer(std::shared_ptr<Layer> layer) {
  this->win->RemoveRenderer(layer->getLayer());

  auto it = std::find(this->layers.begin(), this->layers.end(), layer);
  if (it != this->layers.end()) {
    this->layers.erase(it);
    this->win->SetNumberOfLayers(this->win->GetNumberOfLayers() - 1);
  }
}


void Program::updateData(int t) {
  win->Render();
  for (shared_ptr<Layer> l: layers) {
    l->updateData(t);
  }
}

void Program::setupInteractions() {
  for (shared_ptr<Layer> l: layers) {
    l->addObservers(interact);
  }
}

void Program::render() {
  setupInteractions();
  win->Render();
  interact->Start();
}

void Program::handleGameOver() {
  for (shared_ptr<Layer> l: layers) {
    l->handleGameOver();
  }
}
