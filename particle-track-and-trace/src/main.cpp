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
#include "layers/SplashScreen.h"
#include "Program.h"
#include "advection/UVGrid.h"
#include "advection/kernel/RK4AdvectionKernel.h"
#include "advection/kernel/SnapBoundaryConditionKernel.h"

using namespace std;

#define DT 60 * 60 // 60 sec/min * 60 mins

int main() {
  cout << "Reading data..." << endl;
  string dataPath = "../../../../data";
  shared_ptr<UVGrid> uvGrid = make_shared<UVGrid>(dataPath);
  auto kernelRK4 = make_unique<RK4AdvectionKernel>(uvGrid);
  auto kernelRK4BoundaryChecked = make_unique<SnapBoundaryConditionKernel>(std::move(kernelRK4), uvGrid);
  cout << "Starting vtk..." << endl;

  auto l = new LGlyphLayer(uvGrid, std::move(kernelRK4BoundaryChecked));
//  l->spoofPoints();
  l->setDt(DT);

  unique_ptr<Program> program = make_unique<Program>(DT);
  program->addLayer(new BackgroundImage(dataPath + "/northsea.png"));
  program->addLayer(new EGlyphLayer(uvGrid));
  program->addLayer(l);
  program->addLayer(new SplashScreen(dataPath));

  program->render();

  return EXIT_SUCCESS;
}

