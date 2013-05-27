#include "analysis.hh"

CommandLineInterpreter * decodeInput(int argc, char **argv)
{
  list<CommandLineArgument> myArguments;
  myArguments.push_back(CommandLineArgument("tolerance",1));
  myArguments.push_back(CommandLineArgument("mixedFile",1));
  myArguments.push_back(CommandLineArgument("gammaFile",1));
  myArguments.push_back(CommandLineArgument("coincidenceFile",1));
  myArguments.push_back(CommandLineArgument("minA",1));
  myArguments.push_back(CommandLineArgument("maxA",1));
  myArguments.push_back(CommandLineArgument("minZ",1));
  myArguments.push_back(CommandLineArgument("maxZ",1));
  myArguments.push_back(CommandLineArgument("geEpsilon",1));
  myArguments.push_back(CommandLineArgument("betaEpsilon",1));
  myArguments.push_back(CommandLineArgument("numberOfTubes",1));
  myArguments.push_back(CommandLineArgument("numberPerRow",1));
  myArguments.push_back(CommandLineArgument("maxDecayWait",1));
  myArguments.push_back(CommandLineArgument("dominationFactor", 1));
  myArguments.push_back(CommandLineArgument("gLow", 1));
  myArguments.push_back(CommandLineArgument("gHigh", 1));
  myArguments.push_back(CommandLineArgument("bgTolerance",1));
  myArguments.push_back(CommandLineArgument("decayCut",1));
  myArguments.push_back(CommandLineArgument("detectorCount", 0));
  myArguments.push_back(CommandLineArgument("failInfo", 0));
  myArguments.push_back(CommandLineArgument("help",0));
  myArguments.push_back(CommandLineArgument("forceCorrect",0));
  myArguments.push_back(CommandLineArgument("multiImplant",1));
  myArguments.push_back(CommandLineArgument("timeDistributionFile",1));
  CommandLineInterpreter * myInterpreter = new CommandLineInterpreter(argc, argv, myArguments);
 
  if(!myInterpreter->readFlaggedCommand("help").empty() || myInterpreter->readFlaggedCommand("mixedFile").empty() || myInterpreter->readFlaggedCommand("gammaFile").empty())
    {
      cout << "The following arguments are valid for the analysis program:" << endl;
      cout << setiosflags(ios::left);
      cout << setw(5) << " " << setw(40) << "-multiImplant <integer value>" << "Allow multiple implantation and cross-associate decays." << endl;
      cout << setw(5) << " " << setw(40) << "-detectorCount" << "Count coincidences for different scintillators." << endl;
      cout << setw(5) << " " << setw(40) << "-failInfo" << "Print info about failed ID:s"<< endl;
      cout << setw(5) << " " << setw(40) << "-forceCorrect" << "Force output graphs to contain correct lines instead of actual identified lines."<< endl;
      cout << setw(5) << " " << setw(40) << "-tolerance <double value>" << "Gamma tolerance for identification." << endl;
      cout << setw(5) << " " << setw(40) << "-mixedFile <file name>" << "File containing mixed data to analyze." << endl;
      cout << setw(5) << " " << setw(40) << "-gammaFile <file name>" << "File containing gamma lines for isotopes, to use for identification" << endl;
      cout << setw(5) << " " << setw(40) << "-coincidenceFile <file name>" << "File to output coincidence gamma energies to." << endl;
      cout << setw(5) << " " << setw(40) << "-minA <integer value>" << "Minimum A to include in analysis." << endl;
      cout << setw(5) << " " << setw(40) << "-maxA <integer value>" << "Maximum A to include in analysis." << endl;
      cout << setw(5) << " " << setw(40) << "-minZ <integer value>" << "Minimum Z to include in analysis." << endl;
      cout << setw(5) << " " << setw(40) << "-maxZ <integer value>" << "Maximum Z to include in analysis." << endl;
      cout << setw(5) << " " << setw(40) << "-gLow <double value>" << "Only count Ge energies above this limit (in MeV)." << endl;
      cout << setw(5) << " " << setw(40) << "-gHigh <double value>" << "Only cound Ge energies below this limit (in MeV)." << endl;
      cout << setw(5) << " " << setw(40) << "-geEpsilon <double value>" << "Detector epsilon (treshold energy) for Ge detector. Default 50 keV." << endl;
      cout << setw(5) << " " << setw(40) << "-betaEpsilon <double value>" << "Detector epsilon (treshold energy) for beta detector. Default 500 keV." << endl;
      cout << setw(5) << " " << setw(40) << "-numberOfTubes <integer value>" << "Number of scintillator tubes in detector. Default 40" << endl;
      cout << setw(5) << " " << setw(40) << "-numberPerRow <integer value>" << "Number of tubes per row for scintillator count printing. Default 10" << endl;
      cout << setw(5) << " " << setw(40) << "-maxDecayWait <double value>" << "Maximum wait time for decay before deeming it timeout. Default 1E10 ns." << endl;
      cout << setw(5) << " " << setw(40) << "-decayCut <double value>" << "Maximum wait time for decay before not accepting implants. Default value 1E10 ns." << endl;
      cout << setw(5) << " " << setw(40) << "-dominationFactor <double value>" << "Factor to determine when a decay in a tube is so dominating that detections in other tubes can be ignored." << endl;
      cout << setw(5) << " " << setw(40) << "-timeDistributionFile <file name>" << "File do dump peak time distributions to. Requires -coincidenceFile." << endl; 
      cout << setw(5) << " " << setw(40) << "-bgTolerance <double value>" << "Size around the peaks that background will be measured in order to determine if we have a real peak." << endl;
      cout << setw(5) << " " << setw(40) << "-help" << "Displays this help message." << endl;
      exit(0);
    }
  return myInterpreter;
}

