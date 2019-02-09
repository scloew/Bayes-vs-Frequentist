#include "stdafx.h"
#include "psuedoBayes.h"

psuedoBayes::psuedoBayes() {
	incVal = .5;
	probRight = .5;
	decayVal = .95;
} //should have overloaded constructor so can pass these in

psuedoBayes::psuedoBayes(double inc, double decay)
{
	probRight = 0.5;
	decayVal = decay;
	incVal = inc;
}

void psuedoBayes::updateProb(interaction i){
	
	double delta;
	if (lastDirection ^ i.crash) { //increase prob right;
		delta = (1 - probRight)*incVal;
	}
	else {
		delta = -1 * (probRight*incVal);
	}
	probRight += delta;

	incVal *= decayVal;
}
