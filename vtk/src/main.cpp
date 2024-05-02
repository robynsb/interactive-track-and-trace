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
  auto bg = new BackgroundImage("../../../../data/map_661-661.png");
  auto e = new EGlyphLayer();
  auto l = new LGlyphLayer();
  l->spoofPoints();

  auto program = new Program(bg, e, l);
  program->render();

  return EXIT_SUCCESS;
}

