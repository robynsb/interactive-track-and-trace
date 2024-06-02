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

  interact->SetRenderWindow(win);
  interact->Initialize();


  vtkNew<vtkInteractorStyleUser> style;
  interact->SetInteractorStyle(style);

  win->SetDesiredUpdateRate(60);
  win->SetWindowName("Particle Track and Trace Gamification");
}

Program::Program(int timerDT): cam{createNormalisedCamera()} {
  win->SetNumberOfLayers(0);
  setWinProperties();
}

void Program::addLayer(shared_ptr<Layer> layer) {
  layer->setCamera(cam);
  layer->getLayer()->SetLayer(win->GetNumberOfLayers());

  layers.push_back(layer);
  win->AddRenderer(layer->getLayer());
  win->SetNumberOfLayers(win->GetNumberOfLayers() + 1);
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
