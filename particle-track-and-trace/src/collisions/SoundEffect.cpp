#include "SoundEffect.h"

using namespace std;

SoundEffect::SoundEffect(string datapath, const std::shared_ptr<ParticleCollisionCallback> &callback) :
        callback(callback) {
  if (!buffer.loadFromFile(datapath)) {
    throw std::runtime_error("File at \"" + datapath + "\" not found.");
  }
  sound.setBuffer(buffer);
  sound.setVolume(50);
}

void SoundEffect::handleCollision(int index) {
  callback->handleCollision(index);
  sound.stop();
  sound.play();
}
