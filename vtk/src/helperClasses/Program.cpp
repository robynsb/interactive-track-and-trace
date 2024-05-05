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
#include "../commands/TimerCallbackCommand.h"
#include "SpawnPointCallback.h"

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

Program::Program() {
  this->win = vtkSmartPointer<vtkRenderWindow>::New();
  this->interact = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  this->win->SetNumberOfLayers(0);
  setWinProperties();
  setupTimer();
}


void Program::addLayer(Layer* layer) {
  this->layers.push_back(layer);
  this->win->AddRenderer(layer->getLayer());
  this->win->SetNumberOfLayers(this->win->GetNumberOfLayers()+1);
}

void Program::removeLayer(Layer *layer) {
  this->win->RemoveRenderer(layer->getLayer());

  auto it = std::find(this->layers.begin(), this->layers.end(), layer); 
  if (it != this->layers.end()) { 
    this->layers.erase(it); 
    this->win->SetNumberOfLayers(this->win->GetNumberOfLayers()-1);
  }
}



void Program::setLagrangeInteractor(SpawnPointCallback *cb){
    this->interact->AddObserver(vtkCommand::LeftButtonPressEvent, cb);
    this->interact->AddObserver(vtkCommand::LeftButtonReleaseEvent, cb);
    this->interact->AddObserver(vtkCommand::MouseMoveEvent, cb);
}



void Program::updateData(int t) {
  this->win->Render();
  for (Layer *l : layers) {
    l->updateData(t);
  }
}


void Program::render() {
  this->win->Render();
  this->interact->Start();
}
