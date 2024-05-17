#include "DummyCollisionHandler.h"

#include <iostream>

using namespace std;

void DummyCollisionHandler::handleCollision(int index) const {
  cout << "Collided with particle of index " << index << endl;

}
