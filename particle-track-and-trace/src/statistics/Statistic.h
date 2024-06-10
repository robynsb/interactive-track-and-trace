#ifndef STATISTIC_H
#define STATISTIC_H

/**
 * A Statistic stores a double that tracks something about the game's state.
 * Statistics are used to check if an Achievement is achieved.
 * Statistics can be used to track the users interaction. This can be used for some future
 * quantitative user study.
 */
class Statistic {
public:
  /**
   * Gets the statistics double.
   */
  virtual double getValue() const = 0;

  /**
   * Resets the statistic, called when game is over.
   * May be left empty if the statistic should not reset when game is over.
   */
  virtual void resetStatistic();

  virtual ~Statistic() = default;
};

#endif //STATISTIC_H
