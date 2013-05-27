#!/bin/bash

for i in $(ls MixedResults/Report_C17area_finished/)
do 
    ./analysis -gammaFile Gammalista.txt -minA 5 -maxA 25 -minZ 2 -maxZ 15 -gLow 0.5 -gHigh 3 -maxDecayWait 1E9 -bgTolerance 50E-3 -tolerance 3E-3 -detectorCount -mixedFile MixedResults/Report_C17area_finished/$i -numberOfTubes 40 -coincidenceFile AnalyzedResults/Report_C17area/Cd1e9D1$i.m -timeDistributionFile AnalyzedResults/Report_C17area/Td1e9D1$i > AnalyzedResults/Report_C17area/Rd1e9D1$i

done