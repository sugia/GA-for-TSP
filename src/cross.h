/*
 * cross.h
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */

#ifndef __Cross__
#define __Cross__

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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class TCross{
public:
	TCross( int N );
	~TCross();
	void doIt( TIndi& tKid, TIndi& tPa2, int numOfKids, int flagP, int flagC[ 10 ], vector<vector<int>>& fEdgeFreq ); // EAX entry point
	void setParents( const TIndi& tPa1, const TIndi& tPa2, int flagC[ 10 ], int numOfKids ); // sets parents
	void setABcycle( const TIndi& parent1, const TIndi& parent2, int flagC[ 10 ], int numOfKids ); // sets ab cycle

	void swap(int &x, int &y);
	void formABcycle(); // saves ab cycle
	void changeSol( TIndi& tKid, int ABnum, int type ); // generates intermediate solution from ab cycle

	void makeCompleteSol( TIndi& tKid ); // the 5th step of EAX
	void makeUnit(); // the 5-1th step of EAX
	void backToPa1( TIndi& tKid ); // rolls back p_a
	void goToBest( TIndi& tKid ); // sets tKid to the best solutions of child generation

	void incrementEdgeFreq(vector<vector<int>>& fEdgeFreq); // increates fEdgeFreq[][]
	int calAdpLoss(vector<vector<int>>& fEdgeFreq); // calculates the average road distance from fEdgeFreq[][]
	double calEntLoss(vector<vector<int>>& fEdgeFreq); // calculates the difference of edge entropy from fEdgeFreq[][]

	void setWeight( const TIndi& parent1, const TIndi& parent2 );	// Block2
	int	calCNaive();
	void searchEset( int num );
	void addAB( int num );
	void deleteAB( int num );

	int fNumOfGeneratedCh;
	TEvaluator* eval;
	int Npop;

private:
	TIndi tBestTmp;
	int fFlagImp;
	int fN;
	int r;
	int exam;
	int examFlag;
	int flagSt;
	int flagCycle;
	int prType;
	int chDis;
	int koritsuMany;
	int bunkiMany;
	int st;
	int ci;
	int pr;
	int stock;
	int stAppear;
	int fEvalType;
	int fEsetType;
	int fNumOfABcycleInESet;
	int fNumOfABcycle;
	int fPosiCurr;
	int fMaxNumOfABcycle;

	vector<int> koritsu;
	vector<int> bunki;
	vector<int> koriInv;
	vector<int> bunInv;
	vector<int> checkKoritsu;
	vector<int> fRoute;
	vector<int> fPermu;
	vector<int> fC;
	vector<int> fJun;
	vector<int> fOrd1;
	vector<int> fOrd2;

	vector<vector<int>> nearData;
	vector<vector<int>> fABcycle;

	// speeds up start
	int fNumOfUnit;
	int fNumOfSeg;
	int fNumOfSPL;
	int fNumOfElementInCU;
	int fNumOfSegForCenter;
	int fGainModi;
	int fNumOfModiEdge;
	int fNumOfBestModiEdge;
	int fNumOfAppliedCycle;
	int fNumOfBestAppliedCycle;

	vector<int> fOrder;
	vector<int> fInv;
	vector<int> fSegUnit;
	vector<int> fSegPosiList;
	vector<int> LinkAPosi;
	vector<int> fPosiSeg;
	vector<int> fNumOfElementInUnit;
	vector<int> fCenterUnit;
	vector<int> fListOfCenterUnit;
	vector<int> fSegForCenter;
	vector<int> fGainAB;
	vector<int> fAppliedCylce;
	vector<int> fBestAppliedCylce;

	vector<vector<int>> fSegment;
	vector<vector<int>> LinkBPosi;
	vector<vector<int>> fModiEdge;
	vector<vector<int>> fBestModiEdge;
	// speeds up end

	// block2
	int fNumOfUsedAB;
	int fNumC;
	int fNumE;
	int fTmax;
	int fMaxStag;
	int fNumOfABcycleInEset;
	int fDisAB;
	int fBestNumC;
	int fBestNumE;

	vector<int> fNumOfElementINAB;
	vector<int> fWeightSR;
	vector<int> fWeightC;
	vector<int> fUsedAB;
	vector<int> fMovedAB;
	vector<int> fABcycleInEset;

	vector<vector<int>> fInEffectNode;
	vector<vector<int>> fWeightRR;
};

#endif
