#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include "ParticleCollisionCallback.h"
#include <SFML/Audio.hpp>
#include <string>

/**
 * SoundEffect is a ParticleCollisionCallback that plays a sound at collision.
 *
 * This is a collision extension, this means it stores a callback itself and calls
 * it before playing a sound.
 */
class SoundEffect : public ParticleCollisionCallback {
public:
  /**
   * Constructor.
   * @param datapath needed to find the audio files.
   * @param callback Callback to call before playing the sound.
   */
  SoundEffect(std::string datapath, const std::shared_ptr<ParticleCollisionCallback> &callback);

  /**
   * Calls callback->handleCollision(index) and then plays sound.
   * @param index to pass to callback.
   */
  void handleCollision(int index) override;
private:
  sf::SoundBuffer buffer;
  sf::Sound sound;
  std::shared_ptr<ParticleCollisionCallback> callback;
};


#endif //SOUNDEFFECT_H
