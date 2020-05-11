/*
 * kopt.cpp
 *   created on: April 24, 2013
 * last updated: May 10, 2020
 *       author: Shujia Liu
 */



#ifndef __KOPT__
#include "kopt.h"
#endif

TKopt::TKopt( int N ){
	fN = N;
	fLink = new int* [ fN ];
	for( int i = 0; i < fN; ++i ) fLink[ i ] = new int [ 2 ];

	fOrdCity = new int [ fN ];
	fOrdSeg = new int [ fN ];
	fSegCity = new int [ fN ];
	fOrient = new int [ fN ];
	fLinkSeg = new int* [ fN ];
	for( int i = 0; i < fN; ++i ) fLinkSeg[ i ] = new int [ 2 ];

	fSizeSeg = new int [ fN ];
	fCitySeg = new int* [ fN ];
	for( int i = 0; i < fN; ++i ) fCitySeg[ i ] = new int [ 2 ];

	fT = new int [ 5 ];
	fActiveV = new int [ fN ];
	fInvNearList = new int* [ fN ];
	for( int i = 0; i < fN; ++i ) fInvNearList[ i ] = new int [ 500 ];

	fNumOfINL = new int [ fN ];
	fArray = new int [ fN+2 ];
	fCheckN = new int [ fN ];
	fB = new int [ fN ];
	fGene = new int [ fN ];
}

TKopt::~TKopt(){
	for( int i = 0; i < fN; ++i ) delete [] fLink[ i ];
	delete [] fLink;

	for( int i = 0; i < fN; ++i ) delete [] fLinkSeg[ i ];
	delete [] fLinkSeg;

	for( int i = 0; i < fN; ++i ) delete [] fCitySeg[ i ];
	delete [] fCitySeg;

	for( int i = 0; i < fN; ++i ) delete [] fInvNearList[ i ];
	delete [] fInvNearList;

	delete [] fOrdCity;
	delete [] fOrdSeg;
	delete [] fSegCity;
	delete [] fOrient;
	delete [] fSizeSeg;
	delete [] fT;
	delete [] fActiveV;
	delete [] fNumOfINL;
	delete [] fArray;
	delete [] fCheckN;
	delete [] fB;
	delete [] fGene;
}

void TKopt::setInvNearList(){
	for( int i = 0; i < fN; ++i ) fNumOfINL[ i ] = 0;
	int c;
	for( int i = 0; i < fN; ++i ){
		for( int k = 0; k < 50; ++k ){
			c = eval->fNearCity[i][k];
			if( fNumOfINL[c] < 500 ) fInvNearList[ c ][ fNumOfINL[c]++ ] = i;
			else{
				printf( "Check fNumOfINL[c] < 500 ) in kopt.cpp \n" );
				fflush( stdout );
			}
		}
	}
}

void TKopt::transIndiToTree( TIndi& indi ){
	int num, size, orient;
	fArray[1] = 0;
	for( int i = 2; i <= fN; ++i ) fArray[i] = indi.fLink[ fArray[i-1] ][ 1 ];

	fArray[0] = fArray[fN];
	fArray[fN+1] = fArray[1];
	num = 1;
	fNumOfSeg = 0;
	while(1){
		orient = 1;
		size = 0;
		fOrient[ fNumOfSeg ] = orient;
		fOrdSeg[ fNumOfSeg ] = fNumOfSeg;

		fLink[ fArray[ num ] ][ 0 ] = -1;
		fLink[ fArray[ num ] ][ 1 ] = fArray[ num+1 ];
		fOrdCity[ fArray[ num ] ] = size;
		fSegCity[ fArray[ num ] ] = fNumOfSeg;
		fCitySeg[ fNumOfSeg ][ this->turn(orient) ] = fArray[ num ];
		++num;
		++size;
		for( int i = 0; i < (int)sqrt( fN*1.0 )-1; ++i ){
			if( num == fN ) break;
			fLink[ fArray[ num ] ][ 0 ] = fArray[ num-1 ];
			fLink[ fArray[ num ] ][ 1 ] = fArray[ num+1 ];
			fOrdCity[ fArray[ num ] ] = size;
			fSegCity[ fArray[ num ] ] = fNumOfSeg;
			++num;
			++size;
		}
		if( num == fN-1 ){
			fLink[ fArray[ num ] ][ 0 ] = fArray[ num-1 ];
			fLink[ fArray[ num ] ][ 1 ] = fArray[ num+1 ];
			fOrdCity[ fArray[ num ] ] = size;
			fSegCity[ fArray[ num ] ] = fNumOfSeg;
			++num;
			++size;
		}
		fLink[ fArray[ num ] ][ 0 ] = fArray[ num-1 ];
		fLink[ fArray[ num ] ][ 1 ] = -1;
		fOrdCity[ fArray[ num ] ] = size;
		fSegCity[ fArray[ num ] ] = fNumOfSeg;
		fCitySeg[ fNumOfSeg ][ orient ] = fArray[ num ];
		++num;
		++size;
		fSizeSeg[ fNumOfSeg ] = size;
		++fNumOfSeg;
		if( num == fN+1 ) break;
	}
	for( int s = 1; s < fNumOfSeg-1; ++s ){
		fLinkSeg[ s ][ 0 ] = s-1;
		fLinkSeg[ s ][ 1 ] = s+1;
	}
	fLinkSeg[ 0 ][ 0 ] = fNumOfSeg-1;
	fLinkSeg[ 0 ][ 1 ] = 1;
	fLinkSeg[ fNumOfSeg-1 ][ 0 ] = fNumOfSeg-2;
	fLinkSeg[ fNumOfSeg-1 ][ 1 ] = 0;
	fTourLength = indi.fEvaluationValue;
	fFixNumOfSeg = fNumOfSeg;
}

