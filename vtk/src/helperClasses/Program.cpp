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

// Program::Program(Layer *bg, Layer *e, Layer *l) : background(bg), euler(e), lagrange(l), win(), interact() {
//   this->win = vtkSmartPointer<vtkRenderWindow>::New();
//   this->interact = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//
//   this->win->SetNumberOfLayers(3);
//   this->win->AddRenderer(bg->getLayer());
//   this->win->AddRenderer(e->getLayer());
//   this->win->AddRenderer(l->getLayer());
//   setWinProperties();
//   setupTimer();
// }

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


// void Program::setBackground(Layer *bg) {
//   this->win->RemoveRenderer(this->background->getLayer());
//   this->background = bg;
//   this->win->AddRenderer(bg->getLayer());
//   
// }
//
//
// void Program::setEuler(Layer *e) {
//   this->win->RemoveRenderer(this->euler->getLayer());
//   this->euler = e;
//   this->win->AddRenderer(e->getLayer());
// }
//
//
// void Program::setLagrange(Layer *l) {
//   this->win->RemoveRenderer(this->lagrange->getLayer());
//   this->lagrange = l;
//   this->win->AddRenderer(l->getLayer());
// // }

void Program::setLagrangeInteractor(SpawnPointCallback *cb){
    interact->AddObserver(vtkCommand::LeftButtonPressEvent, cb);
    interact->AddObserver(vtkCommand::LeftButtonReleaseEvent, cb);
    interact->AddObserver(vtkCommand::MouseMoveEvent, cb);
}



void Program::updateData(int t) {
  this->win->Render();
  for (Layer *l : layers) {
    l->updateData(t);
  }
  // this->lagrange->updateData(t);
  // this->euler->updateData(t);
}


void Program::render() {
  this->win->Render();
  this->interact->Start();
}
