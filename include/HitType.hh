#include <vector>
using namespace std;


/**\file HitType.hh
   \author Rikard Lundmark
   \brief Header file for the HitType class.
*/
/**\file HitType.cc
   \author Rikard Lundmark
   \brief Source file for the HitType class.
*/

#ifndef HITTYPE_H
#define HITTYPE_H //!<Inclusion guard
/**Some extended hit information.*/
class HitType
{
public:
  HitType(); //!<Constructor.
  bool wasImplantation ; //!<True if implantation.
  bool wasDecay; //!<True if decay.
  bool wasOther; //!<True if other.
  vector<int> affectedScintillators; //!<If implantation or decay, this only contains one number.
  int statvar; //!<Contains statistics about why we had a failure to identify.
};
#endif
