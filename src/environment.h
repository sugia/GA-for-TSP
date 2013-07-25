/*
 * environment.h
 *   created on: April 24, 2013
 * last updated: June 13, 2013
 *       author: liushujia
 */

#ifndef __ENVIRONMENT__
#define __ENVIRONMENT__

#ifndef __INDI__
#include "indi.h"
#endif

#ifndef __RAND__
#include "randomize.h"
#endif

#ifndef __EVALUATOR__
#include "evaluator.h"
#endif

#ifndef __Cross__
#include "cross.h"
#endif

#ifndef __KOPT__
#include "kopt.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

class TEnvironment{
public:
	TEnvironment(); 
	~TEnvironment();

	void define();						// 初始化
	void doIt();						// GA主程序
	void init();						// GA初始化
	bool terminationCondition();		// 退出条件          
	void setAverageBest();				// 计算种群平均TSP长度与种群最优TSP长度        

	void initPop();						// 初始化种群
	void selectForMating();				// 选择父本与母本                
	void generateKids( int s );			// 产生并选择子代            
	void getEdgeFreq();					// 计算种群中每条边的频率                    

	void printOn( int n );				// 输出结果
	void writeBest();					// 输出最优TSP路径

	TEvaluator* fEvaluator;				// 边距离
	TCross* tCross;						// 边集合交叉
	TKopt* tKopt;						// 局部搜索(2-opt neighborhood)
	char *fFileNameTSP;					// TSP文件名

	int Npop;							// 种群数量                   
	int Nch;							// 每个父本(母本)产生的子代数量                      
	TIndi* tCurPop;						// 当前种群成员
	TIndi tBest;						// 当前种群最优解
	int fCurNumOfGen;					// 当前种群代数
	long int fAccumurateNumCh;			// 子代累计数目             

	int fBestNumOfGen;					// 当前最优解所在的代数                     
	long int fBestAccumeratedNumCh;		// 当前最优解的子代累计数目        
	int **fEdgeFreq;					// 种群的边频率
	double fAverageValue;				// 种群TSP路径的平均长度                  
	int fBestValue;						// 种群最优解的路径长度                        
	int fBestIndex;						// 最优种群的下标

	int* fIndexForMating;				// 交叉列表(r[])
	int fStagBest;						// 子代最优解没有提升的累计代数                         
	int fFlagC[ 10 ];					// EAX方式与选择策略                      
	int fStage;							// 当前阶段
	int fMaxStagBest;					// fStagBest==fMaxStagBest时执行下一阶段                      
	int fCurNumOfGen1;					// Stage I结束时的种群代数                     

	clock_t fTimeStart, fTimeInit, fTimeEnd;	// 保存计算时间
};

#endif
