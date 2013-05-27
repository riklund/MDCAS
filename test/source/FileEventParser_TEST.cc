#include "FileEventParser_TEST.hh"


bool FileEventParser_TEST::DoubleEquality(double d1, double d2, double eps) const
{
  return (abs(d1-d2)<eps);
}

bool FileEventParser_TEST::FileEventParser_OpensFile_AssertTrue() const
{
  FileEventParser myParser((char*)"test/testdata.txt");
  return true;
}

bool FileEventParser_TEST::FileEventParser_ReturnsCorrectNumberOfHits_AssertTrue() const
{
  FileEventParser myParser((char*)"test/testdata.txt");
  int eventCount = 0;
  while(myParser.hasMoreEvents())
    {
      myParser.getNextEventHit();
      if(eventCount>15)
	return false;
      ++eventCount;
    }
  return eventCount==13;
}

bool FileEventParser_TEST::FileEventParser_ReturnsCorrectHits_AssertTrue() const
{
  FileEventParser myParser((char*)"test/testdata.txt");
  int eventCount = 0;
  EventHit * P;
  while(myParser.hasMoreEvents() && (P=myParser.getNextEventHit())!=NULL)
    {
      switch(eventCount)
	{
	case 0:
	  if(P->eventno!=0 || P->Z!=6 || P->A!=17)
	    return false;
	  if(!DoubleEquality(P->time,1E8,1))
	    return false;
	  if(!DoubleEquality(P->UFSP,0,1E-100) || !DoubleEquality(P->LFSP,0,1E-100) || !DoubleEquality(P->BSP,1E1,1E-1) || !DoubleEquality(P->Ge,0,1E-100) )
	    return false;
	  for(int i = 0; i<40; i++)
	    {
	      if(true)
		{
		  if(!DoubleEquality(P->DET[i],0,1E-100))
		    return false;
		}
	    }
	  break;
	case 1:
	  if(P->eventno!=1 || P->Z!=6 || P->A!=17)
	    return false;
	  if(!DoubleEquality(P->time,2E8,1))
	    return false;
	  if(!DoubleEquality(P->UFSP,2E1,1E-10) || !DoubleEquality(P->LFSP,0,1E-100) || !DoubleEquality(P->BSP,0,1E-100) || !DoubleEquality(P->Ge,0,1E-100) )
	    return false;
	  for(int i = 0; i<40; i++)
	    {
	      if(true)
		{
		  if(!DoubleEquality(P->DET[i],0,1E-100))
		    return false;
		}
	    }
	  break;
	case 10:
	  if(P->eventno!=10 || P->Z!=6 || P->A!=17)
	    return false;
	  if(!DoubleEquality(P->time,1.1E9,1))
	    return false;
	  if(!DoubleEquality(P->UFSP,0,1E-100) || !DoubleEquality(P->LFSP,0,1E-100) || !DoubleEquality(P->BSP,0,1E-100) || !DoubleEquality(P->Ge,1.337,1E-10) )
	    return false;
	  for(int i = 0; i<40; i++)
	    {
	      if(i!=9)
		{
		  if(!DoubleEquality(P->DET[i],0,1E-100))
		    return false;
		}
	      else
		{
		  if(!DoubleEquality(P->DET[i],2E1,1E-5))
		    return false;
		}
	    }
	  break;
	  //could add more tests, don't seem neccesary though.
	}
      ++eventCount;
    }
  return true;
}


int FileEventParser_TEST::runUnitTests() const
{
  cout << "Running unit tests on FileEventParser... ";
  cout.flush();
  if(!FileEventParser_OpensFile_AssertTrue())
    {
      return 1;
    }
  cout << "1.";
  cout.flush();
  if(!FileEventParser_ReturnsCorrectNumberOfHits_AssertTrue())
    {
      return 1;
    }
  cout << "2.";
  cout.flush();

  if(!FileEventParser_ReturnsCorrectHits_AssertTrue())
    {
      return 1;
    }
  cout << "3.";
  cout.flush();

  cout << "done" << endl;
  return 0;
}
