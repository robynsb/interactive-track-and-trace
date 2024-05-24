#include <memory>

#include "VesselRouteFactory.h"
#include "../vesselroutes/QuadraticBezierRoute.h"

using namespace std;

shared_ptr<Vessels> createVesselLayer(shared_ptr<UVGrid> uvGrid, string datapath) {
  auto vessels = make_shared<Vessels>(uvGrid, datapath);
  vessels->addRoute(make_shared<QuadraticBezierRoute>(0, 1000000, 900000,
          // Southend-on-sea
                                                      0.6833443334080538,
                                                      51.513525377373554,
          // Somewhere in the ocean
                                                      4.278963276069124,
                                                      53.595354574287875,
          // Amsterdam
                                                      4.905113199673045,
                                                      52.37897444844786
  ));
  vessels->addRoute(make_shared<QuadraticBezierRoute>(10000, 1500000, 21000000,
          // Bremerhaven
                                                      8.07569380036341, 54.148494844184846,
          // Sea
                                                      2.5328328762544854, 55.69646537203329,
          // Rotterdam
                                                      4.082281578861821, 52.086017670497306
  ));
  vessels->addRoute(make_shared<QuadraticBezierRoute>(50000, 7000000, 1200000,
          // Atlantic
                                                      -12.073103195836497, 49.44509691959939,
          // English Channel
                                                      1.5406407998556857, 48.89535637039976,
          // Esbjerg
                                                      8.27971461540914, 55.40949432441276
  ));
  return vessels;
}