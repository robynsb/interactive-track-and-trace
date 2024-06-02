#include "DummyCollisionHandler.h"

#include <iostream>

using namespace std;

void DummyCollisionHandler::handleCollision(int index) {
  cout << "Collided with particle of index " << index << endl;

}
