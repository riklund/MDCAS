#include "CoincidenceFinder.hh"

CoincidenceFinder::CoincidenceFinder(FileEventParser * fParser, double maxWait, int nTubes, float detEps, float minGe, float maxGe, unsigned int multiImplant, float decayCut)
  :multipleImplant(multiImplant), decayCutTime(decayCut), maxDecayWait(maxWait),  minGeEnergy(minGe), maxGeEnergy(maxGe)
{
  numberOfTubes = nTubes;
  detectorEpsilon = detEps;
  myParser = fParser;
  for(int i = 0; i<numberOfTubes; i++)
    {
      pair<list<EventHit*>, double> tmp;
      tmp.second=0-maxWait;
      myScintillatorTubes.push_back(tmp);
      detectorCount.push_back(0);
    }

  //For statistics purpose.
  noHits = 0;
  noImplantations = 0;
  noDecays = 0;
  noOther = 0;
  noCorrectImplantations = 0;
  noDoubleHit = 0;
  noGeHit = 0;
  noNonAssociatedDecays = 0;
  noCorrConnected = 0;
  noErrConnected = 0;
  noDestroyedByOther = 0;
  noCorrCoincidence = 0;
  noFoundCoincidences = 0;
  timeSpan = 0;
  
  memset(failureReasons, 0, sizeof(failureReasons));


  FindNextCoincidence();
}

CoincidenceFinder::~CoincidenceFinder()
{
  for(vector<pair<list<EventHit*>,double> >::iterator it = myScintillatorTubes.begin(); it!=myScintillatorTubes.end(); it++)
    {
      if(it->second>0)
	for(list<EventHit*>::iterator ig = it->first.begin(); ig!=it->first.end(); ig++)
	  {
	    delete *ig;
	  }
    }
}

void CoincidenceFinder::DoImplantation(EventHit * myHit)
{
  ++noImplantations;
  int scNr=myHit->implantationType.affectedScintillators.front();      
  timeSpan = myHit->time; //in ns.
  if(myScintillatorTubes[scNr].second+maxDecayWait<myHit->time )  //Availible for implantation (time-out).
    {
      ++noCorrectImplantations;
      if(myScintillatorTubes[scNr].first.size()>=multipleImplant) //We cannot add more, yet it is availible, so it is OK to clear it.
	  {
	    if(myScintillatorTubes[scNr].second>0) //If we have reset the time behind zero, we shall not delete the object since this means that we have returned this event to somewhere else.
	    for(list<EventHit*>::iterator ig = myScintillatorTubes[scNr].first.begin(); ig!=myScintillatorTubes[scNr].first.end(); ig++)
	      {
		delete *ig;
		ig=myScintillatorTubes[scNr].first.erase(ig);
		ig--;
	      }
	    myScintillatorTubes[scNr].first.clear();
	  }
      
      myScintillatorTubes[scNr].first.push_back(myHit);
      if(myScintillatorTubes[scNr].first.size()>=multipleImplant) //No more, please.
	myScintillatorTubes[scNr].second=myHit->time;
      else
	myScintillatorTubes[scNr].second=-maxDecayWait; //Add more, please.

      return;
    }
  else //not availible for implantation, delete all elements and mark as unavailible.
    {
      ++noDoubleHit;
      myScintillatorTubes[scNr].second=myHit->time; //mark it as unavailible for an even longer time.
      delete myHit;
      for(list<EventHit*>::iterator ig = myScintillatorTubes[scNr].first.begin(); ig!=myScintillatorTubes[scNr].first.end(); ig++)
	{
	  delete *ig;
	}
      myScintillatorTubes[scNr].first.clear();
      return;
    }
}

int CoincidenceFinder::DoDecay(EventHit * myHit)
{
  ++noDecays;
  int toReturn = 0;
  if(myHit->Ge>detectorEpsilon)
    {
      ++noGeHit;
    }

  if(!myScintillatorTubes[myHit->implantationType.affectedScintillators.front()].first.empty() && myHit->time - myScintillatorTubes[myHit->implantationType.affectedScintillators.front()].second < decayCutTime) //This decay can be associated with one/more specific implantation(s), hooray!
    {
      bool corrConnected = false;
      
      for(list<EventHit*>::iterator ig = myScintillatorTubes[myHit->implantationType.affectedScintillators.front()].first.begin(); ig!=myScintillatorTubes[myHit->implantationType.affectedScintillators.front()].first.end(); ig++)
	{
	  if((*ig)->eventno==myHit->eventno)
	    {
	      corrConnected = true;
	      ++noCorrConnected;
	    }
	  else
	    {
	      ++noErrConnected;
	    }
	}
      
      //Now, if we could only have the gamma energy...
      if(myHit->Ge>minGeEnergy && myHit->Ge<maxGeEnergy)
	{
	  //Now we have coincidence beta-gamma. Let's store the both events, and clean up.
	  for(list<EventHit*>::iterator ig = myScintillatorTubes[myHit->implantationType.affectedScintillators.front()].first.begin(); ig!=myScintillatorTubes[myHit->implantationType.affectedScintillators.front()].first.end(); ig++)
	    {
	      nextCoincidence.push_back(make_pair(*ig,myHit));
	      ++toReturn;
	    }
	  myMoreCoincidences = true;	  
	  ++detectorCount[myHit->implantationType.affectedScintillators.front()];
	  if(corrConnected)
	    ++noCorrCoincidence;
	}
      myScintillatorTubes[myHit->implantationType.affectedScintillators.front()].first.clear();
      
      myScintillatorTubes[myHit->implantationType.affectedScintillators.front()].second=-maxDecayWait;
    }
  else
    {
      ++noNonAssociatedDecays;
    }

  return toReturn;
}

