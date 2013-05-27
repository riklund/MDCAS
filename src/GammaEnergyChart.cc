#include "GammaEnergyChart.hh"

GammaEnergyChart::~GammaEnergyChart()
{
  for(map<pair<int, int>, vector<GammaLine*> >::iterator it = myGammaLines->begin(); it!=myGammaLines->end(); it++)
    {
      for(vector<GammaLine*>::iterator ig = it->second.begin(); ig!=it->second.end(); ig++)
	{
	  delete *ig;
	}
    }
  delete myGammaLines;
}

GammaEnergyChart::GammaEnergyChart(char * gammaFile, int minA, int maxA, int minZ, int maxZ, float tol, float bgTol)
{  
  FILE * myFileStream = fopen(gammaFile,"r");
  if(myFileStream==NULL)
    {
      fprintf (stderr,"Could not open input event file %s, exiting.", gammaFile);
      exit(1);
    }
  myGammaLines = new map<pair<int, int>, vector<GammaLine*> >;
  //Read in all gamma lines
  while(!feof(myFileStream))
    {
      int tempA, tempZ;
      float tempGamma, tempProb;
      fscanf(myFileStream, "%d %d %e %e", &tempA, &tempZ, &tempGamma, &tempProb);
      tempGamma/=1000;
      if(!(tempA< minA || tempA > maxA || tempZ < minZ || tempZ > maxZ))
	{
	  (*myGammaLines)[make_pair(tempA, tempZ)].push_back(new GammaLine(tol, bgTol));
	  (*myGammaLines)[make_pair(tempA, tempZ)].back()->gamma = tempGamma;
	  (*myGammaLines)[make_pair(tempA, tempZ)].back()->probability = tempProb;
	}
    }
}

void GammaEnergyChart::addCoincidence(pair<EventHit*, EventHit*> toAdd, float epsilon)
{
  for(map< pair< int , int > , vector < GammaLine * > > ::iterator it = 
	myGammaLines->begin(); it!=myGammaLines->end(); it++)
    {
      for(vector<GammaLine*>::iterator ig = it->second.begin(); ig!=it->second.end(); ig++)
	{
	  //cout << (*ig)->gamma << "  " << toAdd.second->Ge << "  " << abs((*ig)->gamma-toAdd.second->Ge) << " " << (*ig)->gamma-toAdd.second->Ge << " EPS: " << epsilon << endl;
	  (*ig)->addCoincidenceIfValid(toAdd);
	}
    }
}
  

map<pair<int, int>, vector<GammaLine*> > * GammaEnergyChart::getGammaLines()
{
  return myGammaLines;
}
