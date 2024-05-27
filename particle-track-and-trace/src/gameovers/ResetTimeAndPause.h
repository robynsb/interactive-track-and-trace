#ifndef RESETTIMEANDPAUSE_H
#define RESETTIMEANDPAUSE_H

#include "GameoverCallback.h"

class ResetTimeAndPause : public GameoverCallback {
private:

public:
  void handleGameOver() const override;
};


#endif //RESETTIMEANDPAUSE_H
