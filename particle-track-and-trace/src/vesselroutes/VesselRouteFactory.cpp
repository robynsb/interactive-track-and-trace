#include <memory>

#include "VesselRouteFactory.h"
#include "../vesselroutes/QuadraticBezierRoute.h"
#include "../vesselroutes/StraightLineRoute.h"

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
  auto aroundEngland = make_shared<StraightLineRoute>();
  aroundEngland->addKeyPoint(1000000, -1.024415871291601, 55.76223419453827);
  aroundEngland->addKeyPoint(1000000, 1.2253506038693909, 53.447961325360176 );
  aroundEngland->addKeyPoint(1000000, 2.685305444133438, 52.78721588962486 );
  aroundEngland->addKeyPoint(1000000, 1.2253506038693909, 50.789010333264656 );
  aroundEngland->addKeyPoint(940000, -4.3990655840330914, 49.98021113709513);
  aroundEngland->addKeyPoint(755555, -6.050489911544884, 50.072466183978314);
  aroundEngland->addKeyPoint(600000,  -4.638402443092771, 51.255700762267395);
  aroundEngland->addKeyPoint(650000,  -5.691484622955362, 51.702871276667466 );
  aroundEngland->addKeyPoint(750000,  -4.8059382444345475, 52.32156156171424 );
  vessels->addRoute(aroundEngland);

  auto aroundNorthEurope = make_shared<StraightLineRoute>();
  aroundNorthEurope->addKeyPoint(1000000, -3.869305057566341, 46.977071966227626 );
  aroundNorthEurope->addKeyPoint(1000000, -4.330393017973213, 47.52068542679078 );
  aroundNorthEurope->addKeyPoint(1000000, -5.3253723009564595, 48.172137561924046 );
  aroundNorthEurope->addKeyPoint(1000000, -4.670142041430908, 48.86333457670226);
  aroundNorthEurope->addKeyPoint(1000000, -2.8500579871932596, 49.07044604281559 );
  aroundNorthEurope->addKeyPoint(1000000, -1.8065431294303416, 49.03863872539217  );
  aroundNorthEurope->addKeyPoint(1000000, -1.9278820663795186, 49.90593531753628  );
  aroundNorthEurope->addKeyPoint(1000000, -0.35047588604022656, 49.63950109958529  );
  aroundNorthEurope->addKeyPoint(1000000, 0.08634428697680903, 49.874666122808904  );
  aroundNorthEurope->addKeyPoint(1000000, 0.1591476491463154, 49.98401968978316   );
  aroundNorthEurope->addKeyPoint(1000000, 1.3482692312482434, 50.83460970615167 );
  aroundNorthEurope->addKeyPoint(1000000, 1.6152148925364325, 51.14013564345633 );
  aroundNorthEurope->addKeyPoint(1000000, 3.1926210728757263, 51.47389432545294 );
  aroundNorthEurope->addKeyPoint(1000000, 4.100525699264113, 52.24234868024254 );
  aroundNorthEurope->addKeyPoint(1000000, 4.446106460283022, 52.49780305510401 );
  aroundNorthEurope->addKeyPoint(1000000, 4.632913145486828, 53.169788254580574 );
  aroundNorthEurope->addKeyPoint(1000000, 4.845193496430541, 53.43871219280083 );
  aroundNorthEurope->addKeyPoint(1000000, 6.127366653965763, 53.61033862212674 );
  aroundNorthEurope->addKeyPoint(1000000, 6.934031885527656, 53.7913035039934 );
  aroundNorthEurope->addKeyPoint(1000000, 8.037175897773787, 53.924143482288194 );
  aroundNorthEurope->addKeyPoint(8000000, 7.907131449180546, 55.535844591983015 );
  aroundNorthEurope->addKeyPoint(8000000, 7.7614260231845575, 57.964450695336325 );
  aroundNorthEurope->addKeyPoint(8000000, 10.345210261573536, 59.106554875216965  );
  vessels->addRoute(aroundNorthEurope);

  return vessels;
}