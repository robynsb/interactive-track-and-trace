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
#include "layers/EulerGlyphs.h"
#include "layers/Vessels.h"
#include "layers/FoodSpawner.h"
#include "layers/LagrangeGlyphs.h"
#include "layers/Character.h"
#include "collisions/DummyCollisionHandler.h"
#include "collisions/ParticleRemover.h"
#include "layers/ParticleCollision.h"
#include "vesselroutes/VesselRouteFactory.h"
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
  auto kernelRK4Food = make_unique<RK4AdvectionKernel>(uvGrid);
  auto kernelRK4BoundaryCheckedFood = make_unique<SnapBoundaryConditionKernel>(std::move(kernelRK4Food), uvGrid);

  cout << "Starting vtk..." << endl;
  auto litter = make_shared<LagrangeGlyphs>(uvGrid, std::move(kernelRK4BoundaryChecked));
  litter->setColour(254, 74, 73);
//  auto euler = make_shared<EulerGlyphs>(uvGrid);
  auto character = make_shared<Character>(uvGrid, dataPath);

  auto litterRemover = make_unique<ParticleRemover>(litter->getPoints());
  auto collisionHandler = make_shared<ParticleCollision>();
  collisionHandler->addPointSet(litter->getPoints(), std::move(litterRemover));
  collisionHandler->setPosition(character->getPosition());

  auto vessels = createVesselLayer(uvGrid, dataPath);
  vessels->setDepositAndBeached(litter->getPoints(), litter->getBeached());

  auto food = make_shared<LagrangeGlyphs>(uvGrid, std::move(kernelRK4BoundaryCheckedFood));
  food->setColour(5, 74, 41);
  auto foodSpawn = make_shared<FoodSpawner>(food->getPoints(), food->getBeached());
  auto foodRemover = make_unique<ParticleRemover>(food->getPoints());
  collisionHandler->addPointSet(food->getPoints(), std::move(foodRemover));

  unique_ptr<Program> program = make_unique<Program>(DT);
  program->addLayer(make_shared<BackgroundImage>(dataPath + "/map_2071-2067.png"));
  program->addLayer(litter);
//  program->addLayer(euler);
  program->addLayer(food);
  program->addLayer(foodSpawn);
  program->addLayer(collisionHandler);
  program->addLayer(vessels);
  program->addLayer(character);

  program->render();

  return EXIT_SUCCESS;
}

