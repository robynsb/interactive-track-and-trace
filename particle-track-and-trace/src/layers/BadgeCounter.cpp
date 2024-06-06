#include "BadgeCounter.h"

#include <vtkTextProperty.h>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void BadgeCounter::updateData(int t) {
  std::ostringstream badgeNumberStream;
  badgeNumberStream << std::fixed << std::setprecision(0) << std::noshowpoint  << acquiredBadgeStatistic->getValue();
  badgeNumberStream << " badges";
  text->SetInput(badgeNumberStream.str().c_str());
}

BadgeCounter::BadgeCounter(const std::shared_ptr<Statistic> &acquiredBadgeStatistic) :
        acquiredBadgeStatistic(acquiredBadgeStatistic) {
  text->SetInput("0 badges");
  text->GetTextProperty()->SetColor(0,0,0);
  text->GetTextProperty()->SetFontSize(50);
  text->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
  text->GetPositionCoordinate()->SetValue(0.7, 0.016);
  renderer->AddActor(text);
}
