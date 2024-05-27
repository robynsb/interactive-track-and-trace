#include <memory>

#include "VesselRouteFactory.h"
#include "../vesselroutes/QuadraticBezierRoute.h"
#include "../vesselroutes/StraightLineRoute.h"

using namespace std;

shared_ptr<Vessels> createVesselLayer(shared_ptr<UVGrid> uvGrid, string datapath) {
  auto vessels = make_shared<Vessels>(uvGrid, datapath);
//  vessels->addRoute(make_shared<QuadraticBezierRoute>(0, 1000000, 900000,
//          // Southend-on-sea
//                                                      0.6833443334080538,
//                                                      51.513525377373554,
//          // Somewhere in the ocean
//                                                      4.278963276069124,
//                                                      53.595354574287875,
//          // Amsterdam
//                                                      4.905113199673045,
//                                                      52.37897444844786
//  ));
//  vessels->addRoute(make_shared<QuadraticBezierRoute>(10000, 1500000, 21000000,
//          // Bremerhaven
//                                                      8.07569380036341, 54.148494844184846,
//          // Sea
//                                                      2.5328328762544854, 55.69646537203329,
//          // Rotterdam
//                                                      4.082281578861821, 52.086017670497306
//  ));
//  vessels->addRoute(make_shared<QuadraticBezierRoute>(50000, 7000000, 1200000,
//          // Atlantic
//                                                      -12.073103195836497, 49.44509691959939,
//          // English Channel
//                                                      1.5406407998556857, 48.89535637039976,
//          // Esbjerg
//                                                      8.27971461540914, 55.40949432441276
//  ));
  auto aroundEngland = make_shared<StraightLineRoute>();
  aroundEngland->addKeyPoint(8000000, -1.024415871291601, 55.76223419453827);
  aroundEngland->addKeyPoint(8000000, 1.2253506038693909, 53.447961325360176 );
  aroundEngland->addKeyPoint(1000000, 2.685305444133438, 52.78721588962486 );
  aroundEngland->addKeyPoint(1000000, 1.2253506038693909, 50.789010333264656 );
  aroundEngland->addKeyPoint(940000, -4.3990655840330914, 49.98021113709513);
  aroundEngland->addKeyPoint(755555, -6.050489911544884, 50.072466183978314);
  aroundEngland->addKeyPoint(1000000,  -4.638402443092771, 51.255700762267395);
  aroundEngland->addKeyPoint(850000,  -5.691484622955362, 51.702871276667466 );
  aroundEngland->addKeyPoint(850000,  -4.8059382444345475, 52.32156156171424 );
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

  auto scandinaviaToFrance = make_shared<StraightLineRoute>();
  scandinaviaToFrance->addKeyPoint(8000000, 12.034919010539786, 66.62125537441796);
  scandinaviaToFrance->addKeyPoint(8000000, 9.127416539123152, 64.12025709576429);
  scandinaviaToFrance->addKeyPoint(8000000, 4.804419443464212, 62.64661273819398);
  scandinaviaToFrance->addKeyPoint(8000000, 3.73323432241598, 60.98473190506101);
  scandinaviaToFrance->addKeyPoint(8000000, 5.072215723726273, 58.19817906060351);
  scandinaviaToFrance->addKeyPoint(8000000, 6.870276462628663, 57.423780892315484);
  scandinaviaToFrance->addKeyPoint(8000000, 8.171001191990904, 54.15680932374468);
  scandinaviaToFrance->addKeyPoint(8000000, 5.378268339925041, 53.72898137694767);
  scandinaviaToFrance->addKeyPoint(8000000, 4.521034926892454, 53.28743778169868);
  scandinaviaToFrance->addKeyPoint(8000000, 2.9568865433121503, 51.559740197228166);
  scandinaviaToFrance->addKeyPoint(8000000, 1.5060821809297569, 50.99251443013628);
  scandinaviaToFrance->addKeyPoint(8000000, -0.4661049173548383, 49.50689629617164);
  scandinaviaToFrance->addKeyPoint(8000000, -1.4181952501162798, 50.019391205163764);
  scandinaviaToFrance->addKeyPoint(8000000, -2.0415877025239912, 48.89219218426543);
  scandinaviaToFrance->addKeyPoint(8000000, -3.49239195540012, 49.033582082972956);
  scandinaviaToFrance->addKeyPoint(8000000, -5.623260701811933, 48.54821867805831);
  scandinaviaToFrance->addKeyPoint(8000000, -2.9068355366670473, 46.98236307264904);
  scandinaviaToFrance->addKeyPoint(8000000, -2.2494398808201295, 44.09349498408996);
  vessels->addRoute(scandinaviaToFrance);

  auto westIrelandToCopenHagen = make_shared<StraightLineRoute>();
  westIrelandToCopenHagen->addKeyPoint(4000000, -8.870830112476956, 54.453738054239466);
  westIrelandToCopenHagen->addKeyPoint(4000000, -8.870830112476956, 54.89230326581597);
  westIrelandToCopenHagen->addKeyPoint(4000000, -7.505610811486317, 55.59643925166461);
  westIrelandToCopenHagen->addKeyPoint(4000000, -6.097051215226138, 55.400045272739604);
  westIrelandToCopenHagen->addKeyPoint(4000000, -5.511957229087296, 54.85489741848255);
  westIrelandToCopenHagen->addKeyPoint(4000000, -5.381936343278664, 54.13757102528025);
  westIrelandToCopenHagen->addKeyPoint(4000000, -5.750328853069787, 53.97220358834105);
  westIrelandToCopenHagen->addKeyPoint(4000000, -5.858679591243647, 53.291181634245135);
  westIrelandToCopenHagen->addKeyPoint(4000000, -6.097051215226138, 52.229034344869945);
  westIrelandToCopenHagen->addKeyPoint(4000000, -5.251915457470032, 51.936064821361256);
  westIrelandToCopenHagen->addKeyPoint(4000000, -4.991873685852767, 51.35787829925067);
  westIrelandToCopenHagen->addKeyPoint(4000000, -3.9950468946532554, 51.30371827361402);
  westIrelandToCopenHagen->addKeyPoint(8000000, -4.948533390583223, 50.662537842698704);
  westIrelandToCopenHagen->addKeyPoint(8000000, -5.44694678618298, 50.359363543958025);
  westIrelandToCopenHagen->addKeyPoint(8000000, -6.703815348999755, 49.64904872099439);
  westIrelandToCopenHagen->addKeyPoint(8000000, -4.103397632827114, 50.08205953483051);
  westIrelandToCopenHagen->addKeyPoint(8000000, -3.2875160422166383, 50.29018864865551);
  westIrelandToCopenHagen->addKeyPoint(8000000, -3.1017853063448113, 50.60200057247842);
  westIrelandToCopenHagen->addKeyPoint(8000000, -2.409516199913458, 50.51082024238017);
  westIrelandToCopenHagen->addKeyPoint(8000000, -1.8860932170019453, 50.51082024238017);
  westIrelandToCopenHagen->addKeyPoint(8000000, -1.0080933746987648, 50.50008154738379);
  westIrelandToCopenHagen->addKeyPoint(8000000, -0.47622808561126134, 50.76247697504748);
  westIrelandToCopenHagen->addKeyPoint(8000000, 0.3764448381639425, 50.634139761722906);
  westIrelandToCopenHagen->addKeyPoint(8000000, 0.8324463709792884, 50.84130876040274);
  westIrelandToCopenHagen->addKeyPoint(8000000, 1.2415149841505717, 51.02066010055547);
  westIrelandToCopenHagen->addKeyPoint(8000000, 1.7793533719002474, 51.07100293572292);
  westIrelandToCopenHagen->addKeyPoint(8000000, 2.424043306590673, 51.17631863950783);
  westIrelandToCopenHagen->addKeyPoint(8000000, 2.918599968818946, 51.303484960874826);
  westIrelandToCopenHagen->addKeyPoint(8000000, 3.3513370482686837, 51.622605818976034);
  westIrelandToCopenHagen->addKeyPoint(8000000, 3.6162781173195433, 51.775866145094646);
  westIrelandToCopenHagen->addKeyPoint(8000000, 3.960701507085661, 52.03739162414143);
  westIrelandToCopenHagen->addKeyPoint(8000000, 4.234473945104883, 52.23794586348571);
  westIrelandToCopenHagen->addKeyPoint(8000000, 4.455258169313933, 52.43221376709419);
  westIrelandToCopenHagen->addKeyPoint(8000000, 4.552403227965916, 52.828866539020936);
  westIrelandToCopenHagen->addKeyPoint(8000000, 4.6672110245546214, 53.21664278211977);
  westIrelandToCopenHagen->addKeyPoint(8000000, 4.940983462573844, 53.50125171063435);
  westIrelandToCopenHagen->addKeyPoint(8000000, 5.912434180957093, 53.57997269887185);
  westIrelandToCopenHagen->addKeyPoint(8000000, 7.113500360654324, 53.783962736935116);
  westIrelandToCopenHagen->addKeyPoint(8000000, 7.678708056333108, 53.86215753840202);
  westIrelandToCopenHagen->addKeyPoint(8000000, 8.279241146181727, 53.96619037503139);
  westIrelandToCopenHagen->addKeyPoint(8000000, 8.650158642852931, 54.07514608719728);
  westIrelandToCopenHagen->addKeyPoint(8000000, 8.429374418643881, 54.35915548828615);
  westIrelandToCopenHagen->addKeyPoint(8000000, 8.049625563346545, 54.748397342980105);
  westIrelandToCopenHagen->addKeyPoint(8000000, 8.393820801285125, 55.222186362227745);
  westIrelandToCopenHagen->addKeyPoint(8000000, 7.858597576813127, 55.60609359306434);
  westIrelandToCopenHagen->addKeyPoint(8000000, 7.8731945749837955, 56.26290902356576);
  westIrelandToCopenHagen->addKeyPoint(8000000, 8.092550050767546, 56.87436096067643);
  westIrelandToCopenHagen->addKeyPoint(8000000, 8.278547689225453, 57.374568566329536);
  westIrelandToCopenHagen->addKeyPoint(8000000, 9.253306836898576, 57.36234475751101);
  westIrelandToCopenHagen->addKeyPoint(8000000, 10.318741254122685, 57.962550081217664);
  westIrelandToCopenHagen->addKeyPoint(8000000, 11.01014018444897, 57.587826697542475);
  westIrelandToCopenHagen->addKeyPoint(8000000, 11.746876749550745, 57.587826697542475);
  westIrelandToCopenHagen->addKeyPoint(8000000, 12.48361331465252, 56.652599812310925);
  westIrelandToCopenHagen->addKeyPoint(8000000, 12.41560686248928, 56.176087213806795);
  vessels->addRoute(westIrelandToCopenHagen);

  auto rotterdamToAtlantic = make_shared<StraightLineRoute>();
  rotterdamToAtlantic->addKeyPoint(2000000, 4.061030022173321, 52.02224874074552);
  rotterdamToAtlantic->addKeyPoint(2000000, 3.449169161342323, 51.73473116385444);
  rotterdamToAtlantic->addKeyPoint(2000000, 2.7551180356235814, 51.422599934609615);
  rotterdamToAtlantic->addKeyPoint(2000000, 1.6501155854661098, 51.06243002869041);
  rotterdamToAtlantic->addKeyPoint(2000000, 1.3761480358402913, 50.41515007645982);
  rotterdamToAtlantic->addKeyPoint(2000000, 0.8099483493277537, 50.006049281589156);
  rotterdamToAtlantic->addKeyPoint(2000000, 0.03370695872126452, 49.71168488133227);
  rotterdamToAtlantic->addKeyPoint(2000000, -0.12154131940003299, 49.55198198187587);
  rotterdamToAtlantic->addKeyPoint(2000000, -0.10327681609164444, 49.373919879482486);
  rotterdamToAtlantic->addKeyPoint(2000000, -0.8612537033897462, 49.433345814569996);
  rotterdamToAtlantic->addKeyPoint(2000000, -1.1443535046697588, 49.49863128945259);
  rotterdamToAtlantic->addKeyPoint(2000000, -1.107824498052983, 49.80607662642066);
  rotterdamToAtlantic->addKeyPoint(2000000, -2.1489011866310985, 49.75890372240223);
  rotterdamToAtlantic->addKeyPoint(4000000, -1.8018756237717257, 49.11756841079647);
  rotterdamToAtlantic->addKeyPoint(4000000, -1.7014208555755919, 48.727531659717705);
  rotterdamToAtlantic->addKeyPoint(4000000, -2.578117014378215, 48.733555303061884);
  rotterdamToAtlantic->addKeyPoint(4000000, -3.062126352050496, 48.93792994870897);
  rotterdamToAtlantic->addKeyPoint(4000000, -3.8109709876944033, 48.82983547077807);
  rotterdamToAtlantic->addKeyPoint(8000000, -4.775647317989541, 48.72196405681305);
  rotterdamToAtlantic->addKeyPoint(8000000, -7.643174337406454, 48.3591841211844);
  rotterdamToAtlantic->addKeyPoint(8000000, -10.69334674229389, 48.35918410419787);
  rotterdamToAtlantic->addKeyPoint(8000000, -12.291490781777837, 48.46829111661448);
  vessels->addRoute(rotterdamToAtlantic);

  auto franceToAroundEnglandToPacific = make_shared<StraightLineRoute>();
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -2.306348465465, 48.874047388812798404);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -2.183056639716997, 49.930373538309034);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -1.3405624970998942, 49.837691873049216);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -0.9706870198533625, 49.505232296671686);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -0.14874151486106746, 49.43846756876905);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 0.34442578813430985, 49.85094300579);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.2074685683762199, 50.14154952120971);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.4951494951235236, 50.95110136349081);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.5362467703731384, 51.350674954470755);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.5567954079979458, 51.949894834430495);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.8855736099948641, 52.566201453638904);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.3102117565002562, 53.08766510989494);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 0.6321067148816137, 53.075321984880624);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 0.303328512884695, 53.0135532604276);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 0.8992390040041089, 53.1739679198049);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.145822655501798, 53.08766510989494);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.9061222476196715, 52.80287699674788);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.8033790594956332, 52.45364397824089);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.7211845089964042, 52.0258214280087);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.3307603941250634, 51.695875725527465);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 0.8992390040041086, 51.529994600453996);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.6389899584971754, 51.37633515890766);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.4044852892062756, 51.11636726810268);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 1.0005937891269976, 50.85080038173055);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, 0.42617032234757923, 50.737332150949136);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -0.1392777777634105, 50.72028815322973);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -0.35468657780569196, 50.777077367238896);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -0.8303810112323974, 50.703237954272254);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -1.0816912779483925, 50.65205014252274);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -1.3958291113433874, 50.5495069855189);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -1.6740654780646684, 50.63497513117402);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -2.086932344812375, 50.5266892696501);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -2.5985282449127953, 50.49815160067008);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -3.199877811697496, 50.6065029897896);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -3.478114178418777, 50.30363775402797);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -3.720449078466344, 50.07377520937487);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -4.283298346871034, 50.264373183060684);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -4.859395029837201, 50.121604585734374);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -5.21248654520356, 49.84677072983163);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -5.955837198538865, 49.88270768170247);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -8.29739153668382, 49.78081684475133);
  franceToAroundEnglandToPacific->addKeyPoint(4000000, -9.70975759814926, 49.89468072833021);
  franceToAroundEnglandToPacific->addKeyPoint(8000000, -11.35846460845027, 49.79900122941537);
  franceToAroundEnglandToPacific->addKeyPoint(8000000, -13.304485188418527, 49.986506961131);
  vessels->addRoute(franceToAroundEnglandToPacific);

  return vessels;
}