void TKopt::transTreeToIndi( TIndi& indi ){
	int t_p, t_n;
	for( int t = 0; t < fN; ++t ){
		t_p = this->getPrev( t );
		t_n = this->getNext( t );
		indi.fLink[ t ][ 0 ] = t_p;
		indi.fLink[ t ][ 1 ] = t_n;
	}
	eval->doIt( indi );
}

void TKopt::doIt( TIndi& tIndi ){
	this->transIndiToTree( tIndi );
	this->sub();
	this->transTreeToIndi( tIndi );
}

void TKopt::sub(){
	int t1_st;
	int dis1, dis2;
	for( int t = 0; t < fN; ++t ) fActiveV[ t ] = 1;
BEGIN:
	t1_st = rand()%fN;
	fT[1] = t1_st;
	//t1's loop
	while(1){
		fT[1] = this->getNext( fT[1] );
		if( fActiveV[ fT[1] ] == 0 ) goto RETURN;
		fFlagRev = 0;
		fT[2] = this->getPrev( fT[1] );
		for( int num1 = 1; num1 < 50; ++num1 ){
			fT[4] = eval->fNearCity[ fT[1] ][ num1 ];
			fT[3] = this->getPrev( fT[4] );
			dis1 = eval->fEdgeDis[fT[1]][fT[2]] - eval->fEdgeDis[fT[1]][fT[4]];
			if( dis1 > 0 ){
				dis2 = dis1 + eval->fEdgeDis[fT[3]][fT[4]] - eval->fEdgeDis[fT[3]][fT[2]];
				if( dis2 > 0 ){
					this->incrementImp( fFlagRev );
					for( int a = 1; a <= 4; ++a )
						for( int k = 0; k < fNumOfINL[fT[a]]; ++k )
							fActiveV[ this->fInvNearList[fT[a]][k] ] = 1;
					goto BEGIN;
				}
			}
			else break;
		}
		fFlagRev = 1;
		fT[2] = this->getNext( fT[1] );
		for( int num1 = 1; num1 < 50; ++num1 ){
			fT[4] = eval->fNearCity[ fT[1] ][ num1 ];
			fT[3] = this->getNext( fT[4] );
			dis1 = eval->fEdgeDis[fT[1]][fT[2]] - eval->fEdgeDis[fT[1]][fT[4]];
			if( dis1 > 0 ){
				dis2 = dis1 + eval->fEdgeDis[fT[3]][fT[4]] - eval->fEdgeDis[fT[3]][fT[2]];
				if( dis2 > 0 ){
					this->incrementImp( fFlagRev );
					for( int a = 1; a <= 4; ++a )
						for( int k = 0; k < fNumOfINL[fT[a]]; ++k )
							fActiveV[ this->fInvNearList[fT[a]][k] ] = 1;
					goto BEGIN;
				}
			}
			else break;
		}
		fActiveV[ fT[1] ] = 0;
RETURN:
		if( fT[1] == t1_st ) break;
	}
}

