
#include <algorithm>
#include <random>
#include <iostream>
#include <thread>
#include <random>
#include <time.h>
#include <chrono>
#include <iostream>
#include <bits/stdc++.h>
#include "board.hpp"
#include "engine.hpp"
#include "butils.hpp"

using namespace std;
using namespace chrono;
#define pos(x,y) (((y)<<3)|(x))
#include <unistd.h>

class WEIGHTS{
    public:
    int feature_size;
    int no_of_players;
    int size_of_board;
    vector<double> weights;
    vector<double> weights_static;
    vector<double> weights_backed_dynmaic;


    void read_weights_tour(int btype){
        if(btype==3){
            feature_size=2*10+2*10+2*6*8*8+2;
            no_of_players=10;
            size_of_board=8;
            weights={




0.305267,0.377975,3.5,0.478776,0.303118,0.391267,0.101785,0.100503,0.121595,0.120327,
-0.268594,-0.345456,-3.45264,-0.488087,-0.298775,-0.357965,-0.0971242,-0.0896295,-0.0732727,-0.114265,
0.301663,0.322646,1.13756,0.511581,0.30598,0.331102,0.136569,0.131615,0.127094,0.0868746,
-0.273967,-0.301573,-1.06244,-0.496546,-0.31025,-0.294885,-0.0988821,-0.0571186,-0.0515972,-0.0758276,
-1.7605e-05,0.000930376,-0.00206969,9.17563e-05,0.000321447,-1.61181e-05,0.03599,-2.71753e-05,
0.0395431,0.000995693,0.000766259,-3.85444e-06,1.22896e-06,-2.15783e-07,6.44894e-08,6.71131e-06,
0.000139537,0.0010414,0.00178795,-8.90481e-07,3.75659e-07,1.71049e-08,1.00231e-06,3.98964e-05,
-0.00178289,0.00205723,2.70381e-05,0,0,7.94875e-07,3.37225e-08,4.70905e-07,
-0.000799159,0.0080705,0.000773671,0,0,-0.000155868,-0.000136749,-2.62696e-06,
0.000838071,0.0013059,-2.07879e-05,0.00425829,0.00445366,-0.000410252,5.072e-05,-0.000106943,
0.00229167,0.0110896,0.00297496,0.00625023,0.00418896,-0.0131623,0.00219159,0.000952219,
0.00140235,0.0012743,-0.000117164,-0.0074603,0.0001061,-0.0143347,0.00131139,0.00140535,
2.56379e-06,4.53001e-05,2.31078e-05,-8.65713e-07,0,0,0,0,
0.000274983,-0.000362158,0.000125421,2.92898e-05,-3.71751e-07,3.47157e-05,0,0,
0.000175551,-0.000517712,0.000295547,0.000847764,-0.000887748,0.00433307,-3.03099e-06,-2.14612e-06,
0.0013673,0.00011977,0.000151126,0,0,-1.22763e-05,-8.85511e-06,-2.73663e-06,
-0.000617062,-0.00303788,-0.000818063,0,0,0.000227498,0.000742831,0.000281617,
0.00145419,0.00107234,-4.83205e-06,0.00263425,-0.0025724,0.000707606,-0.000798717,-0.0050996,
0.000435987,-8.54702e-05,-0.000964178,0.0074251,-0.0117454,0.00117664,-0.00044315,-0.000611112,
-0.000984046,0.00318987,0.00292521,0.00098905,0.0247498,0.0111582,0.000785476,-0.00061413,
0,1.0933e-05,0,0.000230514,0,4.56896e-05,0,-1.05343e-07,
-5.30759e-07,0,-0.000113079,0,-0.00198303,0,0.000289794,0,
0,0.00255499,0,0.000190151,0,0.000204698,0,-1.4509e-06,
0.000973706,0,0.000519868,0,0,0,2.47491e-06,0,
0,0.000592739,0,0,0,0.000892154,0,0.000570862,
0.00316453,0,0.00100312,0,-0.00165699,0,-0.000140999,0,
0,0.000667917,0,0.00178026,0,-0.000174994,0,-0.000479346,
0.00051921,0,0.000901209,0,0.00174011,0,-0.000722321,0,
-0.00363401,-0.000855699,-0.00242833,0.00351392,-7.40203e-07,0.000301472,-0.000392749,5.06795e-07,
0.0137539,0.00174413,-0.00147083,5.35292e-05,-9.33393e-06,0.000541074,-3.06763e-06,-0.00263519,
0.00075969,0.0015325,-0.0016056,0.00273251,-3.52487e-05,-0.00201443,0.000216215,-0.000264914,
0.000891349,-6.3215e-05,0.0245944,0,0,-0.00308633,0.000127386,-0.000188322,
-0.0100902,0.00123998,0.00951814,0,0,-0.000200777,0.000909883,6.967e-06,
0.000200544,0.00131914,-0.00325967,0.00511945,-0.00189798,0.000534357,-0.00319361,4.78316e-05,
-1.32536e-06,0.0011738,0.000952364,-0.00510755,0.00040992,5.74217e-05,0.000878996,9.71254e-08,
0.0013222,0.012445,-2.02069e-06,-0.0099221,0.00214052,9.67831e-05,0.000299058,2.23089e-05,
-0.000138607,-1.46967e-05,-0.000151299,0.000712292,0.000676476,2.80659e-05,1.28278e-08,2.12144e-07,
-0.000115798,0.000263555,-0.00193672,0.00052711,0.00015117,-1.73301e-05,-0.000152577,-1.03251e-07,
-0.00580909,-0.000243594,0.0284812,0.00230541,0.000429715,-0.000390027,-8.05109e-06,-7.50226e-05,
0.0011454,0.00139131,0.0220428,0,0,0.000670494,-1.54046e-05,-2.38556e-06,
0.00771219,0.000612287,0.0293665,0,0,-0.000118178,-3.01097e-05,-0.00157488,
0.0304543,0.00287513,-0.00299531,5.28161e-05,-2.88e-07,-1.42158e-05,-0.000186154,-3.54357e-06,
0.00144921,0.000738564,0.00733256,1.92966e-05,-1.27538e-05,-2.87946e-05,3.71581e-05,0,
-0.0104812,-0.0049363,-0.00058178,-4.32981e-05,-3.22532e-06,-2.63375e-05,0,-1.98365e-09,
0,0,0.01,0.01,0.02,0.03,0,0,
-9.62857e-08,-9.02101e-07,0.00999972,0.00999998,0.0199977,0.0299996,0,0,
2.30948e-07,-1.83062e-05,0.0099785,0.00989537,0.0202182,0.0299984,0,0,
0,1.77322e-05,0.00921307,0,0,-4.07838e-07,0,0,
7.46873e-06,4.60958e-09,0.0102537,0,0,8.28182e-11,0,0,
1.02285e-08,0.000427284,6.94083e-06,2.53437e-07,0.00163069,-0.0227977,0,0,
0,0.000372761,-6.34814e-06,-0.000136225,0.00403918,0,0,0,
0,9.56086e-06,0.00171849,0.00204842,0,0,0,0,
9.52166e-05,0.00902477,0.00122733,-0.00362183,0.000519881,-0.00283088,-0.00216043,0.000130641,
-0.00107629,0.00333496,0.0128761,0.00028016,0.0011228,6.80388e-05,-5.65064e-05,0.00182108,
3.26657e-05,-0.0036933,0.000486121,-5.30181e-05,0.000545761,-0.000507057,1.17369e-06,0.000783638,
0.000642474,-0.000531479,-8.56688e-05,0,0,9.6783e-05,-1.86714e-06,6.14593e-05,
-0.00195693,2.13793e-05,-8.08608e-06,0,0,0.00131105,1.90884e-05,0.000491106,
3.05284e-05,0.000626784,1.47964e-06,-2.09025e-05,3.00733e-05,-0.000208212,8.93066e-06,0.000275126,
1.68026e-05,0.000110736,4.81305e-05,0.000722992,9.94949e-06,-0.000795044,-5.09001e-05,-0.0348307,
-2.9439e-05,-0.0360129,0.000420357,0.000336624,0.000222018,0.000279717,0.00167965,-0.000832347,
0.000272307,0.000440406,-0.00245769,-0.00721745,0.00463982,-0.00105244,-0.00249513,0.000588211,
0.00391887,0.00215946,-0.010966,0.0206782,-0.000797342,-6.20482e-05,0.000245462,0.00146883,
0.00921455,0.00659538,0.00295977,-8.49176e-05,-0.0039605,-0.00280056,-0.000331989,-0.000219967,
0.0241761,-0.00152,-0.00255475,0,0,-0.00142134,-0.00246168,0.000288106,
-5.89674e-05,-0.000534017,7.67133e-05,0,0,-0.00162704,-3.00934e-05,-4.08372e-06,
8.64647e-06,-2.46718e-05,0.000145491,-1.30272e-06,0.000646988,1.3407e-05,2.08091e-05,-6.4971e-08,
-6.9487e-07,2.67059e-06,0.000562283,6.78229e-05,0.000264493,-7.44077e-05,-2.69406e-06,0,
0,-1.16399e-07,0.000498046,0.000488393,1.47562e-05,-0.000107584,0,0,
0,-0.000426334,0,-0.000770473,0,0.000203912,0,0,
0.00519334,0,-0.0196422,0,0.00137646,0,-0.000299724,0,
0,0.00091907,0,0.0125452,0,-1.4315e-05,0,0.00352157,
1.35846e-05,0,0.00315593,0,0,0,0.00046928,0,
0,-8.83803e-05,0,0,0,3.2089e-05,0,0.000124299,
2.69007e-06,0,3.14282e-05,0,-0.00269258,0,-1.73898e-05,0,
0,-8.1593e-06,0,0.000486571,0,9.69949e-05,0,-0.000748471,
0,0,-3.14369e-05,0,-2.05077e-05,0,4.46394e-05,0,
0.000396784,-0.000211661,0.000231759,-0.000685658,0.00201194,0.00091257,-0.00257717,-0.00329331,
-0.000501759,-0.000830411,0.00275439,-0.00376944,0.00441345,-0.00121156,-0.0135972,-0.00452096,
0.00147255,0.000285233,-0.00194674,0.00011813,0.00280409,0.00229761,-0.00618631,-0.00260119,
0.000303717,-0.00158673,0.00235457,0,0,0.000413335,-0.00127179,-0.000791034,
0.000325462,0.000318813,0.00262962,0,0,-1.71458e-05,0.00127481,-0.00616542,
4.3663e-05,0.00161201,0.00360808,0.00253474,0.0025963,-0.00364509,0.013918,0.00400875,
5.73008e-05,0.00155055,9.48247e-05,0.000651022,8.54583e-05,0.00123444,-0.00554388,0.000147342,
2.29369e-06,6.08075e-05,-0.00411393,-4.50916e-05,0.00305162,0.000528908,-0.00116293,6.01307e-05,
0,-1.33464e-05,7.04729e-06,-1.79735e-05,-0.0013338,0.00681975,-0.00512457,0.00174438,
-2.80069e-07,5.9987e-05,0.000130586,-0.0115312,0.000816143,0.00988691,-4.44979e-06,0.000626736,
-0.000563402,-0.000152291,0.0132344,0.00131949,-0.000588532,-0.000490396,0.00337665,-0.00150696,
2.66213e-06,-0.00156212,1.3958e-05,0,0,0.0302014,0.00112806,-0.00347912,
0.000433714,0.000780121,9.35302e-06,0,0,0.00236747,0.00297602,0.000615916,
-0.00103928,-0.00254354,0.000534289,0.00246163,-0.00134446,-0.00120339,-0.00643317,0.0035731,
0.000158157,-0.0012581,0.0176259,0.00459878,-0.00131249,-0.00128078,-0.00138754,0.00101329,
0.0033633,3.88738e-07,0.00130336,0.000197388,-0.00261477,-0.00028934,1.72672e-06,0,
0,-5.48421e-06,-1.0296e-05,-9.39178e-07,5.42872e-07,0,0,0,
0,0,-3.54872e-06,4.59212e-07,0,0,0,0,
0,-8.43228e-07,-1.90062e-06,0,0,0.00600724,0,0,
-1.70581e-08,-4.61187e-06,-2.13283e-05,0,0,0.000205177,0.0032091,0,
5.13602e-08,-1.98861e-05,8.53452e-05,0,0,-0.01405,0.000810085,0.000215099,
6.5655e-05,0.00165123,-0.0293669,-0.00949484,0.00770648,0.00617003,-0.00314734,2.28214e-05,
9.34059e-05,7.60245e-07,-0.0289984,-0.00763566,0.00093367,0.000299486,0.000510781,0.00570193,
7.17106e-05,0.000747425,-0.0278611,-0.00992388,0.000350238,-3.31726e-05,-0.000134973,2.46649e-05,
1.14423,
-1.1 





            };


        }
        else if(btype==2){
            feature_size=2*8+2*8+2*5*8*8+2;
            no_of_players=8;
            size_of_board=8;
            weights={




                   0.227055,0.301342,3.59303,0.344787,0.119559,0.0885675,0.0800716,0.21312,
-0.174707,-0.305102,-3.44288,-0.336679,-0.124332,-0.170518,-0.0677384,-0.25051,
0.322494,0.457007,2.59035,0.416226,0.0764846,0.0653015,-0.0884437,-0.0503415,
-0.453194,-0.527892,-2.49112,-0.462518,-0.260269,-0.0682199,0.0528116,-0.119609,
0.00911499,-0.00178081,0.0064215,0.0181765,0.0095412,0.00163105,0.0689087,-0.012792,
0.0745968,0.0105747,-0.000603229,-0.00971219,0.00090574,-0.0189269,0.0001559,0.00598135,
0.00876889,-0.000220438,0,0,0,0,-1.10608e-05,0.000121064,
0.00661681,-0.0018416,0,0,0,0,1.01678e-05,0.00453248,
0.0195236,0.000307106,0,0,0,0,0.000401255,-0.000697501,
0.00848905,-0.00195529,0,0,0,0,0.00235463,0.00561338,
0.0177433,0.00214612,0.0159398,0.00428565,0.0865358,0.0761244,0.0272219,0.0282893,
0.0232315,0.0311224,0.00850617,0.0223196,0.0309189,0.10754,0.0311344,0.0596185,
0.00659114,-0.0108115,-0.0064179,-0.00219589,1.28112e-05,-0.000112514,-0.0122769,-0.00258216,
-0.00379943,-0.0167219,-0.0222395,0.0368651,-0.00046441,0.000845498,-0.0256977,0.000537594,
-0.0142708,-0.00460433,0,0,0,0,-0.0016849,-0.00327247,
-0.025621,-0.00617819,0,0,0,0,-0.0271216,-0.00340308,
-0.00941046,0.011878,0,0,0,0,-0.0338194,-0.00438691,
0.0106752,0.00440031,0,0,0,0,0.0245734,-0.0121989,
0.0322806,-0.00734782,0.0500703,0.122173,0.0200835,-0.0152071,-0.0106364,-0.0183654,
0.00259982,0.00191192,-0.0062345,0.00119575,0.0223321,-0.000777538,-0.0100019,-0.022176,
0.0112301,0,0.0156791,0,-0.00578949,0,-0.00188901,0,
0,0.0105911,0,-0.0141637,0,-0.0014942,0,-0.00100345,
0.0152257,0,0,0,0,0,0.000666855,0,
0,0.0102847,0,0,0,0,0,-0.0202796,
0.0233292,0,0,0,0,0,-0.00120932,0,
0,0.0468847,0,0,0,0,0,-0.0154541,
-0.00555734,0,0.0179988,0,0.00740009,0,-0.00228218,0,
0,0.00238015,0,0.0615494,0,-0.0214065,0,-0.00105024,
-0.0266277,0.000932774,0.0011186,0.00314289,0.0012441,0.0063926,-0.004357,0.00153124,
0.000157044,-0.00910703,-0.0518017,0.00336382,0.0162641,0.00628107,0.000981319,-0.000338105,
0.00403152,0.041022,0,0,0,0,3.88561e-06,-0.000658348,
0.0145228,0.0564878,0,0,0,0,-3.79406e-05,-6.55722e-06,
-0.0084375,0.0576747,0,0,0,0,0.000122626,0.00238652,
0.0400964,-0.010159,0,0,0,0,0.000271883,2.91243e-07,
0.0737712,-0.0463353,-0.0143799,-0.00074525,-0.000874375,-0.00143711,-7.98465e-07,-1.64195e-06,
0.0139557,0.0485073,-0.0381696,-7.68428e-05,-0.00100886,-0.000904504,1.71639e-06,0.000219822,
-0.00327062,0.00261342,-0.00396718,0.00312008,0.000305123,0.0533727,0.00737668,-1.2151e-06,
-0.000900985,-0.00691928,0.000544915,0.00250252,0.0112729,0.0521716,0.00318997,-0.00148706,
-0.00100761,0.0106173,0,0,0,0,0.00128983,-5.23641e-06,
-0.00354798,-0.00396344,0,0,0,0,-2.42436e-06,-0.000723457,
-0.0232094,-0.00825443,0,0,0,0,-0.000164577,0.000382333,
-0.0181514,-0.0225517,0,0,0,0,-1.70241e-07,-0.00319828,
-0.00258047,0.00500481,-0.00578289,0.025239,0.0498925,0.0378934,-9.91296e-05,-1.82803e-08,
-0.000815809,-0.00440269,0.0254367,0.0210102,0.0756092,0.0502969,-1.15839e-08,-9.83868e-09,
-0.0211029,0.00827315,-0.0212663,0.0579917,0.0351532,0.0157559,-0.0273614,-0.0429372,
-0.0111489,0.0298885,0.00380084,-0.0254636,0.0786571,0.0261972,0.000548497,0.00159077,
-0.00153098,0.041401,0,0,0,0,0.00100381,0.00359767,
-0.00819823,0.000253125,0,0,0,0,-0.00314262,0.00714112,
-0.00106045,7.28364e-05,0,0,0,0,-0.0050649,-0.014923,
-0.00224669,5.86233e-06,0,0,0,0,-0.000375858,-0.00704108,
0.00248043,0.00163665,-6.04569e-05,-0.00304333,0.00183851,0.00102261,-0.00075458,-0.0808011,
0.00150665,-0.0879079,-0.00382431,0.00470848,-0.0132951,-0.020059,0.00328767,0.00361727,
-0.00114496,0.00176366,0.00149925,0.00620927,-0.0147574,0.0596663,0.0182079,0.0244104,
-0.0145734,-0.00356246,0.0138927,0.0257156,-0.0834206,-0.0389913,0.000592127,-0.0151438,
0.0103555,-0.000281374,0,0,0,0,0.00599154,-0.0321256,
8.9041e-05,0.0039402,0,0,0,0,-0.0039074,0.0143932,
0.000376234,0.00296557,0,0,0,0,-0.00240619,-0.00344155,
-0.00306579,-0.00629571,0,0,0,0,0.00151685,-0.000388231,
-0.000212281,-0.00190599,0.027909,0.0131353,-0.00188549,0.00419484,0.000775238,-0.000876349,
-0.0019752,7.29317e-05,0.00534117,-0.000893057,-0.00310928,-0.000535543,0.000858603,-2.52644e-06,
-0.00102337,0,0.0322743,0,0.0142235,0,-0.00251044,0,
0,0.017637,0,0.0299945,0,0.0380637,0,0.0044671,
-0.0244982,0,0,0,0,0,-0.0243212,0,
0,0.00142475,0,0,0,0,0,0.0147428,
-0.00907998,0,0,0,0,0,0.0743299,0,
0,0.0151016,0,0,0,0,0,0.08141,
-0.00660107,0,0.00690518,0,0.0347806,0,0.000890344,0,
0,-0.00448348,0,0.0222436,0,-0.00967007,0,-0.00681196,
-2.37384e-09,0,0.0983445,0.0640004,0.0198281,0.0247964,-0.00663844,-0.00104658,
-4.868e-09,4.16279e-07,0.0814088,0.0664873,0.0357731,0.000909711,0.0134175,-0.00942364,
-1.33141e-06,5.72483e-05,0,0,0,0,0.011736,-0.0142307,
0.00277427,0.000203568,0,0,0,0,-0.00879853,0.0278514,
6.09211e-05,-0.000101309,0,0,0,0,0.00155439,0.00488801,
-0.000360547,5.55957e-05,0,0,0,0,0.00747254,0.0182799,
-3.168e-05,-0.00260411,-0.00265564,-0.0227104,0.0163566,-0.0373794,0.00596627,-0.000688881,
-4.67492e-06,-1.698e-06,-0.00759744,-0.0109144,-7.66359e-05,-0.022783,-0.00307956,6.5306e-07,
-4.96239e-05,-4.90999e-05,-8.94825e-05,-0.00223829,3.05753e-05,-0.0656033,0.00910573,-0.00462226,
-2.33355e-05,0.000461055,-0.00235143,-0.000316019,-0.000239833,0.047907,-0.0145236,-0.00411582,
0.000918542,5.03884e-05,0,0,0,0,0.057202,0.103509,
0.000630669,0.00253545,0,0,0,0,0.126655,0.00547708,
0.00141422,-1.54617e-05,0,0,0,0,0.014542,0.112093,
-0.000190936,0.000963377,0,0,0,0,0.00599361,-0.00815635,
0.00342334,-0.0265884,-0.00757395,-0.00385579,-0.00846491,0.0271704,-0.00851687,0.0176068,
-1.17366e-05,-0.0295502,-0.00515403,-0.0168678,0.0219135,-0.0109781,-0.00451247,0.000964772,
1.09764,
-1 





            };

        }
        else{
            feature_size=2*6+2*6+2*4*7*7+2;
            no_of_players=6;
            size_of_board=7;
            weights={

0.277783,0.411052,3.5,0.483358,0.0793826,0.0954191,
-0.295405,-0.385283,-3.49252,-0.495694,-0.113779,-0.0998577,
0.283574,0.340117,0.0859627,0.497842,0.0832276,0.0948466,
-0.30762,-0.312068,-0.114038,-0.458165,-0.142675,-0.124401,
0.00179044,-0.000651976,-0.000869683,-0.00274242,-0.000944874,0.0354974,0.000634795,
0.051064,-0.000292249,0.000394592,-4.69183e-06,-6.75222e-06,0.000298891,0.00036881,
0.0029869,3.11e-05,0,0,0,0.00011027,-1.18206e-05,
0.00252084,6.41998e-05,0,0,0,0.00136839,-0.000243998,
0.00318395,-0.000505692,0,0,0,0.00797417,-0.000132374,
0.0171902,-0.000645003,-0.00145769,-0.000825585,-0.000820984,-0.00256602,0.0004834,
0.00128888,-0.000603663,-0.00159937,-0.0036122,7.11092e-05,-0.0118658,-0.0032432,
0,0,0,0,0,0,0,
-2.34511e-07,-5.159e-08,0,0,0,0,0,
-3.59609e-06,-5.15452e-06,0,0,0,0,-1.88664e-05,
-0.000133769,8.31211e-05,0,0,0,0.00981652,4.42393e-07,
0.000887134,-0.0135175,0,0,0,0.00429276,-1.64326e-05,
0.000256907,-0.0128926,-0.0101999,-0.00798048,0.0472972,-0.000641073,-1.25019e-05,
-0.0014662,-0.0228482,-0.00878888,0.00553419,-0.00332455,-0.000344401,-1.38056e-05,
0,-0.00332421,0,0.000434786,0,9.20792e-07,0,
-0.000326021,0,0.000930832,0,-1.9923e-05,0,-7.26175e-07,
0,0.0299968,0,0,0,1.83204e-05,0,
-0.00424189,0,0,0,0,0,-0.000205719,
0,0.000589157,0,0,0,-2.38839e-05,0,
-0.00521804,0,-0.00565276,0,5.28098e-05,0,-2.82808e-07,
0,-0.00686531,0,-0.0083107,0,-2.59235e-07,0,
-0.00200622,-0.00338678,-0.0102423,0.00054505,0.0325241,1.1545e-06,1.18553e-07,
-0.00358612,-0.00239771,-0.000584933,0.00130439,0.0288871,-1.76742e-06,9.87345e-06,
-0.0079742,0.00831825,0,0,0,-1.30967e-06,-0.000101365,
0.00820602,0.00060255,0,0,0,-1.48589e-05,-6.84108e-05,
-0.00242431,0.0228483,0,0,0,-4.35818e-06,0.00126504,
0.00240603,-0.00671075,-0.00160788,-6.37313e-05,1.97359e-07,-0.000526657,-1.09662e-05,
-0.00139865,-0.0146316,-0.0109665,-3.68279e-10,-9.12864e-05,-7.55958e-08,-3.87731e-05,
0.00117718,-0.00205584,0.0124522,0.0177626,-0.000555459,-0.000587691,-0.00225829,
-0.00178428,4.34717e-05,-0.00286853,-0.00855489,-0.00123416,-0.00110866,-0.00250495,
-0.00175527,-0.00123441,0,0,0,0.000121445,-0.00350587,
0.00127728,0.000187124,0,0,0,3.35025e-05,-0.000207189,
-0.000947221,4.33626e-05,0,0,0,-2.46556e-05,-0.00224924,
0.000116816,0.000930111,1.69628e-05,3.19829e-05,-1.96714e-06,-0.00340106,-0.0453533,
0.000333032,-0.0338772,0.00103754,0.000223384,-0.000289743,-0.00439737,-0.00472838,
-2.05657e-05,-0.00361641,0.0331798,0.00309,-0.00779156,-0.00547377,-0.00286343,
-0.00203176,0.00818946,0.00664927,-0.0156122,-0.0030969,-0.00797731,-0.0109092,
-0.000991342,0.00901672,0,0,0,0.000141264,-0.00377301,
-1.15897e-06,-0.000548238,0,0,0,-0.00618301,-0.00102658,
-6.83152e-08,-3.89246e-08,0,0,0,-0.000495331,-0.000890456,
3.03307e-10,7.28134e-08,0.0013548,0.000389758,-0.00168803,0.00123821,-0.0010926,
3.58554e-07,3.34248e-06,3.40555e-05,1.10095e-05,-0.000835137,0.000700429,-0.00112096,
0,-0.00166046,0,-0.000197024,0,3.10015e-05,0,
-0.000827796,0,0.000290177,0,0.00914197,0,0.030974,
0,-0.00380183,0,0,0,0.0141908,0,
0.000132067,0,0,0,0,0,-0.00362438,
0,-0.00177852,0,0,0,2.3339e-05,0,
-0.00052056,0,-9.36807e-05,0,-5.27612e-05,0,-0.000272496,
0,-4.98523e-06,0,-0.000103779,0,-9.0932e-06,0,
-3.96148e-07,0,0.000555409,-2.55608e-06,0.0492597,0.00351666,-0.00234006,
-2.18658e-09,-2.68001e-05,-3.97109e-06,-2.80742e-05,0.00695555,-0.00452415,-0.000719188,
-0.00294262,0,0,0,0,-0.0265464,-0.00237995,
-2.90141e-07,-6.24079e-05,0,0,0,-0.00532396,-0.0176523,
-0.00279381,-1.20008e-05,0,0,0,-0.00369963,-0.00256166,
2.00507e-05,9.10789e-05,-0.0297864,-0.000674384,-0.00476079,-0.0120211,-6.20994e-05,
-2.82167e-06,1.94395e-05,-0.0302315,-0.0364679,-0.00150943,-8.27784e-05,-0.000273065,
1.00662,
-1 



            };

        }
        weights_static=weights;
        

        

    }












    



