#include "stdafx.h"
#include "frequentistAgent.h"

frequentist::frequentist() {
	probRight = 0.5;
	rightCount = 0;
	interactionCount = 0;
	lastDirection = true; //TODO remove this - here for debug
}

void frequentist::updateProb(interaction i){
	interactionCount++;
	rightCount += (lastDirection ^ i.crash);
	probRight = double(rightCount) / interactionCount;
}//overly simplicit