int TKopt::getNext( int t ){
	int t_n, seg, orient;
	seg = fSegCity[ t ];
	orient = fOrient[ seg ];
	t_n = fLink[ t ][ orient ];
	if( t_n == -1 ){
		seg = fLinkSeg[ seg ][ orient ];
		orient = turn( fOrient[ seg ] );
		t_n = fCitySeg[ seg ][ orient ];
	}
	return t_n;
}

int TKopt::getPrev( int t ){
	int t_p, seg, orient;
	seg = fSegCity[ t ];
	orient = fOrient[ seg ];
	t_p = fLink[ t ][ this->turn( orient ) ];
	if( t_p == -1 ){
		seg = fLinkSeg[ seg ][ turn(orient) ];
		orient = fOrient[ seg ];
		t_p = fCitySeg[ seg ][ orient ];
	}
	return t_p;
}

void TKopt::swap(int &x, int &y){
	int s=x;
	x=y;
	y=s;
}

int TKopt::turn( int &orient ){
	return 1-orient;
}

void TKopt::incrementImp( int flagRev ){
	int t1_s, t1_e, t2_s, t2_e;
	int seg_t1_s, seg_t1_e, seg_t2_s, seg_t2_e;
	int ordSeg_t1_s, ordSeg_t1_e, ordSeg_t2_s, ordSeg_t2_e;
	int orient_t1_s, orient_t1_e, orient_t2_s, orient_t2_e;
	int numOfSeg1, numOfSeg2;
	int curr;
	int ord;

	int flag_t2e_t1s;
	int flag_t2s_t1e;
	int length_t1s_seg;
	int length_t1e_seg;
	int seg;

	if( fFlagRev == 0 ){
		t1_s = fT[1];
		t1_e = fT[3];
		t2_s = fT[4];
		t2_e = fT[2];
	}
	else if( fFlagRev == 1 ){
		t1_s = fT[2];
		t1_e = fT[4];
		t2_s = fT[3];
		t2_e = fT[1];
	}

	seg_t1_s = fSegCity[ t1_s ];
	ordSeg_t1_s = fOrdSeg[ seg_t1_s ];
	orient_t1_s = fOrient[ seg_t1_s ];
	seg_t1_e = fSegCity[ t1_e ];
	ordSeg_t1_e = fOrdSeg[ seg_t1_e ];
	orient_t1_e = fOrient[ seg_t1_e ];
	seg_t2_s = fSegCity[ t2_s ];
	ordSeg_t2_s = fOrdSeg[ seg_t2_s ];
	orient_t2_s = fOrient[ seg_t2_s ];
	seg_t2_e = fSegCity[ t2_e ];
	ordSeg_t2_e = fOrdSeg[ seg_t2_e ];
	orient_t2_e = fOrient[ seg_t2_e ];

	//////////////////// Type1 ////////////////////////
	if( ( seg_t1_s == seg_t1_e ) && ( seg_t1_s == seg_t2_s ) && ( seg_t1_s == seg_t2_e ) ){
		if( (fOrient[seg_t1_s] == 1 && (fOrdCity[ t1_s ] > fOrdCity[ t1_e ])) ||
			(fOrient[seg_t1_s] == 0 && (fOrdCity[ t1_s ] < fOrdCity[ t1_e ]))){
			this->swap( t1_s, t2_s );
			this->swap( t1_e, t2_e );
			this->swap( seg_t1_s, seg_t2_s );
			this->swap( seg_t1_e, seg_t2_e );
			this->swap( ordSeg_t1_s, ordSeg_t2_s );
			this->swap( ordSeg_t1_e, ordSeg_t2_e );
			this->swap( orient_t1_s, orient_t2_s );
			this->swap( orient_t1_e, orient_t2_e );
		}
		curr = t1_s;
		ord = fOrdCity[ t1_e ];
		while(1){
			this->swap( fLink[curr][0], fLink[curr][1] );
			fOrdCity[ curr ] = ord;
			if( curr == t1_e ) break;
			curr = fLink[curr][turn(orient_t1_s)];
			if( orient_t1_s == 0 ) ++ord;
			else --ord;
		}

		fLink[t2_e][orient_t1_s] = t1_e;
		fLink[t2_s][turn(orient_t1_s)] = t1_s;
		fLink[t1_s][orient_t1_s] = t2_s;
		fLink[t1_e][turn(orient_t1_s)] = t2_e;

		return;
	}
	//////////////////// Type1 ///////////////////////


	if( ordSeg_t1_e >= ordSeg_t1_s )	numOfSeg1 = ordSeg_t1_e - ordSeg_t1_s + 1;
	else								numOfSeg1 = ordSeg_t1_e - ordSeg_t1_s + 1 + fNumOfSeg;
	if( ordSeg_t2_e >= ordSeg_t2_s )	numOfSeg2 = ordSeg_t2_e - ordSeg_t2_s + 1;
	else								numOfSeg2 = ordSeg_t2_e - ordSeg_t2_s + 1 + fNumOfSeg;

	if( numOfSeg1 > numOfSeg2 ){
		this->swap( numOfSeg1, numOfSeg2 );
		this->swap( t1_s, t2_s );
		this->swap( t1_e, t2_e );
		this->swap( seg_t1_s, seg_t2_s );
		this->swap( seg_t1_e, seg_t2_e );
		this->swap( ordSeg_t1_s, ordSeg_t2_s );
		this->swap( ordSeg_t1_e, ordSeg_t2_e );
		this->swap( orient_t1_s, orient_t2_s );
		this->swap( orient_t1_e, orient_t2_e );
	}
	if( fLink[ t2_e ][ orient_t2_e ] == -1 ) flag_t2e_t1s = 1;
	else flag_t2e_t1s = 0;

	if( fLink[ t2_s ][ this->turn(orient_t2_s) ] == -1 ) flag_t2s_t1e = 1;
	else flag_t2s_t1e = 0;

	length_t1s_seg = abs( fOrdCity[ t2_e ] - fOrdCity[ fCitySeg[ seg_t2_e ][ orient_t2_e ] ] );
	length_t1e_seg = abs( fOrdCity[ t2_s ] - fOrdCity[ fCitySeg[ seg_t2_s ][ this->turn(orient_t2_s) ] ] );

	///////////////////// Type2 /////////////////
	if( seg_t1_s == seg_t1_e ){
		if( flag_t2e_t1s == 1 && flag_t2s_t1e == 1 ){
			orient_t1_s = turn( fOrient[ seg_t1_s ] );
			fOrient[ seg_t1_s ] = orient_t1_s;
			fCitySeg[ seg_t1_s ][ orient_t1_s ] = t1_s;
			fCitySeg[ seg_t1_s ][ turn(orient_t1_s) ] = t1_e;
			fLinkSeg[ seg_t1_s ][ orient_t1_s ] = seg_t2_s;
			fLinkSeg[ seg_t1_s ][ turn(orient_t1_s) ] = seg_t2_e;
			return;
		}
		if( flag_t2e_t1s == 0 && flag_t2s_t1e == 1 ){
			curr = t1_e;
			ord = fOrdCity[ t1_s ];
			while(1){
				this->swap( fLink[curr][0], fLink[curr][1] );
				fOrdCity[ curr ] = ord;
				if( curr == t1_s ) break;

				curr = fLink[curr][orient_t2_e];
				if( orient_t2_e == 0 ) --ord;
				else ++ord;
			}
			fLink[t2_e][orient_t2_e] = t1_e;
			fLink[t1_s][orient_t2_e] = -1;
			fLink[t1_e][turn(orient_t2_e)] = t2_e;
			fCitySeg[seg_t2_e][orient_t2_e] = t1_s;
			return;
		}
		if( flag_t2e_t1s == 1 && flag_t2s_t1e == 0 ){
			curr = t1_s;
			ord = fOrdCity[ t1_e ];
			while(1){
				this->swap( fLink[curr][0], fLink[curr][1] );
				fOrdCity[ curr ] = ord;
				if( curr == t1_e ) break;

				curr = fLink[curr][turn(orient_t2_s)];
				if( orient_t2_s == 0 ) ++ord;
				else --ord;
			}
			fLink[t2_s][turn(orient_t2_s)] = t1_s;
			fLink[t1_e][turn(orient_t2_s)] = -1;
			fLink[t1_s][orient_t2_s] = t2_s;
			fCitySeg[seg_t2_s][turn(orient_t2_s)] = t1_e;
			return;
		}
	}

	///////////////////// Type3 /////////////////

	if( flag_t2e_t1s == 1 ) fLinkSeg[seg_t1_s][turn(orient_t1_s)] = seg_t2_s;
	else{
		seg_t1_s = fNumOfSeg++;
		orient_t1_s = orient_t2_e;
		fLink[ t1_s ][turn(orient_t1_s)] = -1;
		fLink[ fCitySeg[seg_t2_e][orient_t2_e]][orient_t1_s] = -1;
		fOrient[seg_t1_s] = orient_t1_s;
		fSizeSeg[seg_t1_s] = length_t1s_seg;
		fCitySeg[seg_t1_s][turn(orient_t1_s)] = t1_s;
		fCitySeg[seg_t1_s][orient_t1_s] = fCitySeg[seg_t2_e][orient_t2_e];
		fLinkSeg[seg_t1_s][turn(orient_t1_s)] = seg_t2_s;
		fLinkSeg[seg_t1_s][orient_t1_s] = fLinkSeg[seg_t2_e][orient_t2_e];
		seg = fLinkSeg[seg_t2_e][orient_t2_e];
		fLinkSeg[seg][turn(fOrient[seg])] = seg_t1_s;
	}

	if( flag_t2s_t1e == 1 ) fLinkSeg[seg_t1_e][orient_t1_e] = seg_t2_e;
	else{
		seg_t1_e = fNumOfSeg++;
		orient_t1_e = orient_t2_s;
		fLink[ t1_e ][orient_t1_e] = -1;
		fLink[ fCitySeg[seg_t2_s][turn(orient_t2_s)] ][turn(orient_t1_e)] = -1;
		fOrient[seg_t1_e] = orient_t1_e;
		fSizeSeg[seg_t1_e] = length_t1e_seg;
		fCitySeg[seg_t1_e][orient_t1_e] = t1_e;
		fCitySeg[seg_t1_e][turn(orient_t1_e)] = fCitySeg[seg_t2_s][turn(orient_t2_s)];
		fLinkSeg[seg_t1_e][orient_t1_e] = seg_t2_e;
		fLinkSeg[seg_t1_e][turn(orient_t1_e)] = fLinkSeg[seg_t2_s][turn(orient_t2_s)];
		seg = fLinkSeg[seg_t2_s][turn(orient_t2_s)];
		fLinkSeg[seg][fOrient[seg]] = seg_t1_e;
	}

	fLink[t2_e][orient_t2_e] = -1;
	fSizeSeg[seg_t2_e] -= length_t1s_seg;
	fCitySeg[seg_t2_e][orient_t2_e] = t2_e;
	fLinkSeg[seg_t2_e][orient_t2_e] = seg_t1_e;
	fLink[t2_s][turn(orient_t2_s)] = -1;
	fSizeSeg[seg_t2_s] -= length_t1e_seg;
	fCitySeg[seg_t2_s][turn(orient_t2_s)] = t2_s;
	fLinkSeg[seg_t2_s][turn(orient_t2_s)] = seg_t1_s;

	seg = seg_t1_e;
	while(1){
		fOrient[seg] = turn(fOrient[seg]);
		if( seg == seg_t1_s ) break;
		seg = fLinkSeg[seg][fOrient[seg]];
	}

	if( fSizeSeg[seg_t2_e] < length_t1s_seg ){
		seg = fLinkSeg[seg_t2_e][turn(fOrient[seg_t2_e])];
		fLinkSeg[seg][fOrient[seg]] = seg_t1_s;
		seg = fLinkSeg[seg_t2_e][fOrient[seg_t2_e]];
		fLinkSeg[seg][turn(fOrient[seg])] = seg_t1_s;
		seg = fLinkSeg[seg_t1_s][turn(fOrient[seg_t1_s])];
		fLinkSeg[seg][fOrient[seg]] = seg_t2_e;
		seg = fLinkSeg[seg_t1_s][fOrient[seg_t1_s]];
		fLinkSeg[seg][turn(fOrient[seg])] = seg_t2_e;

		this->swap( fOrient[seg_t2_e], fOrient[seg_t1_s] );
		this->swap( fSizeSeg[seg_t2_e], fSizeSeg[seg_t1_s] );
		this->swap( fCitySeg[seg_t2_e][0], fCitySeg[seg_t1_s][0] );
		this->swap( fCitySeg[seg_t2_e][1], fCitySeg[seg_t1_s][1] );
		this->swap( fLinkSeg[seg_t2_e][0], fLinkSeg[seg_t1_s][0] );
		this->swap( fLinkSeg[seg_t2_e][1], fLinkSeg[seg_t1_s][1] );
		this->swap( seg_t2_e, seg_t1_s );
	}

	if( fSizeSeg[seg_t2_s] < length_t1e_seg ){
		seg = fLinkSeg[seg_t2_s][turn(fOrient[seg_t2_s])];
		fLinkSeg[seg][fOrient[seg]] = seg_t1_e;
		seg = fLinkSeg[seg_t2_s][fOrient[seg_t2_s]];
		fLinkSeg[seg][turn(fOrient[seg])] = seg_t1_e;
		seg = fLinkSeg[seg_t1_e][turn(fOrient[seg_t1_e])];
		fLinkSeg[seg][fOrient[seg]] = seg_t2_s;
		seg = fLinkSeg[seg_t1_e][fOrient[seg_t1_e]];
		fLinkSeg[seg][turn(fOrient[seg])] = seg_t2_s;

		this->swap( fOrient[seg_t2_s], fOrient[seg_t1_e] );
		this->swap( fSizeSeg[seg_t2_s], fSizeSeg[seg_t1_e] );
		this->swap( fCitySeg[seg_t2_s][0], fCitySeg[seg_t1_e][0] );
		this->swap( fCitySeg[seg_t2_s][1], fCitySeg[seg_t1_e][1] );
		this->swap( fLinkSeg[seg_t2_s][0], fLinkSeg[seg_t1_e][0] );
		this->swap( fLinkSeg[seg_t2_s][1], fLinkSeg[seg_t1_e][1] );
		this->swap( seg_t2_s, seg_t1_e );
	}

	while( fNumOfSeg > fFixNumOfSeg ){
	if( fSizeSeg[ fLinkSeg[fNumOfSeg-1][0] ] <
		fSizeSeg[ fLinkSeg[fNumOfSeg-1][1] ] )
		this->combineSeg( fLinkSeg[fNumOfSeg-1][0], fNumOfSeg-1 );
	else
		this->combineSeg( fLinkSeg[fNumOfSeg-1][1], fNumOfSeg-1 );
	}
	int ordSeg = 0;
	seg = 0;
	while(1){
		fOrdSeg[seg] = ordSeg;
		++ordSeg;
		seg = fLinkSeg[seg][ fOrient[seg] ];
		if( seg == 0 ) break;
	}
  return;
}

