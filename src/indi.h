/*
 * indi.h
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */

#ifndef __INDI__
#define __INDI__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

class TIndi{
public:
	TIndi();
	~TIndi();
	void define( int N );
	TIndi& operator = ( const TIndi& src );
	bool operator == (  const TIndi& indi2 ); // checks if two roads are equivalent

	int fN; // the number of cities
	int** fLink; // fLink[i][] is the two adjacent cities of city i
	int fEvaluationValue; // the road length of TSP
};

#endif