string nsToReadableTime(double time)
{
  double second = 1E9;
  double minute = 60*second;
  double hour = 60*minute;
  double day = 24*hour;
  double month = 30*day;
  double year = 12*month;
  stringstream ss;
  if(((int)(time/year))>0)
    {
      ss << ((int)(time/year)) << "year" << (((int)(time/year))>1?"s":"");
      time-=year*((int)(time/year));
      ss << " ";
    }
  if(((int)(time/month))>0)
    {
      ss << ((int)(time/month)) << "month" << (((int)(time/month))>1?"s":"");
      time-=month*((int)(time/month));
      ss << " ";
    }
  if(((int)(time/day))>0)
    {
      ss << ((int)(time/day)) << "day" << (((int)(time/day))>1?"s":"");
      time-=day*((int)(time/day));
      ss << " ";
    }
  if(((int)(time/hour))>0)
    {
      ss << ((int)(time/hour)) << "hour" << (((int)(time/hour))>1?"s":"");
      time-=hour*((int)(time/hour));
      ss << " ";
    }
  if(((int)(time/minute))>0)
    {
      ss << ((int)(time/minute)) << "minute" << (((int)(time/minute))>1?"s":"");
      time-=minute*((int)(time/minute));
      ss << " ";
    }
  if(((int)(time/second))>0)
    {
      ss << ((int)(time/second)) << "second" << (((int)(time/second))>1?"s":"");
      time-=second*((int)(time/second));
       ss << " ";
    }
  return ss.str();
}

void printDetectorCount(CoincidenceFinder * F, int numberPerRow)
{
  vector<int> count = F->getDetectorCount();
  int rowbreak = 0;
  cout << "Detector count:" << endl;
  cout << setfill(' ');
  for(vector<int>::iterator it = count.begin(); it!=count.end(); it++)
    {
      cout << setw(5) << *it << " ";
      if(++rowbreak>=numberPerRow)
	{
	  rowbreak=0;
	  cout << endl;
	}
    }
  cout << endl;
}

