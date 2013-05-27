/** \file GammaIdentifier.hh
    \author Rikard Lundmark
    \brief Header file for the GammaIdentifier class.
*/
/** \file GammaIdentifier.cc
    \author Rikard Lundmark
    \brief Source file for the GammaIdentifier class.
*/
using namespace std;


#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <list>
#include <math.h>

#include "EventHit.hh"
#include "GammaEnergyChart.hh"
#include "ScorePair.hh"
#include "ElementLookupTable.hh"

using namespace std;

#ifndef GAMMAIDENTIFIER_HH
#define GAMMAIDENTIFIER_HH //!<Inclusion guard
/**Utilizes the GammaEnergyChart to find the appropriate matches for the found gammas.  */
class GammaIdentifier
{
public:
  GammaIdentifier(GammaEnergyChart * toUse, //!<Energy chart used for identification.
		  double tol, //!<Tolerance.
		  float minGamma, //!<Min gamma energy.
		  float maxGamma //!<Max gamma energy.
		  , float bgTol = 0.05
		  , bool forceCorr = false 
		  ); //!<Constructor.
  ~GammaIdentifier(); //!<Destructor.

  void addCoincidence(pair<EventHit*, EventHit*> toAdd //!<Implant-decay pair
		      ); //!<Add a detected coincidence for analysis.

  list<ScorePair> doSimpleScoring(); //!<Does a simple (non-probabilistic) scoring of line count.

  list<ScorePair> doProbabilisticScoring(); //!<Does a more advanced probabilistic scoring.

  string getMATLABstring(int figure);

  string getPeakString();

private:
  GammaEnergyChart * myChart;
  double tolerance;
  double bgTolerance;
  float minGammaEnergy;
  float maxGammaEnergy;
  bool forceCorrect;
  list<pair<EventHit*, EventHit*> > coincidences;
  ElementLookupTable * myTable;
};

#endif
