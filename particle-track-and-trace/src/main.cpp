#include <netcdf>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>
#include <memory>

#include "layers/BackgroundImage.h"
#include "layers/EulerGlyphs.h"
#include "layers/Vessels.h"
#include "layers/FoodSpawner.h"
#include "layers/LagrangeGlyphs.h"
#include "layers/Character.h"
#include "layers/Health.h"
#include "layers/GameOverScreen.h"
#include "layers/Timer.h"
#include "layers/ParticleCollision.h"
#include "layers/DayCounter.h"
#include "layers/Badges.h"
#include "collisions/ParticleRemover.h"
#include "collisions/FoodPickup.h"
#include "collisions/DebrisPickup.h"
#include "vesselroutes/VesselRouteFactory.h"
#include "Program.h"
#include "advection/UVGrid.h"
#include "advection/kernel/RK4AdvectionKernel.h"
#include "advection/kernel/SnapBoundaryConditionKernel.h"

using namespace std;

constexpr int dt = 60 * 60; // 60 sec/min * 60 mins

int main() {
  cout << "Reading data..." << endl;
  string dataPath = "../../../../data";
  shared_ptr<UVGrid> uvGrid = make_shared<UVGrid>(dataPath);
  auto kernelRK4 = make_unique<RK4AdvectionKernel>(uvGrid);
  auto kernelRK4BoundaryChecked = make_unique<SnapBoundaryConditionKernel>(std::move(kernelRK4), uvGrid);
  auto kernelRK4Food = make_unique<RK4AdvectionKernel>(uvGrid);
  auto kernelRK4BoundaryCheckedFood = make_unique<SnapBoundaryConditionKernel>(std::move(kernelRK4Food), uvGrid);

  cout << "Starting vtk..." << endl;
  auto program = make_shared<Program>(dt);
  auto timer = make_shared<Timer>(program, dt);
  auto camera = make_shared<Camera>();

  auto gameover = make_shared<GameOverScreen>(dataPath);
  auto badges = make_shared<Badges>(dataPath);

  auto litter = make_shared<LagrangeGlyphs>(uvGrid, std::move(kernelRK4BoundaryChecked));
  litter->setColour(254, 74, 73);
//  auto euler = make_shared<EulerGlyphs>(uvGrid);
  auto character = make_shared<Character>(uvGrid, dataPath, camera);

  auto health = make_shared<Health>(program);
  auto litterRemover = make_unique<DebrisPickup>(litter->getPoints(), health, camera, badges);
  auto collisionHandler = make_shared<ParticleCollision>();
  collisionHandler->addPointSet(litter->getPoints(), std::move(litterRemover));
  collisionHandler->setPosition(character->getPosition());

  auto vessels = createVesselLayer(uvGrid, dataPath);
  vessels->setDepositAndBeached(litter->getPoints(), litter->getBeached());

  auto food = make_shared<LagrangeGlyphs>(uvGrid, std::move(kernelRK4BoundaryCheckedFood));
  food->setColour(5, 74, 41);
  auto foodSpawn = make_shared<FoodSpawner>(food->getPoints(), food->getBeached());
  auto foodRemover = make_unique<FoodPickup>(food->getPoints(), health, camera, character, badges);
  collisionHandler->addPointSet(food->getPoints(), std::move(foodRemover));

  auto dayCounter = make_shared<DayCounter>();

  program->addLayer(timer);
  program->addLayer(make_shared<BackgroundImage>(dataPath + "/map_2071-2067.png"));
  program->addLayer(litter);
//  program->addLayer(euler);
  program->addLayer(food);
  program->addLayer(foodSpawn);
  program->addLayer(collisionHandler);
  program->addLayer(vessels);
  program->addLayer(character);
  program->addLayer(health);
  program->addLayer(camera);
  program->addLayer(gameover);
  program->addLayer(dayCounter);
  program->addLayer(badges);

  program->render();

  return EXIT_SUCCESS;
}

