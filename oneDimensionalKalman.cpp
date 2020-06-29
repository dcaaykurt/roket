#include "oneDimensionalKalman.h"

// kalman iyimis

const float R = 0.1, Q = 0.1;
float KK = 0, xKOld = 0, xKNew = 0, pKOld = 1, pKNew = 0;

float oneDimensionalKalman(int val){
	// Time update
	xKNew = xKOld;
	pKNew = pKOld + Q;

	//Measurment update
	KK = pKNew / (pKNew + R);
	xKNew = xKNew + KK * (val - xKOld);
	pKNew = (1 - KK) * pKOld;
	xKOld = xKNew;
	pKOld = pKNew;
	
	return xKNew;
}