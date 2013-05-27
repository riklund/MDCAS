/** \file EventHit.hh
    \author Rikard Lundmark
    \brief Header file for the EventHit class.
*/
/** \file FileEventParser.cc
    \author Rikard Lundmark
    \brief Source file for the EventHit class.
*/
using namespace std;


#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "HitType.hh"


/**\file EventHit.hh
   \author Rikard Lundmark
   \brief Header file for the EventHit class.
*/
/**\file EventHit.cc
   \author Rikard Lundmark
   \brief Source file for the EventHit class.
*/

#ifndef EVENTHIT_H
#define EVENTHIT_H //!<Inclusion guard
/**Contains information about a single event hit, not to be confused with an event.  */
class EventHit
{
public:
  //Cheat information, not to be used for analysis purposes, for validation only.
  int A; //!<A of the event.
  int Z; //!<Z of the event.
  int eventno; //!<Event number.


  //Real information, to be used for analysis purposes.
  double time; //!<Time of the event hit, relative the beginning of the event.
  
  float UFSP; //!<Upper front scintillator plate energy deposition.
  float LFSP; //!<Lower front scintillator plate energy deposition.
  float BSP; //!<Back scintillator plate energy deposition.
  float Ge; //!<Ge detector energy deposition.

  
  vector<float> DET;  // Energy deposition in each scintillator tube.
  
  HitType implantationType; //!<Type of implantation

  void ComputeHitType(); //!<Computes type of implantation. Call when parameters are correctly set.

  string toString(); //Returns a string describing the object.

  EventHit(int nTubes = 40,
	   float detEpsilon = 1E-2,
	   float dRatio = 1E2
	   ); //!<Constructor, constructs the object.

private:
  int GetDominating(); //Returns the dominating scintillator, or -10 if no such scintillator.
  int numberOfTubes; //!<Number of scintillator tubes in detector.
  float detectorEpsilon; //!<Detector epsilon.
  float dominateRatio; //!<Ratio for domination.
};
#endif
