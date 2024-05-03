#include <vtkRenderWindow.h>
#include <vtkNew.h>
#include <vtkCallbackCommand.h>
#include <vtkInteractorStyleUser.h>

#include "Program.h"
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

void Program::CallbackFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData) {
  ((Program *)clientData)->lagrange->updateData(1);
  ((Program *)clientData)->win->Render();
}

void Program::setupTimer() {
  vtkNew<vtkCallbackCommand> callback;
  callback->SetCallback(this->CallbackFunction);
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

void Program::setLagrangeInteractor(SpawnPointCallback *cb){
    interact->AddObserver(vtkCommand::LeftButtonPressEvent, cb);
    interact->AddObserver(vtkCommand::LeftButtonReleaseEvent, cb);
    interact->AddObserver(vtkCommand::MouseMoveEvent, cb);
}


void Program::render() {
  this->win->Render();
  this->interact->Start();
}
