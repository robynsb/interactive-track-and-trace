#include <netcdf>
#include <vtkActor2D.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>

#include "layers/BackgroundImage.h"
#include "layers/EGlyphLayer.h"
#include "layers/LGlyphLayer.h"
#include "Program.h"

using namespace std;


int main() {
  auto l = new LGlyphLayer();
  l->spoofPoints();

  Program *program = new Program();
  program->addLayer(new BackgroundImage("../../../../data/map_661-661.png"));
  program->addLayer(new EGlyphLayer());
  program->addLayer(l);

  program->render();

  return EXIT_SUCCESS;
}

