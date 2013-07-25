/*
 * randomize.h
 *   created on: April 24, 2013
 * last updated: June 13, 2013
 *       author: liushujia
 */

#ifndef __RAND__
#define __RAND__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

extern void InitURandom( int );    
extern void InitURandom( void );   

class TRandom {
public:
	TRandom();
	~TRandom();
	int Integer( int minNumber, int maxNumber ); 
	double Double( double minNumber, double maxNumber );
	double normalDistribution( double mu, double sigma );
	void permutation( int *array, int numOfelement, int numOfSample );	// 随机产生种群的一个排列
	void shuffle( int *array, int numOfElement );						// 根据产生的排列调整种群中的个体位置
};

extern TRandom* tRand;


#endif


