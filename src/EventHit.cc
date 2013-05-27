#include "EventHit.hh"
EventHit::EventHit(int nTubes, float detEpsilon, float dRatio)
{
  numberOfTubes = nTubes;
  detectorEpsilon = detEpsilon;
  dominateRatio = dRatio;
  for(int i = 0; i<nTubes; i++)
    DET.push_back(0);
}

int EventHit::GetDominating()
{
  int dominating = -10;
  for(vector<int>::iterator it = implantationType.affectedScintillators.begin(); it!=implantationType.affectedScintillators.end(); it++)
    {
      bool itDominating = true;
      for(vector<int>::iterator iw = implantationType.affectedScintillators.begin(); iw!=implantationType.affectedScintillators.end(); iw++)
	{
	  if(*it!=*iw)
	    {
	      if(DET[(*it)]/DET[(*iw)]<dominateRatio)
		itDominating=false;
	    }
	}
      if(itDominating)
	dominating=*it;
    }
  return dominating;
}


void EventHit::ComputeHitType()
{
  //Check which scintillators were affected.
  for(int i = 0; i<numberOfTubes; i++)
    {
      if(DET[i]>detectorEpsilon)
	{
	  implantationType.affectedScintillators.push_back(i);
	}
    }

  if(UFSP>detectorEpsilon || LFSP>detectorEpsilon) //Particle entered. If something, this must be an implantation.
    {
      if(BSP>detectorEpsilon) //Particle exited. No implantation.
	{
	  implantationType.statvar = 1;
	  implantationType.wasOther=true;
	  implantationType.affectedScintillators.clear(); //If we know that the particle exited, no need to disregard future decays in the affected scintillators.
	  return;
	}
      if(implantationType.affectedScintillators.size()<1 || (GetDominating()<-1)) //More than one scintillator affected. No obvious implantation, we also might need to invalidate scintillator implants.
	{
	  if(implantationType.affectedScintillators.size()<1) //no scintillator affected.
	    implantationType.statvar=2;
	  else //More than one scintillator affected.
	    implantationType.statvar=3;

	  implantationType.wasOther=true;
	  return;
	}
      else //Real implantation (or dominating...)
	{
	  int domin = GetDominating();
	  implantationType.affectedScintillators.clear();
	  implantationType.affectedScintillators.push_back(domin);
	  implantationType.wasImplantation=true;
	  return;
	}
    }
  else if(BSP<detectorEpsilon) //Particle did not enter, this is clearly a decay.
    {
      //Not obvious which scintillator was affected, we might need to invalidate implanted particles in several...
      if(implantationType.affectedScintillators.size()<1 || (GetDominating()<-1)) 
	{
	  if(implantationType.affectedScintillators.size()<1) //no scintillator affected.
	    implantationType.statvar=4;
	  else //More than one scintillator affected.
	    implantationType.statvar=5;
	  implantationType.wasOther=true;
	  return;
	}
      else //We had an actual decay. This does not guarantee that we had a Ge energy though, that must be checked separately.
	{
	  int domin = GetDominating();
	  implantationType.affectedScintillators.clear();
	  implantationType.affectedScintillators.push_back(domin);
	  implantationType.wasDecay=true;
	  return;
	}
    }
  else //Back scintillator only.
    {
      if(implantationType.affectedScintillators.size()<1 || (GetDominating()<-1)) 
	{
	  if(implantationType.affectedScintillators.size()<1) //no scintillator affected.
	    implantationType.statvar=6;
	  else //More than one scintillator affected.
	    implantationType.statvar=7;
	  implantationType.wasOther=true;
	  return;
	}
      else
	{
	  implantationType.statvar=8;
	  implantationType.wasOther=true;
	  return;
	}
    }
}

string EventHit::toString()
{
  stringstream ss;
  ss << "EID:" << eventno << " A:" << A << " Z:" << Z << " time:" << time << " UFSP=" << UFSP << " LFSP=" << LFSP << " BSP=" << BSP << " Ge=" << Ge;
  ss << ". Hits in scintillators: ";
  for(vector<int>::iterator it = implantationType.affectedScintillators.begin(); it!=implantationType.affectedScintillators.end(); it++)
    {
      ss << " SCid" << *it << "=" << DET[*it];
    }
  ss << ". Identified as ";
  if(implantationType.wasImplantation)
    ss << "IMPLANTATION";
  if(implantationType.wasDecay)
    ss << "DECAY";
  if(implantationType.wasOther)
    ss << "OTHER";
  ss << " statvar=" <<implantationType.statvar << endl;
  return ss.str();
  return "";
}
