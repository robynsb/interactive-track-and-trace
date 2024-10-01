#include "DayCounter.h"
#include <vtkTextProperty.h>
#include <sstream>
#include <iomanip>
#include <math.h>

// Utility function to determine if a year is a leap year
bool isLeapYear(int year) {
  if (year % 4 != 0) {
    return false;
  } else if (year % 100 != 0) {
    return true;
  } else if (year % 400 != 0) {
    return false;
  } else {
    return true;
  }
}

// Function to convert days since January 1 to a date string
std::string daysToDate(double days) {
  // Days in each month for a non-leap year
  const std::vector<int> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  // Days in each month for a leap year
  const std::vector<int> daysInMonthLeap = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  // Month names
  const std::vector<std::string> monthNames = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

  // Use 2024 as a reference leap year
  int year = 2024;
  bool leapYear = isLeapYear(year);

  // Ensure days is within the range of a single year
  int totalDaysInYear = leapYear ? 366 : 365;
  int dayOfYear = static_cast<int>(std::fmod(days, totalDaysInYear));
  if (dayOfYear < 0) dayOfYear += totalDaysInYear;

  // Find the month and day
  int month = 0;
  while (dayOfYear >= (leapYear ? daysInMonthLeap[month] : daysInMonth[month])) {
    dayOfYear -= (leapYear ? daysInMonthLeap[month] : daysInMonth[month]);
    month++;
  }
  dayOfYear++; // Convert zero-based index to one-based day

  // Format month and day as "D Mon"
  std::ostringstream dateStream;
  dateStream << dayOfYear << " " << monthNames[month];

  return dateStream.str();
}

DayCounter::DayCounter() {
  text->SetInput("1 Jan");
  text->GetTextProperty()->SetColor(0,0,0);
  text->GetTextProperty()->SetFontSize(50);
  text->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
  text->GetPositionCoordinate()->SetValue(0.5, 0.016);
  renderer->AddActor(text);
}

void DayCounter::updateData(int t) {
  int dt = t - lastT;
  lastT = t;
  if (dt < 0) dt = t;
  days += dt/(3600.0*24);
  text->SetInput(daysToDate(days).c_str());
}

void DayCounter::handleGameOver() {
  days = 0;
}

double DayCounter::getValue() const {
  return days;
}

