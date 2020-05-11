/*
 * environment.h
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */

#ifndef __ENVIRONMENT__
#define __ENVIRONMENT__

#ifndef __INDI__
#include "indi.h"
#endif

#ifndef __RAND__
#include "randomize.h"
#endif

#ifndef __EVALUATOR__
#include "evaluator.h"
#endif

#ifndef __Cross__
#include "cross.h"
#endif

#ifndef __KOPT__
#include "kopt.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <vector>

class TEnvironment{
public:
	TEnvironment();
	~TEnvironment();

	void define(); // global initialization
	void doIt(); // entry point of genetic algorithm
	void init(); // initializes genetic algorithm
	bool terminationCondition(); // condition to termination the genetic algorithm
	void setAverageBest(); // sets the average distance of TSP and the shortest distance of TSP

	void initPop(); // initializes population
	void selectForMating(); // selects parents
	void generateKids( int s ); // generates and selects children
	void getEdgeFreq(); // calculates the frequency of each edge

	void printOn( int n ); // logs out results
	void writeBest(); // logs out the best TSP solution

	TEvaluator* fEvaluator; // distance of each edge
	TCross* tCross; // intersection of edge sets
	TKopt* tKopt; // local search (2-opt neighborhood)
	char *fFileNameTSP; // file name of TSP

	int Npop; // the number of population
	int Nch; // the number of children generated from one pair of parent
	TIndi* tCurPop; // the member of the current population
	TIndi tBest; // the best solution from the current population
	int fCurNumOfGen; // the number of generations of the current population
	long int fAccumurateNumCh; // accumulated number of children so far

	int fBestNumOfGen; // the number of generations that generates the current best solution
	long int fBestAccumeratedNumCh; // accumulated number of generations of the current best solution
	vector<vector<int>> fEdgeFreq; // edge frequency of a population
	double fAverageValue; // average road length of TSP in a population
	int fBestValue; // road length of the best solution in a population
	int fBestIndex;	// index of the best solution in a population

	vector<int> fIndexForMating; // list for edge cross operation
	int fStagBest; // accumulated number of generations that doesn't generate a better solution compared to previous generation
	int fFlagC[ 10 ]; // EAX method and selection strategy
	int fStage; // the current step of genetic algorithm
	int fMaxStagBest; // the genetic algorithm goes into the next stage when fStagBest == fMaxStagBest
	int fCurNumOfGen1; // the number of generations when stage 1 completes

	clock_t fTimeStart, fTimeInit, fTimeEnd; // saves calculation time
};

#endif
