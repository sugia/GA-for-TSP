/*
 * evaluator.h
 *   created on: April 24, 2013
 * last updated: June 13, 2013
 *       author: liushujia
 */

#ifndef __EVALUATOR__
#define __EVALUATOR__

#ifndef __INDI__
#include "indi.h"
#endif

#include <string.h>
#include <assert.h>

class TEvaluator{
public:
	TEvaluator();
	~TEvaluator();
	void setInstance( char filename[] );		// 设置变量
	void doIt( TIndi& indi );					// 设置indi.fEvaluationValue
	void writeTo( FILE* fp, TIndi& indi );		// 输出TSP路径
	bool checkValid( int* array, int value );	// 检查TSP路径合法性 

	int fNearNumMax;	// 近邻点数目的最大值
	int **fNearCity;	// NearCity[i][k]表示距离i最近的第k个城市
	int **fEdgeDis;		// EdgeDis[i][j]表示城市i到j的距离
	int Ncity;			// 城市数目
	double *x;			// x[i]表示第i个城市的x坐标
	double *y;			// y[i]表示第i个城市的y坐标
	int *Array;			// 最优解的节点标号
};

#endif