void TKopt::combineSeg( int segL, int segS ){
	int seg;
	int t_s, t_e, direction; t_s = 0; t_e = 0; direction = 0;
	int ord; ord = 0;
	int increment; increment = 0;
	int curr, next;

	if( fLinkSeg[segL][fOrient[segL]] == segS ){
		fLink[fCitySeg[segL][fOrient[segL]]][fOrient[segL]] = fCitySeg[segS][turn(fOrient[segS])];
		fLink[fCitySeg[segS][turn(fOrient[segS])]][turn(fOrient[segS])] = fCitySeg[segL][fOrient[segL]];
		ord = fOrdCity[fCitySeg[segL][fOrient[segL]]];

		fCitySeg[segL][fOrient[segL]] = fCitySeg[segS][fOrient[segS]];
		fLinkSeg[segL][fOrient[segL]] = fLinkSeg[segS][fOrient[segS]];
		seg = fLinkSeg[segS][fOrient[segS]];
		fLinkSeg[seg][turn(fOrient[seg])] = segL;

		t_s = fCitySeg[segS][turn(fOrient[segS])];
		t_e = fCitySeg[segS][fOrient[segS]];
		direction = fOrient[segS];

		if( fOrient[segL] == 1 ) increment = 1;
		else increment = -1;
	}
	else if( fLinkSeg[segL][turn(fOrient[segL])] == segS ){
		fLink[fCitySeg[segL][turn(fOrient[segL])]][turn(fOrient[segL])] = fCitySeg[segS][fOrient[segS]];
		fLink[fCitySeg[segS][fOrient[segS]]][fOrient[segS]] = fCitySeg[segL][turn(fOrient[segL])];
		ord = fOrdCity[fCitySeg[segL][turn(fOrient[segL])]];

		fCitySeg[segL][turn(fOrient[segL])] = fCitySeg[segS][turn(fOrient[segS])];
		fLinkSeg[segL][turn(fOrient[segL])] = fLinkSeg[segS][turn(fOrient[segS])];
		seg = fLinkSeg[segS][turn(fOrient[segS])];
		fLinkSeg[seg][fOrient[seg]] = segL;

		t_s = fCitySeg[segS][fOrient[segS]];
		t_e = fCitySeg[segS][turn(fOrient[segS])];
		direction = turn(fOrient[segS]);

		if( fOrient[segL] == 1 ) increment = -1;
		else increment = 1;
	}
	curr = t_s;
	ord = ord + increment;
	while(1){
		fSegCity[curr] = segL;
		fOrdCity[curr] = ord;

		next = fLink[curr][direction];
		if( fOrient[segL] != fOrient[segS] ) this->swap( fLink[curr][0], fLink[curr][1] );

		if( curr == t_e ) break;
		curr = next;
		ord += increment;
	}
	fSizeSeg[segL] += fSizeSeg[segS];
	--fNumOfSeg;
}

