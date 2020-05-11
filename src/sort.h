/*
 * sort.h
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */

#ifndef __SORT__
#define __SORT__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <vector>
using namespace std;

void InitSort();
void swap(int &x, int &y);
void selectionSort(vector<int>& Arg, int l, int r);
int partition(vector<int>& Arg, int l, int r); // partition for quick sort
void quickSort(vector<int>& Arg, int l, int r);

class TSort{
public:
	TSort();
	~TSort();
	void index(vector<double>& Arg, int numOfArg, vector<int>& indexOrderd, int numOfOrd);
	void index(vector<int>& Arg, int numOfArg, vector<int>& indexOrderd, int numOfOrd);
	void indexB(vector<double>& Arg, int numOfArg, vector<int>& indexOrderd, int numOfOrd);
	void indexB(vector<int>& Arg, int numOfArg, vector<int>& indexOrderd, int numOfOrd);
	void sort(vector<int>& Arg, int numOfArg);
};

extern TSort* tSort;

#endif
