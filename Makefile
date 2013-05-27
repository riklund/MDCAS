#This is a makefile for compiling the DataAnalys analyzing program and supplementary software.
#(c) Rikard Lundmark 2012-2013. All rights reserved.

SHELL = /bin/sh

INCDIR = include

BINDIR = bin

SRCDIR = src

TSTDIR = test

TSTSRCDIR = source

TSTINCDIR = include

CFLAGS = -Wall -g -I $(INCDIR)

CTESTFLAGS = -Wall -g -I $(TSTDIR)/$(TSTINCDIR) -I $(INCDIR)

CC = g++ -Wl,--no-as-needed

all: directory analysis tests
	./$(BINDIR)/RunTests

directory:
	+ (mkdir -p $(BINDIR))

tests: $(BINDIR)/RunTests

$(BINDIR)/GammaEnergyChart.o: $(SRCDIR)/GammaEnergyChart.cc $(INCDIR)/GammaEnergyChart.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/GammaEnergyChart.cc -o $(BINDIR)/GammaEnergyChart.o

$(BINDIR)/analysis.o: $(SRCDIR)/analysis.cc $(INCDIR)/analysis.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/analysis.cc -o $(BINDIR)/analysis.o

$(BINDIR)/FileEventParser.o: $(SRCDIR)/FileEventParser.cc $(INCDIR)/FileEventParser.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/FileEventParser.cc -o $(BINDIR)/FileEventParser.o

$(BINDIR)/CoincidenceFinder.o: $(SRCDIR)/CoincidenceFinder.cc $(INCDIR)/CoincidenceFinder.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/CoincidenceFinder.cc -o $(BINDIR)/CoincidenceFinder.o

$(BINDIR)/CommandLineArgument.o: $(SRCDIR)/CommandLineArgument.cc $(INCDIR)/CommandLineArgument.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/CommandLineArgument.cc -o $(BINDIR)/CommandLineArgument.o

$(BINDIR)/CommandLineException.o: $(SRCDIR)/CommandLineException.cc $(INCDIR)/CommandLineException.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/CommandLineException.cc -o $(BINDIR)/CommandLineException.o

$(BINDIR)/CommandLineInterpreter.o: $(SRCDIR)/CommandLineInterpreter.cc $(INCDIR)/CommandLineInterpreter.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/CommandLineInterpreter.cc -o $(BINDIR)/CommandLineInterpreter.o


$(BINDIR)/EventHit.o: $(SRCDIR)/EventHit.cc $(INCDIR)/EventHit.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/EventHit.cc -o $(BINDIR)/EventHit.o

$(BINDIR)/GammaIdentifier.o: $(SRCDIR)/GammaIdentifier.cc $(INCDIR)/GammaIdentifier.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/GammaIdentifier.cc -o $(BINDIR)/GammaIdentifier.o

$(BINDIR)/HitType.o: $(SRCDIR)/HitType.cc $(INCDIR)/HitType.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/HitType.cc -o $(BINDIR)/HitType.o

$(BINDIR)/ScorePair.o: $(SRCDIR)/ScorePair.cc $(INCDIR)/ScorePair.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/ScorePair.cc -o $(BINDIR)/ScorePair.o


$(BINDIR)/GammaLine.o: $(SRCDIR)/GammaLine.cc $(INCDIR)/GammaLine.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/GammaLine.cc -o $(BINDIR)/GammaLine.o


$(BINDIR)/ElementLookupTable.o: $(SRCDIR)/ElementLookupTable.cc $(INCDIR)/ElementLookupTable.hh
	$(CC) $(CFLAGS) -c $(SRCDIR)/ElementLookupTable.cc -o $(BINDIR)/ElementLookupTable.o


