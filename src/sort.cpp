/*
 * sort.cpp
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */

#ifndef __Sort__
#include "sort.h"
#endif

TSort* tSort = NULL;

void InitSort(){
	tSort = new TSort();
}

void swap(int &x, int &y){
	int s=x;
	x=y;
	y=s;
}

void selectionSort(vector<int>& Arg, int l, int r){
	int id;
	for(int i=l;i<r;++i){
		id=i;
		for(int j=i+1;j<=r;++j)
			if(Arg[j]<Arg[id]) id=j;
		swap(Arg[i], Arg[id]);
	}
}

int partition(vector<int>& Arg, int l, int r){
	int id=l+rand()%(r-l+1);
	swap(Arg[l], Arg[id]);
	id=l;
	for(int i=l+1;i<=r;++i)
		if(Arg[i]<Arg[l]) swap(Arg[++id], Arg[i]);
	swap(Arg[l], Arg[id]);
	return id;
}

void quickSort(vector<int>& Arg, int l, int r){
	if(l<r){
		if(r-l<20){	// utilizes selection sort for small batch of data
			selectionSort(Arg, l, r);
			return ;
		}
		int mid=partition(Arg, l, r);
		quickSort(Arg, l, mid-1);
		quickSort(Arg, mid+1, r);
	}
}

TSort::TSort(){}
TSort::~TSort(){}

void TSort::index(vector<double>& Arg, int numOfArg, vector<int>& indexOrderd, int numOfOrd){
	int indexBest = 0;
	double valueBest;
	int *checked = new int [ numOfArg ];
	for( int i = 0 ; i < numOfArg ; ++i ) checked[ i ] = 0;
	for( int i = 0; i < numOfOrd; ++i ){
		valueBest = 99999999999.9;
		for( int j = 0; j < numOfArg; ++j ){
			if( ( Arg[j] < valueBest ) && checked[j]==0){
				valueBest = Arg[j];
				indexBest = j;
			}
		}
		indexOrderd[ i ]=indexBest;
		checked[ indexBest ]=1;
	}
	delete [] checked;
}

void TSort::indexB(vector<double>& Arg, int numOfArg, vector<int>& indexOrderd, int numOfOrd){
	int indexBest = 0;
	double valueBest;
	int *checked = new int [ numOfArg ];
	for( int i = 0 ; i < numOfArg ; ++i ) checked[ i ] = 0;
	for( int i = 0; i < numOfOrd; ++i ){
		valueBest = -99999999999.9;
		for( int j = 0; j < numOfArg; ++j ){
			if( ( Arg[j] > valueBest ) && checked[j]==0){
				valueBest = Arg[j];
				indexBest = j;
			}
		}
		indexOrderd[ i ]=indexBest;
		checked[ indexBest ]=1;
	}
	delete [] checked;
}

void TSort::index(vector<int>& Arg, int numOfArg, vector<int>& indexOrderd, int numOfOrd){
	int indexBest = 0;
	int valueBest;
	int *checked = new int [ numOfArg ];
	for( int i = 0 ; i < numOfArg ; ++i ) checked[ i ] = 0;
	for( int i = 0; i < numOfOrd; ++i ){
		valueBest = 99999999;
		for( int j = 0; j < numOfArg; ++j ){
			if( ( Arg[j] < valueBest ) && checked[j]==0){
				valueBest = Arg[j];
				indexBest = j;
			}
		}
		indexOrderd[ i ]=indexBest;
		checked[ indexBest ]=1;
	}
	delete [] checked;
}

void TSort::indexB(vector<int>& Arg, int numOfArg, vector<int>& indexOrderd, int numOfOrd){
	int indexBest = 0;
	int valueBest;
	int *checked = new int [ numOfArg ];
	for( int i = 0 ; i < numOfArg ; ++i ) checked[ i ] = 0;
	for( int i = 0; i < numOfOrd; ++i ){
		valueBest = -999999999;
		for( int j = 0; j < numOfArg; ++j ){
			if( ( Arg[j] > valueBest ) && checked[j]==0){
				valueBest = Arg[j];
				indexBest = j;
			}
		}
		indexOrderd[ i ]=indexBest;
		checked[ indexBest ]=1;
	}
	delete [] checked;
}

void TSort::sort(vector<int>& Arg, int numOfArg){
	//selectionSort(Arg, 0, numOfArg-1);
	quickSort(Arg, 0, numOfArg-1);
}

