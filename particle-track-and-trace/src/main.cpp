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
#include "layers/Character.h"
#include "layers/collisions/DummyCollisionHandler.h"
#include "layers/collisions/ParticleCollision.h"
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

  auto lagrange = make_shared<LGlyphLayer>(uvGrid, std::move(kernelRK4BoundaryChecked));
//  l->spoofPoints();
  auto euler = make_shared<EGlyphLayer>(uvGrid);
  auto character = make_shared<Character>();
  auto collisionCallback = make_unique<DummyCollisionHandler>();
  auto collisionHandler = make_shared<ParticleCollision>();
  collisionHandler->addPointSet(lagrange->getPoints(), std::move(collisionCallback));
  collisionHandler->setPosition(character->getPosition());

  unique_ptr<Program> program = make_unique<Program>(DT);
  program->addLayer(make_shared<BackgroundImage>(dataPath + "/map_2071-2067.png"));
  program->addLayer(lagrange);
  program->addLayer(euler);
  program->addLayer(character);
  program->addLayer(collisionHandler);

  program->render();

  return EXIT_SUCCESS;
}

