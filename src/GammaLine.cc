#include "GammaLine.hh"

GammaLine::GammaLine(float tol, float bgTol)
  :tolerance(tol), bgTolerance(bgTol)
{
  for(float i = tol-bgTol; i<=tol+bgTol; i+=2*tol)
    {
      background.push_back(0);
    }
}

void GammaLine::addBackground(float bg)
{
  for(unsigned int i = 0; i<background.size(); i++)
    {
      if((tolerance-bgTolerance+i*tolerance)>bg)
	{
	  ++background[i];
	  return;
	}
    }
}

void GammaLine::addCoincidenceIfValid(pair<EventHit*, EventHit*> toAdd)
{
  if(AbsVal(toAdd.second->Ge-gamma)<tolerance)
    {
      coincidences.push_back(toAdd);
    }
  if(AbsVal(toAdd.second->Ge-gamma)<bgTolerance)
    {
      addBackground(toAdd.second->Ge);
    }
}

float GammaLine::AbsVal(float toAbs)
{
  if(toAbs<0)
    return -toAbs;
  return toAbs;
}


float GammaLine::standardDeviation(vector<float> toDeviate)
{
  if(toDeviate.size()<2)
    return 0;
  float mean = meanValue(toDeviate);
  float stdev = 0;
  for(vector<float>::iterator it = toDeviate.begin(); it!=toDeviate.end(); it++)
    {
      stdev+=pow(*it-mean,2);
    }
  stdev/=(toDeviate.size()-1);
  return sqrt(stdev);
}

float GammaLine::meanValue(vector<float> toMean)
{
  return sum(toMean)/toMean.size();
}


float GammaLine::sum(vector<float> toSum)
{
  float sum = 0;
  for(vector<float>::iterator it = toSum.begin(); it!=toSum.end(); it++)
    {
      sum+=*it;
    }
  return sum;
}

float GammaLine::getBackgroundSTD()
{
  return standardDeviation(background);
}

float GammaLine::getBackgroundMean()
{
  return meanValue(background);
}
