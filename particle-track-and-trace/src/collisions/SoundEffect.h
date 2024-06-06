#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include "ParticleCollisionCallback.h"
#include <SFML/Audio.hpp>
#include <string>

class SoundEffect : public ParticleCollisionCallback {
public:
  SoundEffect(std::string datapath, const std::shared_ptr<ParticleCollisionCallback> &callback);

  void handleCollision(int index) override;
private:
  sf::SoundBuffer buffer;
  sf::Sound sound;
  std::shared_ptr<ParticleCollisionCallback> callback;
};


#endif //SOUNDEFFECT_H
