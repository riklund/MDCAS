#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <utility>
#include <string>

#include "GammaEnergyChart.hh"
#include "FileEventParser.hh"
#include "EventHit.hh"
using namespace std;

/**\file CoincidenceFinder.hh
   \author Rikard Lundmark
   \brief Header file for the CoincidenceFinder class.
*/
/**\file CoincidenceFinder.cc
   \author Rikard Lundmark
   \brief Source file for the CoincidenceFinder class.
*/


#ifndef COINCIDENCE_FINDER_HH
#define COINCIDENCE_FINDER_HH //!<Inclusion guard
class CoincidenceFinder
{
public:
  CoincidenceFinder(FileEventParser * fParser //!<FileEventParser to read from.
		    ,double maxWait //!<Maximum decay wait time.
		    , int nTubes = 40 //!<Number of scintillator tubes in detector.
		    , float detEps = 1E-2 //!<Minimum energy to consider for the beta detector.
		    , float minGe = 1E-2 //!<Minimum energy to consider for the germanium detector.
		    , float maxGe = 1E20 //!<Maximum energy to consider for the germanium detector.
		    , unsigned int multiImplant = 1 //!<Number of allowed multiple implantations.
		    , float decayCut = 1E20 //!<Decay cut, if more than this the particle is considered as disappeared.
		    ); //!<Constructor, constructs the object.
  
  ~CoincidenceFinder(); //!<Destructor, destroys the object. 

  pair<EventHit*, EventHit*> getNextCoincidence(); //!<Returns the next coincidence pair. Please note that this might be invalid if the hasMoreCoincidences returns false. Calling this method will update the next coincidence to the next one automatically.
  
  bool hasMoreCoincidences(); //!<Returns true if there are more coincidences to be read from the class, otherwise false.

  int getFailureReason(int reason /** Reason*/); //!<Returns the failure reason.

  int getNoHits(); //!<Get number of hits. 

  int getNoImplantations(); //!<Get number of implantations.

  int getNoDecays(); //!<Get number of decays.

  int getNoOther(); //!<Get number of others.

  int getNoCorrectImplantations(); //!<Get number of correct implantations.

  int getNoDoubleHit(); //!<Get number of double hits. 

  int getNoGeHit();//!<Get number of Ge hits.

  int getNoNonAssociatedDecays(); //!<Get number of non-associated decays.

  int getNoCorrConnected(); //!<Get number of correctly connected implant-decays.

  int getNoErrConnected(); //!<Get number of incorrectly connected implant-decays.

  int getNoDestroyedByOther(); //!<Get number of implantations destroyed by other-events.

  int getNoCorrCoincidence(); //!<Get number of correct coincidences. 

  int getNoFoundCoincidences(); //!<Get number of found coincidences. 

  double getTimeSpan(); //!<Get time span.

  vector<int> getDetectorCount(); //!<Get detector count for each scintillator tube. \return The detector count for each scintillator tube.
  
private:
  int noHits; //!<Number of hits.

  int failureReasons[8]; //!<Information about why events were classified as "other".
  
  int noImplantations; //!<Number of implantations..
  int noDecays; //!<Number of decays.
  int noOther; //!<Number of events other than decay or implant.

  int noCorrectImplantations; //!<Number of correct implantations.
  int noDoubleHit; //!<Number of double hits. Note that double-hits reduces the number of usable implantations.

  int noGeHit; //!<Number of decays resulting in Ge hits.
  int noNonAssociatedDecays; //!<Number of decays not associated with a correct implantation.
  int noCorrConnected; //!<Number of decays connected with the correct implantation.
  int noErrConnected; //!<Number of decays connected with wrong implantation. This should be orders of magnitude lower than noCorrConnected, otherwise we have serious problems...
  int noCorrCoincidence; //!<Number of correct coincidences. 
  
  int noDestroyedByOther; //!<Number of implantations destroyed by another event.
  int noFoundCoincidences; //!<Numer of found coincidences. 

  double timeSpan; //!<Time span

  unsigned int multipleImplant; //!<Multiple implantations allowed. 
  
  float decayCutTime; //!<Decay cut time.


  bool myMoreCoincidences; //!<True if there are more coincidences to be read out from this object.

  vector<pair<list< EventHit*>, double> > myScintillatorTubes; //Contains the EventHits and the time a scintillator tube becomes availible for implantation again.

  FileEventParser * myParser; //!<The FileEventParser connected to this particular event.

  void FindNextCoincidence(); //!<Finds the next coincidence and replaces the nextCoincidence with this. If no coincidence was found, the hasMoreCoincidences is set to false.

  list<pair<EventHit*, EventHit*> > nextCoincidence; //!<Cointains the next coincidence(s). This may cointain NULL when the hasMoreCoincidences variable is set to false.

  void DoImplantation(EventHit * myHit //!<The hit to do implantation with.
		      ); //!<Called from the FindNextCoincidence routine ONLY.
  int DoDecay(EventHit * myHit //!<The hit to pair decay with.
	       ); //!<Called from the FindNextCoincidence routine ONLY.
  void DoOther(EventHit * myHit //!<The hit to do the other with.
	       ); //!<Called from the FindNextCoincidence routine ONLY.

  double maxDecayWait; //!<Maximum time to wait for a decay before deeming the tube empty.
  int numberOfTubes; //!<Number of scintillator tubes in detector.
  float detectorEpsilon; //!<Detector epsilon. 
  float minGeEnergy; //!<Minimum germanium energy. 
  float maxGeEnergy; //!<Maximum germanium energy. 
  vector<int> detectorCount; //!<Detector count. 
};

#endif
