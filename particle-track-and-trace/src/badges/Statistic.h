#ifndef STATISTIC_H
#define STATISTIC_H

class Statistic {
public:
  virtual double getValue() const = 0;

  virtual void resetStatistic();

  virtual ~Statistic() = default;
};

#endif //STATISTIC_H
