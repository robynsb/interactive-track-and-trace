#ifndef GAMEOVERCALLBACK_H
#define GAMEOVERCALLBACK_H

class GameoverCallback {
public:
  virtual void handleGameOver() const = 0;

  virtual ~GameoverCallback() = default;
};

#endif //GAMEOVERCALLBACK_H
