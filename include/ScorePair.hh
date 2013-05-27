#include <algorithm>


/**\file ScorePair.hh
   \author Rikard Lundmark
   \brief Header file for the ScorePair class.
*/

/**\file ScorePair.cc
   \author Rikard Lundmark
   \brief Source file for the ScorePair class.
*/

#ifndef SCOREPAIR_HH
#define SCOREPAIR_HH //!<Inclusion guard
/**
   Pair score with A and Z, also implement comparision operator. Used for scoring and finding which nuclide the gamma lines most probably are related to.
 */
class ScorePair
{
public:
  int A; //!<A of the nuclide.
  int Z; //!<Z of the nuclide.
  double score; //!<Score
  bool operator<(ScorePair rhs //!<Score pair for comparision
		 ) //!<Comparision operator.
  { return score > rhs.score; }
};
#endif
