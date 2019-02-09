#pragma once
#include "agent.h"

class psuedoBayes : public agent {

public:

	psuedoBayes();
	psuedoBayes(double, double);
	void updateProb(interaction) override;

private:

	double incVal;
	double decayVal;
};