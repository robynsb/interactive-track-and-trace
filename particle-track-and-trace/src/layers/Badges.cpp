#include "Badges.h"

#include "../badges/MedianIsKing.h"
#include "../badges/NorthernFulmar.h"
#include "../badges/FirstSteps.h"
#include "../badges/EveryoneMakesMistakes.h"
#include "../CartographicTransformation.h"

#include <vtkPolyData.h>
#include <vtkTransformFilter.h>
#include <vtkTransform.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>

using namespace std;

void Badges::logDebrisConsumption() {
  gramsOfDebrisEaten += 0.01;
}

void Badges::logFoodConsumption() {
  gramsOfFoodEaten += 0.01;
}

Badges::Badges(string datapath) : pq{
        [](const BadgePair &lhs, const BadgePair &rhs) {
          return lhs.first > rhs.first; // For ascending order
        }},
        medianIsKing{make_shared<MedianIsKing>(datapath)},
        northernFulmar{make_shared<NorthernFulmar>(datapath)},
        firstSteps{make_shared<FirstSteps>(datapath)},
        everyoneMakesMistakes{make_shared<EveryoneMakesMistakes>(datapath)}
{
  medianIsKing->setVisible(false);
  ren->AddActor(medianIsKing->getActor());
  badges.push_back(medianIsKing);

  northernFulmar->setVisible(false);
  ren->AddActor(northernFulmar->getActor());
  badges.push_back(northernFulmar);

  firstSteps->setVisible(false);
  ren->AddActor(firstSteps->getActor());
  badges.push_back(firstSteps);

  everyoneMakesMistakes->setVisible(false);
  ren->AddActor(everyoneMakesMistakes->getActor());
  badges.push_back(everyoneMakesMistakes);
}

void Badges::setCamera(vtkCamera *camera) {
  getLayer()->SetActiveCamera(createNormalisedCamera());
}

void Badges::updateData(int t) {
  /**
   * Note: this code assumes that t doesn't reset. However this assumption is false.
   * It happens to be true as long as all awards end before the end of a year.
   * i.e the priority queue pq is empty at the beginning of each new year.
   */
   if (!pq.empty()) {
     auto [time, badge] = pq.top();
     if(time < t) {
       badge->setVisible(false);
       pq.pop();
     }
   }

  double days = t / 3600. / 24;
  if (days >= 365) {
    if (gramsOfDebrisEaten < 0.0001 and !medianIsKing->isCollected()) {
      collectBadge(t, medianIsKing);
    }
  }

  if (gramsOfDebrisEaten >= 0.03 and !northernFulmar->isCollected()) {
    collectBadge(t, northernFulmar);
  }

  if (gramsOfFoodEaten >= 0.00001 and !firstSteps->isCollected()) {
    collectBadge(t, firstSteps);
  }
  if (gramsOfDebrisEaten >= 0.00001 and !everyoneMakesMistakes->isCollected()) {
    collectBadge(t, everyoneMakesMistakes);
  }

  for (auto badge : badges) {
    badge->updateData(t);
  }
}

void Badges::handleGameOver() {
  medianIsKing->reset();
  northernFulmar->reset();
  firstSteps->reset();
  everyoneMakesMistakes->reset();
  while (!pq.empty()) {
    pq.pop();
  }
  gramsOfDebrisEaten = 0;
  gramsOfFoodEaten = 0;
}

void Badges::collectBadge(int t, std::shared_ptr<Badge> badge) {
  badge->setVisible(true);
  badge->collect();
  pq.push({t + displaytime, badge});
}
