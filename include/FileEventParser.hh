/** \file FileEventParser.hh
    \author Rikard Lundmark
    \brief Header file for the FileEventParser class.
*/
/** \file FileEventParser.cc
    \author Rikard Lundmark
    \brief Source filef or the FileEventParser class.
*/


#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <iostream>

#include "EventHit.hh"

using namespace std;


#ifndef FILEEVENTPARSER_H
#define FILEEVENTPARSER_H //!<Inclusion guard.
/**Creates a pointer to a file, and reads events from that file.*/
class FileEventParser
{
public:
  FileEventParser(char * filename, //!<The file to read events from.
		  int nTubes = 40,
		  float detEpsilon = 1E-2,
		  float dRatio = 1E2); //!<Constructor, constructs the FileEventParser.
  ~FileEventParser(); //!<Destructor.
  EventHit * getNextEventHit(); //!<Returns the next event from the file.
  bool hasMoreEvents(); //!<Returns the fileEmpty variable.
private:
  FILE * myFileStream; //!<The file stream that this object is connected to. Opened upon creation, closed upon destruction.
  bool fileEmpty; //!<True if file is now empty. If a getNextEvent() is called when this is true, a zero result will be returned.
  int numberOfTubes; //!<Number of scintillator tubes in detector.
  float detectorEpsilon; //!<Detector epsilon.
  float dominateRatio; //!<Ratio for domination.
}
;
#endif
