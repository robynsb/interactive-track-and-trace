#include <netcdf>
#include <vtkActor2D.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>
#include <memory>

#include "layers/BackgroundImage.h"
#include "layers/EGlyphLayer.h"
#include "layers/LGlyphLayer.h"
#include "Program.h"
#include "advection/UVGrid.h"
#include "advection/RK4AdvectionKernel.h"

using namespace std;


int main() {
  shared_ptr<UVGrid> uvGrid = std::make_shared<UVGrid>();
  auto kernelRK4 = make_unique<RK4AdvectionKernel>(uvGrid);

  auto l = new LGlyphLayer(move(kernelRK4));
//  l->spoofPoints();

  Program *program = new Program();
  program->addLayer(new BackgroundImage("../../../../data/map_661-661.png"));
  program->addLayer(new EGlyphLayer(uvGrid));
  program->addLayer(l);

  program->render();

  return EXIT_SUCCESS;
}

