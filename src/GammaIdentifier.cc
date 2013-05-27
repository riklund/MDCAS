#include "GammaIdentifier.hh"

GammaIdentifier::GammaIdentifier(GammaEnergyChart * toUse, double tol, float minGamma, float maxGamma, float bgTol, bool forceCorr)
  :myChart(toUse), tolerance(tol), bgTolerance(bgTol), minGammaEnergy(minGamma), maxGammaEnergy(maxGamma), forceCorrect(forceCorr)
{
  myTable = new ElementLookupTable();
}

GammaIdentifier::~GammaIdentifier()
{
  delete myTable;
}

void GammaIdentifier::addCoincidence(pair<EventHit*, EventHit*> toAdd)
{
  myChart->addCoincidence(toAdd, tolerance);
  coincidences.push_back(toAdd);
}

list<ScorePair> GammaIdentifier::doSimpleScoring()
{
  list<ScorePair> scoring;
  map<pair<int, int>, vector<GammaLine*> > * lines = myChart->getGammaLines();
  for(map<pair<int, int>, vector<GammaLine*> >::iterator it = lines->begin(); it!=lines->end(); it++)
    {
      scoring.push_back(ScorePair());
      scoring.back().A=it->first.first;
      scoring.back().Z=it->first.second;
      for(vector<GammaLine*>::iterator ig = it->second.begin(); ig!=it->second.end(); ig++)
	{
	  scoring.back().score+=(*ig)->coincidences.size();
	}
    }
  scoring.sort();
  return scoring;
}

string GammaIdentifier::getMATLABstring(int figure)
{
  list<ScorePair> score = doProbabilisticScoring();
  stringstream ss;
  ss << "A" << coincidences.front().first->A << "Z" << coincidences.front().first->Z << "=[" << endl;  
  for(list<pair<EventHit*, EventHit*> >::iterator it =  coincidences.begin(); it!=coincidences.end(); it++)
    {
      ss << scientific << it->second->Ge << endl;
    }
  ss << "];" << endl;
  ss << "figure(" << figure << ");" << endl;
  ss << "hold on;" << endl;
  ss << "hist(" << "A" << coincidences.front().first->A << "Z" << coincidences.front().first->Z << ",[" << minGammaEnergy << ":" << 2*tolerance << ":" << maxGammaEnergy << "]);" << endl;
  ss << "[AZh, AZe]=hist(" << "A" << coincidences.front().first->A << "Z" << coincidences.front().first->Z << ",[" << minGammaEnergy << ":" << 2*tolerance << ":" << maxGammaEnergy << "]);" << endl;
  ss << "h = findobj(gca,'Type','patch');\nset(h,'FaceColor','b','EdgeColor','b')" << endl;
  ss << "AZs=smooth(AZh,33);" << endl;
  ss << "plot(AZe,AZs,'r-');" << endl;
  ss << "AZd=(AZh-AZs');" << endl;
  ss << "AZv=AZd.^2;" << endl;
  ss << "AZvs=smooth(AZv,33);" << endl;
  ss << "AZstd=sqrt(AZvs);" << endl;
  ss << "plot(AZe,AZs+2*AZstd,'k-');" << endl;

  map<pair<int, int>, vector<GammaLine*> > * lines = myChart->getGammaLines();
  unsigned int max = 0;
  for(map<pair<int, int>, vector<GammaLine*> >::iterator it = lines->begin(); it!=lines->end(); it++)
    {
      if((it->first.first==score.front().A && it->first.second==score.front().Z))
	{
	  for(vector<GammaLine*>::iterator ig = it->second.begin(); ig!=it->second.end(); ig++)
	    {
	      if((*ig)->coincidences.size()>max)
		max = (*ig)->coincidences.size();
	      ss << "plot([" << (*ig)->gamma << " " << (*ig)->gamma <<"],[" 
		 << 0 << " " << (*ig)->coincidences.size() << "],'r','LineWidth',2);" << endl;
	      ss.precision(5);
	      ss << "text(" << (*ig)->gamma << "," << (float)(*ig)->coincidences.size()+0.25 << ",'";
	      ss.precision(3);
	      ss.unsetf(ios::fixed);
	      ss.unsetf(ios::scientific);
	      ss << fixed << (*ig)->gamma << " MeV, #=" << fixed << (*ig)->coincidences.size() << "');" << endl;
		}
	  
	}
    }
  ss << "xlim([" << minGammaEnergy << " " << maxGammaEnergy << "]);" << endl;
  ss << "ylim([0 " << max+1 << "]);" << endl;
  ss << "title('^{" << coincidences.front().first->A << "}" << myTable->lookupElement((unsigned short int)coincidences.front().first->Z) << ": identified as ^{" << score.front().A << "}" << myTable->lookupElement((unsigned short int)score.front().Z) << "');" << endl;
  ss << "xlabel('Energy [/MeV]');" << "ylabel('Counts');" << endl;



  return ss.str();
}


