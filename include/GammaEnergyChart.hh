#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <map>

#include "EventHit.hh"
#include "GammaLine.hh"
using namespace std;


/**\file GammaEnergyChart.hh
   \author Rikard Lundmark
   \brief Header file for the GammaEnergyChart class.
*/
/**\file GammaEnergyChart.cc
   \author Rikard Lundmark
   \brief Source file for the GammaEnergyChart class.
*/

#ifndef GAMMAENERGYCHART_HH
#define GAMMAENERGYCHART_HH //!<Inclusion guard.
class GammaEnergyChart
{
public:
  GammaEnergyChart(char * gammaFile, //!<File containing gamma data of interesting nuclides.
		   int minA = -100000, //!<Discard A below this value.
		   int maxA = 1000000, //!<Discard A above this value.
		   int minZ = -100000,  //!<Discard Z below this value.
		   int maxZ = 1000000, //!<Discard Z above this value.
		   float tol = 3E-3,
		   float bgTol = 5E-2
		   ); //!<Constructor, constructs the object.

  ~GammaEnergyChart(); //!<Destructor, destroys the object.

  void addCoincidence(pair<EventHit*, EventHit*> toAdd //!<The eventhit to add.
		    , float epsilon //!<Tolerance of energy.
		    ); //!<Adds a gamma line.

  map<pair<int, int>, vector<GammaLine*> > * getGammaLines();


private:

  map<pair<int, int>, vector<GammaLine*> > * myGammaLines; //!<Gamma data from text file. Key is <A, Z>, value is a vector with gamma lines.
};
#endif