void printStatistics(CoincidenceFinder * F)
{
  //For statistic purposes.
  cout << "====================";
  cout << "Statistics:";
  cout << "====================";
  cout << endl;
  cout << setiosflags(ios::left);
  cout << setfill('_');
  cout << setw(50) << "# events processed:" << F->getNoHits() << endl;
  cout << setw(50) << "Time of last implantation: " << nsToReadableTime(F->getTimeSpan()) << endl;
  cout << "Classification of events:" << endl;
  cout << setw(50) << "---># implantations:" << F->getNoImplantations() << endl;
  cout << setw(50) << "# Correct implantations:" << F->getNoCorrectImplantations() << endl;
  cout << setw(50) << "# Double hits:" << F->getNoDoubleHit() << endl;
  cout << setw(50) << "---># decays:" << F->getNoDecays() << endl;
  cout << setw(50) << "# Non-associated decays:" << F->getNoNonAssociatedDecays() << endl;
  cout << setw(50) << "# Decays without Ge-hit:" << F->getNoGeHit() << endl;
  cout << setw(50) << "# Correctly connected implant-decay:" << F->getNoCorrConnected() << endl;
  cout << setw(50) << "# Incorrectly connected implant-decay:" << F->getNoErrConnected() << endl;
  cout << setw(50) << "---># other:" << F->getNoOther() << endl;
  cout << setw(50) << "# Destroyed by other:" << F->getNoDestroyedByOther() << endl;
  cout << endl;
  cout << "Reasons for other-classification:" << endl;
  cout << setw(50) << "Particle went through FSP and BSP:" << F->getFailureReason(0) << endl;
  cout << setw(50) << "Particle through FSP but no implant:" << F->getFailureReason(1) << endl;
  cout << setw(50) << "Particle through FSP but implant in several tubes:" << F->getFailureReason(2) << endl;
  cout << setw(50) << "Particle not through SP, and no tube:" << F->getFailureReason(3) << endl;
  cout << setw(50) << "Particle not through SP, and several tubes:" << F->getFailureReason(4) << endl;
  cout << setw(50) << "Particle through BSP, not FSP, no tube:" << F->getFailureReason(5) << endl;
  cout << setw(50) << "Particle through BSP, not FSP, several tubes:" << F->getFailureReason(6) << endl;
  cout << setw(50) << "Particle through BSP, not FSP, one tube:" << F->getFailureReason(7) << endl;

  cout << endl;
  
  cout << setw(50) << "Found coincidences:" << F->getNoFoundCoincidences() << endl; 
  cout << setw(50) << "# correct:" << F->getNoCorrCoincidence() << endl;
  cout << setw(50) << "Ratio:" << (float)F->getNoCorrCoincidence()/((float)F->getNoFoundCoincidences())*100 << "%" <<  endl;
  
  cout << endl;
}

void printSettings(Settings * toPrint)
{
  cout << "++++++++++++++++";
  cout << "Analysis settings:";
  cout << "++++++++++++++++";
  cout << endl;
  cout << setiosflags(ios::left);
  cout << setfill('_');
  cout << setw(50) << "Coincidence file:" << toPrint->coincidenceFile << endl;
  cout << setw(50) << "Time distribution file:" << toPrint->timeDistributionFile << endl;
  cout << setw(50) << "Mix file (data to analyze):" << toPrint->mixedFile << endl;
  cout << setw(50) << "Gamma data file:" << toPrint->gammaFile << endl;
  cout << endl;
  cout << setw(50) << "Tolerance (MeV):" << toPrint->tolerance << endl;
  cout << setw(50) << "Background tolerance (MeV):" << toPrint->bgTolerance << endl;
  cout << setw(50) << "#Multi-implantations allowed:" << toPrint->multiImplant << endl;
  cout << setw(50) << "Number of scintillator tubes:" << toPrint->nTubes << endl;
  cout << setw(50) << "Number of tubes per row:" << toPrint->nTubesPerRow << endl;
  cout << setw(50) << "Ge detector epsilon (MeV):" << toPrint->geEpsilon << endl;
  cout << setw(50) << "Beta detector epsilon (MeV):" << toPrint->betaEpsilon << endl;
  cout << setw(50) << "Domination ratio:" << toPrint->dRatio << endl;
  cout << setw(50) << "Minimum Ge energy (MeV):" << toPrint->minGe << endl;
  cout << setw(50) << "Maximum Ge energy (MeV):" << toPrint->maxGe << endl;
  cout << setw(50) << "Maximum decay wait (ns):" << toPrint->maxDecayWait << endl;
  cout << setw(50) << "Decay cut (ns):" << toPrint->decayCut << endl;
  cout << setw(50) << "Force correct identification:" << (toPrint->forceCorrect?"yes":"no") << endl;
  cout << setw(50) << "A range:" << toPrint->minA << "-" << toPrint->maxA << endl;
  cout << setw(50) << "Z range:" << toPrint->minZ << "-" << toPrint->maxZ << endl;
  cout << setw(50) << "Display detector count:" << (toPrint->detectorCount?"yes":"no") << endl;
  cout << setw(50) << "Display info about ID failures:" << (toPrint->failInfo?"yes":"no") << endl;
  cout << endl;
}