list<ScorePair> GammaIdentifier::doProbabilisticScoring()
{
  list<ScorePair> scoring;
  if(forceCorrect)
    {
      scoring.push_back(ScorePair());
      scoring.back().A=coincidences.front().first->A;
      scoring.back().Z=coincidences.front().first->Z;
      return scoring;
    }
  map<pair<int, int>, vector<GammaLine*> > * lines = myChart->getGammaLines();
  //cout << endl << endl;
  for(map<pair<int, int>, vector<GammaLine*> >::iterator it = lines->begin(); it!=lines->end(); it++)
    {
      scoring.push_back(ScorePair());
      scoring.back().A=it->first.first;
      scoring.back().Z=it->first.second;
      //cout << scoring.back().A << " " << scoring.back().Z << ": ";
      float score = 0;
      for(vector<GammaLine*>::iterator ig = it->second.begin(); ig!=it->second.end(); ig++)
	{
	  float lineSize = 0;
	  if(((*ig)->coincidences.size()-(*ig)->getBackgroundMean())>2*sqrt((*ig)->coincidences.size()+(*ig)->getBackgroundSTD()))
	     //if((*ig)->coincidences.size()-2*(*ig)->getBackgroundSTD()-(*ig)->getBackgroundMean())
	    {
	      lineSize = (*ig)->coincidences.size();
	    }

	  lineSize/=(*ig)->probability;
	  //cout << (*ig)->gamma << "(" << (*ig)->probability << "): " << (*ig)->coincidences.size() << " LS:" << lineSize << "   ";
	  score+=lineSize/it->second.size();
	}
      //cout << endl;
      scoring.back().score=score;
      //if(lines.size()<2)
      //scoring.back().score/=2; //We need some kind of penalty if there is only one line...
      
      /*if(lines.size()>0)
	tempScore/=scoreCount;
      
	scoring.back().score/=scoreCount;*/
      
    }
  scoring.sort();
  return scoring;
}

string GammaIdentifier::getPeakString()
{
  list<ScorePair> score = doProbabilisticScoring();
  stringstream ss;
  ss << "tA" << coincidences.front().first->A << "Z" << coincidences.front().first->Z << "=[" << endl;  

  map<pair<int, int>, vector<GammaLine*> > * lines = myChart->getGammaLines();
  for(map<pair<int, int>, vector<GammaLine*> >::iterator it = lines->begin(); it!=lines->end(); it++)
    {
      if((it->first.first==score.front().A && it->first.second==score.front().Z))
	{
	  for(vector<GammaLine*>::iterator ig = it->second.begin(); ig!=it->second.end(); ig++)
	    {
	      for(vector<pair<EventHit*, EventHit*> >::iterator ip = (*ig)->coincidences.begin(); ip!=(*ig)->coincidences.end(); ip++)
		{
		  ss << scientific << (ip->second->time-ip->first->time) << endl;
		}
	    }
	}
    }
  ss << "];";
  return ss.str();
}
