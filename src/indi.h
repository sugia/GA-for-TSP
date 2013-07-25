/*
 * indi.h
 *   created on: April 24, 2013
 * last updated: June 13, 2013
 *       author: liushujia
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
	bool operator == (  const TIndi& indi2 );	// 判断两路径是否相同 

	int fN;						// 城市数目
	int** fLink;				// fLink[i][]表示路径中i的两个相邻的城市
	int fEvaluationValue;		// TSP路径长度
};

#endif
