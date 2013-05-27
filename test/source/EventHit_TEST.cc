#include "EventHit_TEST.hh"


bool EventHit_TEST::DoubleEquality(double d1, double d2, double eps) const
{
  return (abs(d1-d2)<eps);
}

bool EventHit_TEST::EventHit_ClassifiesCorrectly_AssertTrue() const
{
  FileEventParser myParser((char*)"test/testdata.txt");
  int eventCount = 0;
  EventHit * P;
  while(myParser.hasMoreEvents() && (P=myParser.getNextEventHit())!=NULL)
    {
      HitType H = P->implantationType;
      switch(eventCount)
	{
	case 0:
	  if(H.wasImplantation || H.wasDecay || !H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=0)
	    return false;
	  if(H.statvar!=6)
	    return false;
	  break;

	case 1:
	  if(H.wasImplantation || H.wasDecay || !H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=0)
	    return false;
	  if(H.statvar!=2)
	    return false;
	  break;

	case 2:
	  if(H.wasImplantation || H.wasDecay || !H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=0)
	    return false;
	  if(H.statvar!=1)
	    return false;
	  break;

	case 3:
	  if(H.wasImplantation || H.wasDecay || !H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=0) //no affection on passing.
	    return false;
	  if(H.statvar!=1)
	    return false;
	  break;

	case 4:
	  if(!H.wasImplantation || H.wasDecay || H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=1)
	    return false;
	  if(H.affectedScintillators.front()!=39)
	    return false;
	  if(H.statvar!=0)
	    return false;
	  break;

	case 5:
	  if(H.wasImplantation || !H.wasDecay || H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=1)
	    return false;
	  if(H.affectedScintillators.front()!=9)
	    return false;
	  if(H.statvar!=0)
	    return false;
	  break;

	case 6:
	  if(H.wasImplantation || !H.wasDecay || H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=1)
	    return false;
	  if(H.statvar!=0)
	    return false;
	  if(H.affectedScintillators.front()!=39)
	    return false;
	  break;

	case 7:
	  if(!H.wasImplantation || H.wasDecay || H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=1)
	    return false;
	  if(H.affectedScintillators.front()!=19)
	    return false;
	  if(H.statvar!=0)
	    return false;
	  break;

	case 8:
	  if(!H.wasImplantation || H.wasDecay || H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=1)
	    return false;
	  if(H.affectedScintillators.front()!=9)
	    return false;
	  if(H.statvar!=0)
	    return false;
	  break;

	case 9:
	  if(!H.wasImplantation || H.wasDecay || H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=1)
	    return false;
	  if(H.affectedScintillators.front()!=19)
	    return false;
	  if(H.statvar!=0)
	    return false;
	  break;

	case 10:
	  if(H.wasImplantation || !H.wasDecay || H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=1)
	    return false;
	  if(H.statvar!=0)
	    return false;
	  if(H.affectedScintillators.front()!=9)
	    return false;
	  break;

	case 11:
	  if(H.wasImplantation || !H.wasDecay || H.wasOther)
	    return false;
	  if(H.affectedScintillators.size()!=1)
	    return false;
	  if(H.statvar!=0)
	    return false;
	  if(H.affectedScintillators.front()!=19)
	    return false;
	  break;

	}	
      ++eventCount;
    }
  return true;
}


int EventHit_TEST::runUnitTests() const
{
  cout << "Running unit tests on EventHit... ";
  cout.flush();
  if(!EventHit_ClassifiesCorrectly_AssertTrue())
    {
      return 1;
    }
  cout << "done" << endl;
  return 0;
}
