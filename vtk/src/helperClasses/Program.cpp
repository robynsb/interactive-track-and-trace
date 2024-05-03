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

#include "Program.h"
#include "../commands/TimerCallbackCommand.h"

void Program::setWinProperties() {
  this->win->SetWindowName("Simulation");
  this->win->SetSize(661, 661);
  this->win->SetDesiredUpdateRate(60);

  this->interact->SetRenderWindow(this->win);
  this->interact->Initialize();

}

void Program::setupTimer() {
  auto callback = vtkSmartPointer<TimerCallbackCommand>::New(this);
  callback->SetClientData(this);
  this->interact->AddObserver(vtkCommand::TimerEvent, callback);
  this->interact->CreateRepeatingTimer(17); // 60 fps == 1000 / 60 == 16.7 ms per frame
}


Program::Program(Layer *bg, Layer *e, Layer *l) : background(bg), euler(e), lagrange(l), win(), interact() {
  this->win = vtkSmartPointer<vtkRenderWindow>::New();
  this->interact = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  this->win->SetNumberOfLayers(3);
  this->win->AddRenderer(bg->getLayer());
  this->win->AddRenderer(e->getLayer());
  this->win->AddRenderer(l->getLayer());
  setWinProperties();
  setupTimer();
}


void Program::setBackground(Layer *bg) {
  this->win->RemoveRenderer(this->background->getLayer());
  this->background = bg;
  this->win->AddRenderer(bg->getLayer());
  
}


void Program::setEuler(Layer *e) {
  this->win->RemoveRenderer(this->euler->getLayer());
  this->euler = e;
  this->win->AddRenderer(e->getLayer());
}


void Program::setLagrange(Layer *l) {
  this->win->RemoveRenderer(this->lagrange->getLayer());
  this->lagrange = l;
  this->win->AddRenderer(l->getLayer());
}

// void Program::addInteractionStyle(vtkInteractorStyle style);



void Program::updateData(int t) {
  this->win->Render();
  this->lagrange->updateData(t);
  this->euler->updateData(t);
}


void Program::render() {
  this->win->Render();
  this->interact->Start();
}
