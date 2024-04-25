#include <vtkRenderWindow.h>
#include <vtkNew.h>

#include "Program.h"


void Program::setWinProperties() {
  this->win->SetWindowName("Simulation");
  this->win->SetSize(661, 661);

  this->interact->SetRenderWindow(this->win);
}

// Program::Program() : background(), euler(), lagrange(), win(), interact() {
//   setWinProperties();
// }

Program::Program(Layer bg, Layer e, Layer l) : background(bg), euler(e), lagrange(l), win(), interact() {
  this->win = vtkSmartPointer<vtkRenderWindow>::New();
  this->interact = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  this->win->SetNumberOfLayers(3);
  this->win->AddRenderer(bg.getLayer());
  this->win->AddRenderer(e.getLayer());
  this->win->AddRenderer(l.getLayer());
  setWinProperties();
}


void Program::setBackground(Layer bg) {
  this->win->RemoveRenderer(this->background.getLayer());
  this->background = bg;
  this->win->AddRenderer(bg.getLayer());
  
}


void Program::setEuler(Layer e) {
  this->win->RemoveRenderer(this->euler.getLayer());
  this->euler = e;
  this->win->AddRenderer(e.getLayer());
}


void Program::setLagrange(Layer l) {
  this->win->RemoveRenderer(this->lagrange.getLayer());
  this->lagrange = l;
  this->win->AddRenderer(l.getLayer());
}

// void Program::addInteractionStyle(vtkInteractorStyle style);


void Program::render() {
  this->win->Render();
  this->interact->Start();
}