void TKopt::checkDetail(){
	int seg, seg_p, seg_n;
	int ord, ord_p, ord_n;
	int orient;
	int curr;

	seg = 0;
	for( int s = 0; s < fNumOfSeg; ++s ){
		seg = s;
		orient = fOrient[ seg ];
		seg_p = fLinkSeg[ seg ][ this->turn(orient) ];
		seg_n = fLinkSeg[ seg ][ orient ];

		ord = fOrdSeg[ seg ];
		ord_p = ord - 1 ;
		if( ord_p < 0 ) ord_p = fNumOfSeg - 1;

		ord_n = ord + 1;
		if( ord_n >= fNumOfSeg ) ord_n = 0;

		curr = fCitySeg[ s ][ 0 ];
		int count = 0;

		while(1){
			++count;
			if( curr == fCitySeg[ s ][1] ) break;
			curr = fLink[curr][1];
		}
	}
	int t, t_n, t_p, t_s, t_e;
	for( t = 0; t < fN; ++t ){
		seg = fSegCity[ t ];
		orient = fOrient[ seg ];
		t_s = fCitySeg[ seg ][ 0 ];
		t_e = fCitySeg[ seg ][ 1 ];

		t_p = fLink[ t ][ 0 ];
		t_n = fLink[ t ][ 1 ];
	}
}

