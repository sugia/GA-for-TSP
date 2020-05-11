/*
 * kopt.h
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */

#ifndef __KOPT__
#define __KOPT__

#ifndef __RAND__
#include "randomize.h"
#endif

#ifndef __Sort__
#include "sort.h"
#endif

#ifndef __INDI__
#include "indi.h"
#endif

#ifndef __EVALUATOR__
#include "evaluator.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

class TKopt{
public:
	TKopt( int N );
	~TKopt();
	void setInvNearList();
	void transIndiToTree( TIndi& indi );
	void transTreeToIndi( TIndi& indi );
	void doIt( TIndi& tIndi );

	int getNext( int t );
	int getPrev( int t );
	int turn( int &orient );

	void sub();
	void incrementImp( int flagRev );
	void combineSeg( int segL, int segS );

	void checkDetail();
	void checkValid();
	void swap(int &x, int &y);
	void makeRandSol( TIndi& indi );

	TEvaluator* eval;

private:
	int fN;
	int fFixNumOfSeg;
	int fNumOfSeg;
	int fFlagRev;
	int fTourLength;

	int **fLink;
	int **fLinkSeg;
	int **fCitySeg;
	int **fInvNearList;

	int *fT;
	int *fB;
	int *fSegCity;
	int *fOrdCity;
	int *fOrdSeg;
	int *fOrient;
	int *fSizeSeg;
	int *fActiveV;
	int *fNumOfINL;
	int *fArray;
	int *fCheckN;
	int *fGene;
};

#endif
