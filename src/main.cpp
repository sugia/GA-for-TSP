/*
 * main.cpp
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */

#ifndef __ENVIRONMENT__
#include "environment.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main( int argc, char* argv[] ){
	InitURandom(); 
	int maxNumOfTrial;

	TEnvironment* gEnv = new TEnvironment();
	gEnv->fFileNameTSP=(char*)malloc(100);
	
	/*
	scanf("%d", &maxNumOfTrial);
	scanf("%s", dstFile);
	scanf("%d", &gEnv->fNumOfPop);
	scanf("%d", &gEnv->fNumOfKids);
	*/
	vector<string> exampleTspMaps{
		"../tc/eil101.tsp",
		"../tc/att532.tsp",
		"../tc/rat575.tsp",
		"../tc/fnl4461.tsp",
		"../tc/ja9847.tsp",
	};

	int id = -1;
	do {
		cout << "Please type in 0~4 to choose a dataset." << endl;
		for (int i = 0; i < exampleTspMaps.size(); i++) {
			cout << i << ": " << exampleTspMaps[i] << endl;
		}
		scanf("%d", &id);
	} while (id < 0 || id > 4);

	strcpy(gEnv->fFileNameTSP, exampleTspMaps[id].c_str());
 	//scanf("%s", gEnv->fFileNameTSP);
	
	maxNumOfTrial = 5; // repeated times
	gEnv->Npop = 100; // number of items
	gEnv->Nch = 30; // number of offsprings

	cout << "Initializing ..." << endl;
	gEnv->define();
	cout << "Building solution ..." << endl;
	for (int n = 0; n < maxNumOfTrial; ++n){ 
		gEnv->doIt(); 
		gEnv->printOn(n);
		gEnv->writeBest();
	}
	//system("pause");
	return 0;
}