    double sigmoid(double x){
    return (1/(1+exp(-x)));
    }






};

double sigmoid(double x){
    return (1/(1+exp(-x)));
}


int create_pos(int j, int i, int color, int board_size){
    if(color==1){
        return pos(board_size-1-j,board_size-1-i);
    }
    else{
        return pos(j,i);
    }
}
vector<int> get_features(Board state,WEIGHTS* weight_ob){
    vector <int> features(weight_ob->feature_size,0);
    int k=0;
    int color=0, adv_color=0;
    if(state.data.player_to_play==WHITE) {adv_color=1;color=0;}
    else {color=1;adv_color=0;}
    U8* peice_pos=(U8*) &(state.data);

    vector <int> peices_under_consideration;
    if(state.data.board_type==1){
        peices_under_consideration={0,1,2,3,6,7};
    }
    else if(state.data.board_type==2){
        peices_under_consideration={0,1,2,3,6,7,8,9};
    }
    else{
        peices_under_consideration={0,1,2,3,4,5,6,7,8,9};
    }

    // threat_to_adversary
    state.flip_player_();
    for(int i:peices_under_consideration){
        if(state.under_threat(peice_pos[i+adv_color*10]) && 
        (state.data.board_0[peice_pos[i+adv_color*10]]==PAWN_BISHOP || state.data.board_0[peice_pos[i+adv_color*10]]==PAWN_ROOK
        || state.data.board_90[peice_pos[i+adv_color*10]]==PAWN_BISHOP || state.data.board_90[peice_pos[i+adv_color*10]]==PAWN_ROOK
        || state.data.board_180[peice_pos[i+adv_color*10]]==PAWN_BISHOP || state.data.board_180[peice_pos[i+adv_color*10]]==PAWN_ROOK
        || state.data.board_270[peice_pos[i+adv_color*10]]==PAWN_BISHOP || state.data.board_270[peice_pos[i+adv_color*10]]==PAWN_ROOK)
        )
        {
            features[k]=2.7;
        }
        else if(state.under_threat(peice_pos[i+adv_color*10]) && peice_pos[i+adv_color*10]!=DEAD)
            features[k]=1;
        
        k++;
    }
    state.flip_player_();
    // threat_to_player 
    for(int i:peices_under_consideration){
        if(state.under_threat(peice_pos[i+color*10]) && 
        (state.data.board_0[peice_pos[i+color*10]]==PAWN_BISHOP || state.data.board_0[peice_pos[i+color*10]]==PAWN_ROOK
        || state.data.board_90[peice_pos[i+color*10]]==PAWN_BISHOP || state.data.board_90[peice_pos[i+color*10]]==PAWN_ROOK
        || state.data.board_180[peice_pos[i+color*10]]==PAWN_BISHOP || state.data.board_180[peice_pos[i+color*10]]==PAWN_ROOK
        || state.data.board_270[peice_pos[i+color*10]]==PAWN_BISHOP || state.data.board_270[peice_pos[i+color*10]]==PAWN_ROOK)
        )
        {
            features[k]=2.7;
        }
        else if(state.under_threat(peice_pos[i+color*10]) && peice_pos[i+color*10]!=DEAD)
            features[k]=1;
        k++;
    }
    // player_count
    for(int i:peices_under_consideration){
        if(
        (state.data.board_0[peice_pos[i+color*10]]==PAWN_BISHOP || state.data.board_0[peice_pos[i+color*10]]==PAWN_ROOK
        || state.data.board_90[peice_pos[i+color*10]]==PAWN_BISHOP || state.data.board_90[peice_pos[i+color*10]]==PAWN_ROOK
        || state.data.board_180[peice_pos[i+color*10]]==PAWN_BISHOP || state.data.board_180[peice_pos[i+color*10]]==PAWN_ROOK
        || state.data.board_270[peice_pos[i+color*10]]==PAWN_BISHOP || state.data.board_270[peice_pos[i+color*10]]==PAWN_ROOK)
        )
        {
            features[k]=2.7;
        }
        else if(peice_pos[i+color*10]!=DEAD)
            features[k]=1;
        k++;
    }
    // adversary_count
    for(int i:peices_under_consideration){
        if(
        (state.data.board_0[peice_pos[i+adv_color*10]]==PAWN_BISHOP || state.data.board_0[peice_pos[i+adv_color*10]]==PAWN_ROOK
        || state.data.board_90[peice_pos[i+adv_color*10]]==PAWN_BISHOP || state.data.board_90[peice_pos[i+adv_color*10]]==PAWN_ROOK
        || state.data.board_180[peice_pos[i+adv_color*10]]==PAWN_BISHOP || state.data.board_180[peice_pos[i+adv_color*10]]==PAWN_ROOK
        || state.data.board_270[peice_pos[i+adv_color*10]]==PAWN_BISHOP || state.data.board_270[peice_pos[i+adv_color*10]]==PAWN_ROOK)
        )
        {
            features[k]=2.7;
        }
        else if(peice_pos[i+adv_color*10]!=DEAD)
            features[k]=1;
        k++;
    }
    // ROOKS
    
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[0+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[1+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // KING
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[2+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // BISHOP
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[3+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // KNIGHTS   in case of board 3 ONLY
    if(state.data.board_type==3){
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[4+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[5+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
                k++;
            }
        }
    }
    // PAWNS T1
    if(state.data.board_type==1){
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[6+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[8+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[9+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
        }
    }
    else if(state.data.board_type==2){
        // PAWNS T1
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[6+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }

        // PAWNS T2
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[8+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[9+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }
    }

    else if (state.data.board_type==3){
        // PAWNS T1
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[6+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[8+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }

        // PAWNS T2
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[9+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }
    }

    


    // ADV ROOKS
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[0+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[1+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // ADV KING
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[2+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // ADV BISHOP
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[3+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // ADV KNIGHTS   in case of board 3 ONLY
    if(state.data.board_type==3){
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[4+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[5+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
                k++;
            }
        }
    }

    // ADV  PAWNS T1
    if(state.data.board_type==1){
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[6+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[8+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[9+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
        }
    }
    else if(state.data.board_type==2){
        // ADV PAWNS T1
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[6+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }

        // ADV PAWNS T2
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[8+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[9+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }
    }

    else if (state.data.board_type==3){
        // ADV PAWNS T1
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[6+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[8+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }

        // ADV PAWNS T2
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[9+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }
    }


    if(state.get_pseudolegal_moves_for_piece(peice_pos[2+adv_color*10]).size()<=5 && state.under_threat(peice_pos[2+adv_color*10])){
            features[k]+=1;
            k++;
    }
    if(state.get_pseudolegal_moves_for_piece(peice_pos[2+color*10]).size()<=5 && state.under_threat(peice_pos[2+color*10])){
            features[k]+=1;
            k++;
    }



    return features;

}

double evaluation(Board state,WEIGHTS* weight_ob, PlayerColor player){
    vector<int> features= get_features(state,weight_ob);
    double eval=0;
    for(int fs=0;fs<features.size();fs++){
        if(player==BLACK){
            eval=eval+weight_ob->weights_static[fs]*features[fs];
        }
        else{
            eval=eval+weight_ob->weights[fs]*features[fs];
        }
    }
    return eval;

}



// Defining MCTS Node
struct MCTSNode {
    int visits;
    double totalScore;
    U16 move_done;
    MCTSNode* parent;
    std::vector<MCTSNode*> children;
    Board board;
    PlayerColor player;
    WEIGHTS* weight_ob;
    //Constructor
    MCTSNode(Board st, PlayerColor player, WEIGHTS* ob) : visits(0), totalScore(0.0),move_done(0), parent(nullptr), board(st), player(player), weight_ob(ob) {children.resize(0, nullptr);}
};

//MCTS Function

MCTSNode* selectNode(MCTSNode* root, int curr_depth, double exploration_factor){
    root->visits+=1;
    double parent_visit = root->visits;
    double Max_value = INT_MIN;
    // double exploration_factor = 0.0075; //EXPLORATION FACTOR
    MCTSNode* choosenode= root->children[0];
    for(auto x:root->children){
        double curr_visits = x->visits;
        double total = x->totalScore;
        // if(curr_visits==0){
        //     choosenode=x;
        //     return choosenode;
        // }
        double value;
        if(root->board.data.player_to_play==root->player){
            value = (total+0.0001)/(double)(curr_visits+0.001) + exploration_factor*sqrt(log(parent_visit))/(curr_visits+0.001);
        }
        else{
            value = 1 - (total+0.0001)/(double)(curr_visits+0.001) + exploration_factor*sqrt(log(parent_visit))/(curr_visits+0.001);
        }
        if(value >= Max_value){
            choosenode = x;
            Max_value = value;
        }
    }
    // cout<<endl;
    return choosenode;
}

void expandNode(MCTSNode* node){
    if(node->children.size()!=node->board.get_legal_moves().size()){
        node->children.resize(0);
        for(auto x:node->board.get_legal_moves()){
            Board copy = Board((node->board));
            copy.do_move_(x);
            MCTSNode* childnode = new MCTSNode(copy,node->player, node->weight_ob);
            childnode->parent = node;
            childnode->move_done = x;
            node->children.push_back(childnode);
        }
    }
    else{
        // Node already Expanded
    }
}

double utility(MCTSNode* node){
    U8* peice_pos=(U8*) &(node->board.data);
    int adv_color=1;
    if(node->player==WHITE){
        adv_color=1;   
    }
    else adv_color=0;

    if(node->board.get_legal_moves().size()==0 && node->board.data.player_to_play==node->player){
        return 0;
    }
    else if(node->board.get_legal_moves().size()==0 && node->board.data.player_to_play!=node->player) {
        return 1;
    }

    if(node->board.data.player_to_play==node->player){
            return sigmoid(evaluation(node->board,node->weight_ob, node->player));
    }
    else{
            return 1-sigmoid(evaluation(node->board,node->weight_ob, node->player));
    }
}

void backpropagate(MCTSNode* node , double score, int depth, int simulations){
    int iter=0;
    auto leafnode= node;
    // cout<<"Laef "<<leafboard.data.player_to_play<<endl;
    // double lr=0.0000000005*depth*depth*depth*simulations;
    double lr=0.00000000009*depth*depth*depth*simulations;
    while(node != nullptr){
        // if(node->player==WHITE && node->board.data.player_to_play==WHITE)
        //         node->weight_ob->update_weights(score,utility(node), get_features(node->board,node->weight_ob), lr);
        node->totalScore += score;
        // cout<<node->totalScore<<endl;
        node = node->parent; 
    }
}






void Engine::find_best_move(const Board& b) {

    auto start= high_resolution_clock::now();
    auto player=b.data.player_to_play;
    // If WHITE WTS are to be updated, use 0 as DYNAMIC PLAYER; 1 as STATIC pLAYER
    WEIGHTS weight_ob;
    cout<<weight_ob.weights.size()<<endl;



    // TUNE
    weight_ob.read_weights_tour((int)b.data.board_type);
    // weight_ob.read_weights((int)b.data.board_type,"0");
    // weight_ob.read_weights((int)b.data.board_type,"1");
    U16 best_action = 0;
    auto moveset = b.get_legal_moves();
    if (moveset.size() == 0) {
        std::cout << "Could not get any moves from board!\n";
        std::cout << board_to_str(&b.data);
        this->best_move = 0;
    }
    else{
        
        
        Board copy=Board(b);
        cout<<endl;
        MCTSNode* root = new MCTSNode(copy,player, &weight_ob);
        
        int simulations;
        // IDA*
        bool search=true;
        int depth=2;
        double exploration_factor;

        // TUNE
        double init_exp=0.09;
        int TL_DEPTH=6;


        // TUNE
        int sim_count=125;
        if(copy.data.board_type==3){
            sim_count=67;
        }

        // TUNE
        if(time_left.count()<copy.data.board_type*100000/3 && time_left.count()>copy.data.board_type*40000/3){
            TL_DEPTH=4;init_exp=0.05;
        }
        else if(time_left.count()<copy.data.board_type*40000/3){
            TL_DEPTH=2; init_exp=0.02;
        }
        else{
            TL_DEPTH=6;
        }
        while(search && depth<=TL_DEPTH){
                cout<<"DEPTH ............."<<depth<<endl;
                simulations=sim_count*depth;
                // SIMULATIONS
                for(int i=0;i<simulations;i++){
                    int curr_depth=0;
                    MCTSNode* childNode=root;
                    expandNode(childNode);
                    while (!childNode->children.empty() && (curr_depth<depth)) {
                        exploration_factor=init_exp/(curr_depth+1);
                        MCTSNode* selectedNode = selectNode(childNode, curr_depth,exploration_factor);
                        childNode=(MCTSNode*)selectedNode;
                        expandNode(childNode);
                        curr_depth++;
                    }
                    double playoutResult = utility(childNode);
                    // cout<<"Result of this Simulation "<<i<<" "<<playoutResult<<"-->"<<childNode->visits<<" "<<endl;
                    childNode->visits+=1;
                    backpropagate(childNode, playoutResult, depth, i);
                }
                
                // cout<<endl;
                MCTSNode* bestChild = root->children[0];
                for (MCTSNode* child : root->children) {
                    if(child->visits!=0){
                    if (child->totalScore/child->visits >= bestChild->totalScore/bestChild->visits ) {
                        bestChild = child;
                        best_action = child->move_done;
                    }
                    }
                }


                if(utility(bestChild)>0.71){
                    search=false;
                }


                // TUNE

                if(best_action==prev_prev_prev_prev_move && depth==TL_DEPTH){
                    cout<<"THREE FOLDS REP>>>>>>>>>>?????????????????????????"<<endl;
                    best_action = *moveset.begin();
                }
                else if(best_action==prev_prev_prev_prev_move){
                    init_exp+=2;
                }
                depth+=2;

                // PRINTs FOR THIS DEPTH
                cout<<"Time required elementel"<<duration_cast<milliseconds>(high_resolution_clock::now()-start).count()<<endl;
                for(auto i:moveset){
                    cout<< move_to_str(i)<<" ";
                }
                cout<<endl;
                cout<< move_to_str(best_action)<<endl;

                // weight_ob.write_weights((int)b.data.board_type);
            }
    }

    this->best_move = best_action;
    prev_prev_prev_prev_move=prev_prev_prev_move;
    prev_prev_prev_move=prev_prev_move;
    prev_prev_move=prev_move;
    prev_move=this->best_move;
    
    cout<<"TOTAL TIME required to get best move=     "<<duration_cast<milliseconds>(high_resolution_clock::now()-start).count()<<endl;

    cout<<"Time Left "<<time_left.count()<<endl;
    

}




