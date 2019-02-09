#pragma once

//This class should NEVER be instantiated
//It is a bass clase for the other three
//types of agents that will be used.

#include<random>

using namespace std;

struct interaction {
	bool crash;
	bool direction; //1=right; 0=left; don't think I need this
};

class agent {

public:

	virtual void updateProb(interaction) =0;
	const double getProbRight();
	const bool getDirection();//1= right; 0= left. better name?
								//could return string "RIGHT" "LEFT"

protected:
	double probRight;
	bool lastDirection;
};