analysis: $(BINDIR)/analysis.o $(BINDIR)/FileEventParser.o $(BINDIR)/EventHit.o $(BINDIR)/HitType.o $(BINDIR)/GammaEnergyChart.o $(BINDIR)/CoincidenceFinder.o $(BINDIR)/CommandLineInterpreter.o $(BINDIR)/CommandLineArgument.o $(BINDIR)/CommandLineException.o $(BINDIR)/GammaIdentifier.o $(BINDIR)/ScorePair.o $(BINDIR)/GammaLine.o $(BINDIR)/ElementLookupTable.o
	$(CC) $(CFLAGS) $(BINDIR)/analysis.o $(BINDIR)/FileEventParser.o $(BINDIR)/HitType.o $(BINDIR)/GammaEnergyChart.o $(BINDIR)/EventHit.o $(BINDIR)/CoincidenceFinder.o  $(BINDIR)/CommandLineInterpreter.o $(BINDIR)/CommandLineArgument.o $(BINDIR)/CommandLineException.o $(BINDIR)/GammaIdentifier.o $(BINDIR)/ScorePair.o $(BINDIR)/GammaLine.o $(BINDIR)/ElementLookupTable.o -o analysis 

$(BINDIR)/FileEventParser_TEST.o: $(TSTDIR)/$(TSTSRCDIR)/FileEventParser_TEST.cc $(TSTDIR)/$(TSTINCDIR)/FileEventParser_TEST.hh
	$(CC) $(CTESTFLAGS) -c $(TSTDIR)/$(TSTSRCDIR)/FileEventParser_TEST.cc -o $(BINDIR)/FileEventParser_TEST.o

$(BINDIR)/EventHit_TEST.o: $(TSTDIR)/$(TSTSRCDIR)/EventHit_TEST.cc $(TSTDIR)/$(TSTINCDIR)/EventHit_TEST.hh
	$(CC) $(CTESTFLAGS) -c $(TSTDIR)/$(TSTSRCDIR)/EventHit_TEST.cc -o $(BINDIR)/EventHit_TEST.o


$(BINDIR)/GenericUnitTest.o: $(TSTDIR)/$(TSTSRCDIR)/GenericUnitTest.cc $(TSTDIR)/$(TSTINCDIR)/GenericUnitTest.hh
	$(CC) $(CTESTFLAGS) -c $(TSTDIR)/$(TSTSRCDIR)/GenericUnitTest.cc -o $(BINDIR)/GenericUnitTest.o

$(BINDIR)/RunTests: $(TSTDIR)/$(TSTSRCDIR)/RunTests.cc $(TSTDIR)/$(TSTINCDIR)/RunTests.hh $(BINDIR)/GenericUnitTest.o $(BINDIR)/FileEventParser_TEST.o $(BINDIR)/EventHit_TEST.o
	$(CC) $(CTESTFLAGS) $(TSTDIR)/$(TSTSRCDIR)/RunTests.cc $(BINDIR)/GenericUnitTest.o $(BINDIR)/FileEventParser_TEST.o $(BINDIR)/FileEventParser.o $(BINDIR)/EventHit.o $(BINDIR)/HitType.o $(BINDIR)/EventHit_TEST.o  -o $(BINDIR)/RunTests

clean: 
	-find . -type f -name "*~" -exec rm -f {} \;
	-find . -type f -name "*.o" -exec rm -f {} \;
	-find . -type f -name "\#*\#" -exec rm -f {} \;

cleanall: clean
	rm -rf bin/* analysis


document:
	+ doxygen doxyconf
	+ (cd doc/latex/ && pdflatex refman.tex && cd ../..)
	+ (cd doc/latex/ && pdflatex refman.tex && cd ../..)
	+ (cd doc/latex/ && pdflatex refman.tex && cd ../..)

publish: 
	+ rm -f MDCAS.tar.gz
	+ mkdir -p MDCAS
	+ cp -r Makefile MDCAS
	+ cp -r include MDCAS
	+ cp -r src MDCAS
	+ cp -r test MDCAS
	+ cp -r call.sh MDCAS
	+ cp -r doc/latex/refman.pdf MDCAS/ReferenceManual.pdf
	+ tar -cvzf MDCAS.tar.gz --exclude-vcs --exclude-backups MDCAS
	+ rm -rf MDCAS
	+ (mkdir -p ../Webbpage/MDCAS/)
	+ (cp MDCAS.tar.gz ../Webbpage/MDCAS)
	+ (cp -r doc/html/* ../Webbpage/MDCAS)
