#include "NorthernFulmar.h"

NorthernFulmar::NorthernFulmar(const std::string &datapath)
  : StaticBadge(datapath + "/NorthernFulmar.png", 0.3, 5.74) {
  setZ(1);
}
