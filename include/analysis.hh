/**\file analysis.hh
   \author Rikard Lundmark
   \brief Main header file for the analysis software.
*/
/**\file analysis.cc
   \author Rikard Lundmark
   \brief Main source file for the analysis software.
*/




#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <iomanip>
#include <sstream>
#include <set>

#include "GammaEnergyChart.hh"
#include "FileEventParser.hh"
#include "EventHit.hh"
#include "CoincidenceFinder.hh"
#include "CommandLineInterpreter.hh"
#include "CommandLineException.hh"
#include "CommandLineArgument.hh"
#include "GammaIdentifier.hh"
#include "ScorePair.hh"



#ifndef SETTINGS_H
#define SETTINGS_H
/** Contains the settings availible when using the command line.
 */
struct Settings
{
  string coincidenceFile; //!<Concindence file (MATLAB code printed to this file). Will be overwritten.
  string timeDistributionFile; //!<Time distribution file. Will be overwritten.
  string mixedFile; //!<File containing mixed data to analyze.
  string gammaFile; //!<File containing the gamma levels to use for analysis.

  float tolerance; //!<Tolerance
  float bgTolerance; //!<Background tolerance.
  unsigned int multiImplant; //!<Multiple implantation allowed.
  int nTubes; //!<Number of scintillator tubes.
  int nTubesPerRow; //!<Number of tubes per row.
  float geEpsilon; //!<Energy resolution of Ge detector.
  float betaEpsilon; //!<Energy epsilon of beta detectors.
  float dRatio; //!<Domination ratio (ratio for considering only one scintillator)
  float minGe; //!<Minimum Ge energy to consider.
  float maxGe; //!<Maximum Ge energy to consider.
  float maxDecayWait; //!<Maximum decay wait.
  float decayCut; //!<Decay cut.
  bool forceCorrect; //!<Fake all identifications to be correct.

  unsigned short int minA; //!<Minimum A to consider in the identification.
  unsigned short int maxA; //!<Maximum A to consider in the identification.
  unsigned short int minZ; //!<Minimum Z to consider in the identification.
  unsigned short int maxZ; //!<Maximum Z to consider in the identification.

  bool detectorCount; //!<Print number of coincidences per detector.
  bool failInfo; //!<Print info about failed coincidences.
};
#endif

using namespace std;

string nsToReadableTime(double time //!<Time in ns to convert
			); //!<Convert ns to readable time.

int main(int argc //!<Number of arguments the program was called with.
	 , char **argv //!<All the arguments.
	 ); //!<Main method. \return Exit status.

CommandLineInterpreter * decodeInput(int argc //!<Number of arguments.
		  , char **argv //!<The actual arguments.
		  ); //!<Verifies input, exists and prints a usage message if this does not conform with expected command line.

void printStatistics(CoincidenceFinder * F //!<To print statistics from.
		     ); //!<Print statistics from the Coincidence finder.

void printDetectorCount(CoincidenceFinder * F //!<To print detector count from.
			,int numberPerRow //!<Number per row.
			); //!<Print detector count to stdout.

void printSettings(Settings * S //!<The settings to print.
		   ); //!<Prints the settings to stdout.

Settings * initSettings(CommandLineInterpreter * myInterpreter //!<Initialize from this.
			); //!<Initialize a new settings object from a command line interpreter.


/** \mainpage
 \section intro_sec Introduction
The Mixed Data Coincidence Analysis Software can be used to analyze mixed data from the EventMixer software using a variety of settings. 
 
 \section install Installation
For installation, download the MDCAS from <a href="MDCAS.tar.gz">here</a>, unpack it and run "make".
 */
