/*
 * main.cpp
 *   created on: April 24, 2013
 * last updated: March 25, 2020
 *       author: liushujia
 */

#ifndef __ENVIRONMENT__
#include "environment.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
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

	cout<<"Please type in 1~5 to choose a dataset."<<endl;
	cout<<"1: ../tc/eil101.tsp"<<endl;
	cout<<"2: ../tc/att532.tsp"<<endl;
	cout<<"3: ../tc/rat575.tsp"<<endl;
	cout<<"4: ../tc/fnl4461.tsp"<<endl;
	cout<<"5: ../tc/ja9847.tsp"<<endl;

	int id=0;
	while(id<1 || id>5){
		scanf("%d", &id);
		if (id<1 || id>5)
			cout<<"Please type in 1~5 to choose a dataset."<<endl;
	}
	if (id==1) {
		gEnv->fFileNameTSP="../tc/eil101.tsp";
	} else if (id==2) {
		gEnv->fFileNameTSP="../tc/att532.tsp";
	} else if (id==3) {
		gEnv->fFileNameTSP="../tc/rat575.tsp";
	} else if (id==4) {
		gEnv->fFileNameTSP="../tc/fnl4461.tsp";
	} else if (id==5) {
		gEnv->fFileNameTSP="../tc/ja9847.tsp";
	}
 	//scanf("%s", gEnv->fFileNameTSP);
	
	maxNumOfTrial=5;					// repeated times
	gEnv->Npop=100;						// number of items
	gEnv->Nch=30;						// number of offsprings

	cout<<"Initializing ..."<<endl;
	gEnv->define();
	cout<<"Building solution ..."<<endl;
	for ( int n = 0; n < maxNumOfTrial; ++n ){ 
		gEnv->doIt(); 
		gEnv->printOn(n);
		gEnv->writeBest();
	}
	//system("pause");
	return 0;
}
