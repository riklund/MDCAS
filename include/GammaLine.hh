#include <vector>
#include <utility>
#include <iostream>
#include <math.h>
using namespace std;

#include "EventHit.hh"

/**\file GammaLine.hh
   \author Rikard Lundmark
   \brief Header file for the GammaLine class.
*/
/**\file GammaLine.cc
   \author Rikard Lundmark
   \brief Source file for the GammaLine class.
*/


#ifndef GAMMALINE_HH
#define GAMMALINE_HH //!<Inclusion guard.
class GammaLine
{
public:
  GammaLine(float tol //!<Tolerance when adding a gamma energy.
	    ,float bgTol //!<Background tolerance when adding that energy.
	    );

  void addCoincidenceIfValid(pair<EventHit*, EventHit*> toAdd //!<The coincidence to add.
			     ); //!<Add a coincidence if it should be done.

  float getBackgroundMean(); //!<Get mean value of background.

  float getBackgroundSTD(); //!<Get standard deviation of background. 

  float gamma; //!<Gamma energy. 
  float probability; //!<Probability
  vector<pair<EventHit*, EventHit*> > coincidences; //!<Coincidences (valid) added to this gamma line. 
  
private:
  float AbsVal(float toAbs //!<Value to take abs of
	       ); //!<Absolute value.
  void addBackground(float bg//!<Only add valid background, plz.
		     );

  float standardDeviation(vector<float> toDeviate //!<To deviate...
			   );//!<Compute standard deviation.
  float meanValue(vector<float> toMean //to mean
		  ); //!<Compute mean value.
  float sum(vector<float> toSum //!<Elements to sum.
	    ); //!<Sum.

  float tolerance; //!<Tolerance. 
  float bgTolerance; //!<Background tolerance
  vector<float> background; //!<Background events. 
};
#endif

