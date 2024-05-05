#include <netcdf>
#include <vtkActor2D.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>

#include "helperClasses/BackgroundImage.h"
#include "helperClasses/EGlyphLayer.h"
#include "helperClasses/LGlyphLayer.h"
#include "helperClasses/Program.h"

using namespace std;


int main() {
  auto l = new LGlyphLayer();
  l->spoofPoints();

  Program *program = new Program();
  program->addLayer(new BackgroundImage("../../../../data/map_661-661.png"));
  program->addLayer(new EGlyphLayer());
  program->addLayer(l);

  // auto program = new Program(bg, e, l);
  program->setLagrangeInteractor(l->createSpawnPointCallback());
  program->render();

  return EXIT_SUCCESS;
}