Settings * initSettings(CommandLineInterpreter * myInterpreter)
{
  Settings * S = new Settings();
  S->tolerance = 0.003; //MeV
  if(myInterpreter->readFlaggedCommand("tolerance").size()==1)
    S->tolerance = atof(myInterpreter->readFlaggedCommand("tolerance").front().c_str());
  S->bgTolerance = 0.05; //MeV
  
  S->multiImplant = myInterpreter->readFlaggedCommand("multiImplant").size()==1?atoi(myInterpreter->readFlaggedCommand("multiImplant").front().c_str()):1;
  
  S->nTubes = myInterpreter->readFlaggedCommand("numberOfTubes").size()==1?
    atoi(myInterpreter->readFlaggedCommand("numberOfTubes").front().c_str()):40;
  S->nTubesPerRow = myInterpreter->readFlaggedCommand("numberPerRow").size()==1?
    atoi(myInterpreter->readFlaggedCommand("numberPerRow").front().c_str()):10;

  S->geEpsilon = myInterpreter->readFlaggedCommand("geEpsilon").size()==1?atof(myInterpreter->readFlaggedCommand("geEpsilon").front().c_str()):5E-2;
  S->betaEpsilon = myInterpreter->readFlaggedCommand("betaEpsilon").size()==1?atof(myInterpreter->readFlaggedCommand("betaEpsilon").front().c_str()):5E-1;

  S->dRatio = myInterpreter->readFlaggedCommand("dominationFactor").size()==1?atof(myInterpreter->readFlaggedCommand("dominationFactor").front().c_str()):1E3;
  S->minGe = myInterpreter->readFlaggedCommand("gLow").size()==1?atof(myInterpreter->readFlaggedCommand("gLow").front().c_str()):5E-1;
  
  S->maxGe = myInterpreter->readFlaggedCommand("gHigh").size()==1?atof(myInterpreter->readFlaggedCommand("gHigh").front().c_str()):3E0;
  
  S->maxDecayWait=  myInterpreter->readFlaggedCommand("maxDecayWait").size()==1?atof(myInterpreter->readFlaggedCommand("maxDecayWait").front().c_str()):1E10;
  
  S->decayCut=  myInterpreter->readFlaggedCommand("decayCut").size()==1?atof(myInterpreter->readFlaggedCommand("decayCut").front().c_str()):1E20;

  S->mixedFile = myInterpreter->readFlaggedCommand("mixedFile").size()==1?(myInterpreter->readFlaggedCommand("mixedFile").front()):("");
  S->forceCorrect = !myInterpreter->readFlaggedCommand("forceCorrect").empty();

  S->gammaFile =myInterpreter->readFlaggedCommand("gammaFile").size()==1?(myInterpreter->readFlaggedCommand("gammaFile").front()):("");
  S->minA = ((myInterpreter->readFlaggedCommand("minA").size()==1)?atoi(myInterpreter->readFlaggedCommand("minA").front().c_str()):(-1000));
  S->maxA = ((myInterpreter->readFlaggedCommand("maxA").size()==1)?atoi(myInterpreter->readFlaggedCommand("maxA").front().c_str()):(1000));
  S->minZ = ((myInterpreter->readFlaggedCommand("minZ").size()==1)?atoi(myInterpreter->readFlaggedCommand("minZ").front().c_str()):(-1000));
  S->maxZ = ((myInterpreter->readFlaggedCommand("maxZ").size()==1)?atoi(myInterpreter->readFlaggedCommand("maxZ").front().c_str()):(1000));

  S->coincidenceFile = myInterpreter->readFlaggedCommand("coincidenceFile").size()==1?(myInterpreter->readFlaggedCommand("coincidenceFile").front()):("");

  S->detectorCount = !myInterpreter->readFlaggedCommand("detectorCount").empty();

  S->timeDistributionFile = (myInterpreter->readFlaggedCommand("timeDistributionFile").size()==1)?(myInterpreter->readFlaggedCommand("timeDistributionFile").front()):"";
  S->failInfo = !myInterpreter->readFlaggedCommand("failInfo").empty();

  return S;
}

