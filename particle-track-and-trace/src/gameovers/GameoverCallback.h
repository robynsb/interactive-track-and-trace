#ifndef GAMEOVERCALLBACK_H
#define GAMEOVERCALLBACK_H
#include <memory>

class GameoverCallback {
public:
  virtual void handleGameOver() = 0;

  virtual ~GameoverCallback() = default;
};

#endif //GAMEOVERCALLBACK_H
