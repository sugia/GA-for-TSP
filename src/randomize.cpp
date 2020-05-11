/*
 * randomize.cpp
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */

#ifndef __RAND__
#include "randomize.h"
#endif

TRandom* tRand = NULL;

void InitURandom(){
	int seed;
	unsigned short seed16v[3];
	seed = 1111;
	seed16v[0] = 100;
	seed16v[1] = 200;
	seed16v[2] = seed;
	tRand = new TRandom();
	srand( seed );
}

void InitURandom( int dd ){
	int seed;
	unsigned short seed16v[3];
	seed = dd;
	seed16v[0] = 100;
	seed16v[1] = 200;
	seed16v[2] = seed;
	tRand = new TRandom();
	srand( seed );
}

TRandom::TRandom(){}
TRandom::~TRandom(){}

int TRandom::Integer(int minNumber, int maxNumber){
	return minNumber + (rand() % (maxNumber - minNumber + 1));
}

double TRandom::Double(double minNumber, double maxNumber){
	return minNumber + rand() % (int)(maxNumber - minNumber);
}

void TRandom::permutation(vector<int>& array, int numOfElement, int numOfSample){
	if(numOfElement <= 0) {
		return;
	}
	vector<int> visited(numOfElement, 0);

	for (int i = 0; i < numOfSample; i++) {
		int r = rand() % (numOfElement - i);
		while (visited[r] == 1) {
			r = (r + 1) % numOfElement;
		}
		array[i] = r;
		visited[r] = 1;
	}
}

double TRandom::normalDistribution(double mu, double sigma){
	double U1,U2,X;
	double PI = 3.1415926;
	while( 1 ){
		U1 = this->Double( 0.0, 1.0 );
		if( U1 != 0.0 ) break;
	}
	U2 = this->Double( 0.0, 1.0 );
	X = sqrt(-2.0*log(U1)) * cos(2*PI*U2);
	return( mu + sigma*X );
}

void TRandom::shuffle(vector<int>& array, int numOfElement){
	vector<int> a(numOfElement);
	vector<int> b(numOfElement);

	this->permutation(b, numOfElement, numOfElement);
	for (int i = 0; i < numOfElement; ++i) {
		a[ i ] = array[ i ];
	}
	for (int i = 0; i < numOfElement; ++i) {
		array[ i ] = a[ b[ i ] ];
	}
}
