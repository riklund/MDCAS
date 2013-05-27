#include "FileEventParser.hh"

FileEventParser::FileEventParser(char * filename, int nTubes, float detEpsilon, float dRatio)
{
  numberOfTubes = nTubes;
  detectorEpsilon = detEpsilon;
  dominateRatio = dRatio;
  myFileStream = fopen(filename,"r");
  if(myFileStream==NULL)
    {
      fprintf (stderr,"Could not open input event file %s, exiting.", filename);
      exit(1);
    }
  fileEmpty = false;
}

FileEventParser::~FileEventParser()
{
  fclose(myFileStream);
}

EventHit * FileEventParser::getNextEventHit()
{
  EventHit * eventToReturn;
  eventToReturn = new EventHit(numberOfTubes, detectorEpsilon, dominateRatio);

  if(fileEmpty)
    return NULL;
  if(fscanf(myFileStream,"%d %d %d %le", &eventToReturn->eventno, &eventToReturn->Z, &eventToReturn->A, &eventToReturn->time)<4)
    {
      fileEmpty = true;
      return NULL;
    }
  if(fscanf(myFileStream, "%e %e %e %e", &eventToReturn->UFSP, &eventToReturn->LFSP, &eventToReturn->BSP, &eventToReturn->Ge)<4)
    {
      fileEmpty = true;
      return NULL;
    }
  for(int j = 0; j<numberOfTubes; j++)
    {
      if(fscanf(myFileStream,"%e",&eventToReturn->DET[j])<1)
	{
	  fileEmpty = true;
	  return NULL;
	}
    }
  if(feof(myFileStream))
    {
      fileEmpty = true;
    }  
  eventToReturn->ComputeHitType();
  return eventToReturn;
}

bool FileEventParser::hasMoreEvents()
{
  return !fileEmpty;
}
