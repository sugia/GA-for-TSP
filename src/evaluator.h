/*
 * evaluator.h
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */

#ifndef __EVALUATOR__
#define __EVALUATOR__

#ifndef __INDI__
#include "indi.h"
#endif

#include <string.h>
#include <assert.h>

class TEvaluator{
public:
	TEvaluator();
	~TEvaluator();
	void setInstance( char filename[] ); // sets variables
	void doIt( TIndi& indi ); // sets indi.fEvaluationValue
	void writeTo( FILE* fp, TIndi& indi ); // prints out TSP solution
	bool checkValid( int* array, int value ); // checks if TSP solution is valid

	int fNearNumMax; // the maximum value of the number of nearby points
	int **fNearCity; // NearCity[i][k] is the k points that with a shortest distance from point i
	int **fEdgeDis; // EdgeDis[i][j] is the distance from city i to city j
	int Ncity; // the number of cities
	double *x; // x[i] is the x coordinate of city i
	double *y; // y[i] is the y coordinate of city i
	int *Array; // the index of best solution
};

#endif
