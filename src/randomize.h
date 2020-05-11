/*
 * randomize.h
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */

#ifndef __RAND__
#define __RAND__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
using namespace std;

extern void InitURandom( int );
extern void InitURandom( void );

class TRandom {
public:
	TRandom();
	~TRandom();
	int Integer(int minNumber, int maxNumber);
	double Double(double minNumber, double maxNumber);
	double normalDistribution(double mu, double sigma);
	void permutation(vector<int>& array, int numOfelement, int numOfSample); // generates random permutation of a given population
	void shuffle(vector<int>& array, int numOfElement); // random shuffles individuals in a given population
};

extern TRandom* tRand;


#endif