int main(int argc, char **argv)
{
  CommandLineInterpreter * myInterpreter = decodeInput(argc, argv);
  Settings * S = initSettings(myInterpreter);
  printSettings(S);

  FileEventParser * myEventParser = new FileEventParser((char*)S->mixedFile.c_str(), S->nTubes, S->betaEpsilon, S->dRatio);

  list<pair<EventHit*, EventHit*> > foundCoincidences;

  CoincidenceFinder * myFinder = new CoincidenceFinder(myEventParser, S->maxDecayWait, S->nTubes, S->geEpsilon, S->minGe, S->maxGe, S->multiImplant, S->decayCut);


  while(myFinder->hasMoreCoincidences())    
    {
      foundCoincidences.push_back(myFinder->getNextCoincidence());
    }

  printStatistics(myFinder);


  if(S->coincidenceFile.size()>0)
    {
      FILE * coinFile = fopen(S->coincidenceFile.c_str(),"w");
      list<pair<EventHit*, EventHit*> > deletable(foundCoincidences);
      FILE * tFile = NULL;
      if(S->timeDistributionFile.size()>0)
	{
	  tFile = fopen(S->timeDistributionFile.c_str(),"w");
	}

      if(coinFile!=NULL)
	{
	  int count = 0;
	  while(!deletable.empty())
	    {
	      ++count;
	      GammaEnergyChart * myEnergyChart = 
		new GammaEnergyChart((char*)S->gammaFile.c_str(), S->minA, S->maxA, S->minZ, S->maxZ, S->tolerance, S->bgTolerance);
	      
	      GammaIdentifier * myIdentifier = new GammaIdentifier(myEnergyChart, S->tolerance, S->minGe, S->maxGe, S->bgTolerance, S->forceCorrect);
	      int A = deletable.front().first->A;
	      int Z = deletable.front().first->Z;
	      for(list<pair<EventHit*, EventHit*> >::iterator it =  deletable.begin(); it!=deletable.end(); it++)
		{
		  
		  if(it->first->A==A && it->first->Z==Z)
		    {
		      myIdentifier->addCoincidence(*it);
		      it=deletable.erase(it);
		      --it;
		    }
		}
	      fprintf(coinFile,"%s\n",myIdentifier->getMATLABstring(count).c_str());
	      if(tFile!=NULL)
		{
		  fprintf(tFile,"%s\n",myIdentifier->getPeakString().c_str());
		}
	      
	      delete myIdentifier;
	      delete myEnergyChart;
	    }
	}
    }
  
  if(S->detectorCount)
    {
      printDetectorCount(myFinder, S->nTubesPerRow);
    }

  if(S->failInfo)
    {
      cout << "The failed ID:s:" << endl << endl;
      for(list<pair<EventHit*, EventHit*> >::iterator it =  foundCoincidences.begin(); it!=foundCoincidences.end(); it++)
	{
	  if(it->first->eventno!=it->second->eventno)
	    {
	      cout << "Time diff (ms): " << (it->second->time - it->first->time)/1E6 << endl;
	      cout << it->first->toString();
	      cout << it->second->toString() << endl;
	      cout << endl;
	    }
	}
    }


  set<EventHit*> toDelete;
  //Clean up.
  for(list<pair<EventHit*, EventHit*> >::iterator it =  foundCoincidences.begin(); it!=foundCoincidences.end(); it++)
    {
      toDelete.insert(it->first);
      toDelete.insert(it->second);
    }
  //we have to check as so not make a multiple-delete... that would indeed be bad.
  for(set<EventHit*>::iterator it = toDelete.begin(); it!=toDelete.end(); it++)
    {
      delete *it;
    }

  delete myEventParser;
  return 0;
}
