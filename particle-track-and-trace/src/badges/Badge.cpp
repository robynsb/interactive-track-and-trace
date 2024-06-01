#include "Badge.h"

bool Badge::isCollected() {
  return collected;
}

void Badge::collect() {
  collected = true;
}

void Badge::reset() {
  collected = false;
}

void Badge::updateData(int t) {
  // By default do nothing
}