void CoincidenceFinder::DoOther(EventHit * myHit)
{
  ++noOther;
  if(myHit->implantationType.affectedScintillators.size()<4) //!<If we have more than this, we probably haven't destroyed that much... hopefully.
    {
      for(vector<int>::iterator it = myHit->implantationType.affectedScintillators.begin(); it!=myHit->implantationType.affectedScintillators.end(); it++)
	{
	  for(list<EventHit*>::iterator ig = myScintillatorTubes[*it].first.begin(); ig!=myScintillatorTubes[*it].first.end(); ig++)
	    {
	      if(myScintillatorTubes[*it].second>0)
		{
		  delete *ig;
		  noDestroyedByOther++;
		}
	      ig=myScintillatorTubes[*it].first.erase(ig);
	      ig--;
	    }
	  myScintillatorTubes[*it].second=myHit->time; //Block.	 
	}
    }
  delete myHit;
  return;
}

void CoincidenceFinder::FindNextCoincidence()
{
  if(!nextCoincidence.empty())
    return;
  myMoreCoincidences=false;
  EventHit * myHit;
  while(myParser->hasMoreEvents() && (myHit = myParser->getNextEventHit())!=NULL)
    {
      ++noHits;
      if(myHit->implantationType.statvar>0)
	++failureReasons[myHit->implantationType.statvar-1];
 
      if(myHit->implantationType.wasImplantation) //Implantation into one and only one scintillator.
	{
	  DoImplantation(myHit);
	  continue;
	}
      if(myHit->implantationType.wasDecay)//Decay in one and only one of the scintillators.
	{
	  int add = DoDecay(myHit);
	  if(add>0)
	    {
	      noFoundCoincidences+=add;
	      return;
	    }
	  else
	    continue;
	}
      if(myHit->implantationType.wasOther)
	{
	  DoOther(myHit);
	}
    }
}

pair<EventHit*, EventHit*> CoincidenceFinder::getNextCoincidence()
{
  pair<EventHit*, EventHit*> toReturn = nextCoincidence.front();
  nextCoincidence.erase(nextCoincidence.begin());
  FindNextCoincidence();
  return toReturn;
}

int CoincidenceFinder::getFailureReason(int reason)
{
  return failureReasons[reason];
}

int CoincidenceFinder::getNoImplantations()
{
  return noImplantations;
}

int CoincidenceFinder::getNoDecays()
{
  return noDecays;
}

double CoincidenceFinder::getTimeSpan()
{
  return timeSpan;
}

int CoincidenceFinder::getNoOther()
{
  return noOther;
}

int CoincidenceFinder::getNoCorrectImplantations()
{
  return noCorrectImplantations;
}

int CoincidenceFinder::getNoDoubleHit()
{
  return noDoubleHit;
}

int CoincidenceFinder::getNoGeHit()
{
  return noGeHit;
}

int CoincidenceFinder::getNoNonAssociatedDecays()
{
  return noNonAssociatedDecays;
}

int CoincidenceFinder::getNoCorrConnected()
{
  return noCorrConnected;
}

int CoincidenceFinder::getNoErrConnected()
{
  return noErrConnected;
}

int CoincidenceFinder::getNoDestroyedByOther()
{
  return noDestroyedByOther;
}

int CoincidenceFinder::getNoCorrCoincidence()
{
  return noCorrCoincidence;
}

int CoincidenceFinder::getNoFoundCoincidences()
{
  return noFoundCoincidences;
}

int CoincidenceFinder::getNoHits()
{
  return noHits;
}

bool CoincidenceFinder::hasMoreCoincidences()
{
  return myMoreCoincidences;
}

vector<int> CoincidenceFinder::getDetectorCount()
{
  return detectorCount;
}
