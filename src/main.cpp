/*
 * main.cpp
 *   created on: April 24, 2013
 * last updated: June 13, 2013
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

	cout<<"请输入1~5其中的一个数字以选择数据集"<<endl;
	cout<<"1: eil101.tsp"<<endl;
	cout<<"2: att532.tsp"<<endl;
	cout<<"3: rat575.tsp"<<endl;
	cout<<"4: fnl4461.tsp"<<endl;
	cout<<"5: ja9847.tsp"<<endl;

	int id=0;
	while(id<1 || id>5){
		scanf("%d", &id);
		if(id<1 || id>5)
			cout<<"请重新输入1~5其中的一个数字以选择数据集"<<endl;
	}
	if(id==1) gEnv->fFileNameTSP="eil101.tsp";
	else if(id==2) gEnv->fFileNameTSP="att532.tsp";
	else if(id==3) gEnv->fFileNameTSP="rat575.tsp";
	else if(id==4) gEnv->fFileNameTSP="fnl4461.tsp";
	else if(id==5) gEnv->fFileNameTSP="ja9847.tsp";
 	//scanf("%s", gEnv->fFileNameTSP);
	
	maxNumOfTrial=5;					// 重复次数
	gEnv->Npop=100;						// 种群数量
	gEnv->Nch=30;						// 每个父本(母本)产生子代数量

	cout<<"正在初始化 ..."<<endl;
	gEnv->define();
	cout<<"正在生成可行解 ..."<<endl;
	for( int n = 0; n < maxNumOfTrial; ++n ){ 
		gEnv->doIt(); 
		gEnv->printOn(n);
		gEnv->writeBest();
	}
	//system("pause");
	return 0;
}
