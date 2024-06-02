#include "DayCounter.h"
#include <vtkTextProperty.h>
#include <iostream>
#include <sstream>
#include <iomanip>

DayCounter::DayCounter() {
  text->SetInput("0.0 days");
  text->GetTextProperty()->SetColor(0,0,0);
  text->GetTextProperty()->SetFontSize(50);
  text->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
  text->GetPositionCoordinate()->SetValue(0.6, 0.016);
  ren->AddActor(text);
}

void DayCounter::updateData(int t) {
  int dt = t - lastT;
  lastT = t;
  if (dt < 0) dt = t;
  days += dt/(3600.0*24);
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(1) << days << " days";
  std::string rounded_string = stream.str();
  text->SetInput(rounded_string.c_str());
}

void DayCounter::handleGameOver() {
  days = 0;
}

double DayCounter::getValue() const {
  return days;
}