void TKopt::checkValid(){
	int t_st, t_c, t_n, count, seg, orient, Invalid = 0;
	for( int i = 0; i < fN; ++i ) fCheckN[ i ] = 0;

	t_st = rand() % fN;
	t_n = t_st;
	count = 0;
	while(1){
		t_c = t_n;
		fCheckN[ t_c ] = 1;
		++count;

		seg = fSegCity[ t_c ];
		orient = fOrient[ seg ];
		t_n = this->getNext( t_c );

		if( t_n == t_st ) break;

		if( count == fN+1 ){
			Invalid = 1;
			break;
		}
	}
	for( int i = 0; i < fN; ++i )
		if( fCheckN[ i ] == 0 ) Invalid = 1;

	if( Invalid == 1 ) printf( "Invalid \n" ); fflush( stdout );

}

void TKopt::makeRandSol( TIndi& indi ){
	for( int j = 0; j < fN; ++j ) fB[j] = j;
	int r;
	for( int i = 0; i < fN; ++i ){
		r = rand() % (fN-i);
		fGene[i] = fB[r];
		fB[r] = fB[fN-i-1];
	}

	for( int j2 = 1 ; j2 < fN-1; ++j2 ){
		indi.fLink[fGene[j2]][0] = fGene[j2-1];
		indi.fLink[fGene[j2]][1] = fGene[j2+1];
	}
	indi.fLink[fGene[0]][0] = fGene[fN-1];
	indi.fLink[fGene[0]][1] = fGene[1];
	indi.fLink[fGene[fN-1]][0] = fGene[fN-2];
	indi.fLink[fGene[fN-1]][1] = fGene[0];

	eval->doIt( indi );
}

