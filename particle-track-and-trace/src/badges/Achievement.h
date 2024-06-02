#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

class Achievement {
public:
  virtual bool isAchieved() = 0;

  virtual ~Achievement() = default;
};

#endif //ACHIEVEMENT_H
