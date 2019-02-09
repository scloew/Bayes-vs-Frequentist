// Bayes-vs-Frequentist_local.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "frequentistAgent.h"
#include "psuedoBayes.h"
#include "randomAgent.h"
#include<iostream>
#include <vector>
#include<string>
#include<random>
#include<ctime>

//using namespace std;

void checkCollision(agent& a1, agent& a2, interaction& i) { //change return type

	bool tmp1, tmp2;
	tmp1 = a1.getDirection();
	tmp2 = a2.getDirection();
	i.direction = tmp1;
	i.crash = !(tmp1 == tmp2);
}

void printProbs(vector<frequentist>& f, vector<psuedoBayes>& b) {
	for (int i = 0; i < f.size(); i++) {
		cout << f[i].getProbRight() << "  " << b[i].getProbRight() << endl;
	}
}

void runSim(int numAgents, double inc,double decay) //want to add default arguments for bayes inc method, and decay val
{	
	vector<frequentist> frqs(numAgents);
	vector<psuedoBayes> bayes;
	vector<randAgent> rands(numAgents);//should vary size of arrays and number of interactions -> I wonder if on every loop if every agent
								  //should have an interaction?

	for (int i = 0; i < numAgents; i++) {
		bayes.push_back(psuedoBayes(inc, decay));
	} //initialize bayes array

	time_t tm;
	srand(time(&tm)); //double check this is the right way to do this
	cout << "prints percentage of crashes as decimal." << endl;
	int bayesCount = 0;
	int freqCount = 0;
	int randCount = 0;
	int interactionCount = 0;

	int iterationLimit = 10000;
	for (int i = 0; i <= iterationLimit; i++) {
		for (int j = 0; j < frqs.size(); j++) {
			vector<bool> checkedNums(20);
			int first, second;
			do {
				first = (rand() % frqs.size());
			} while (checkedNums[first]);

			do {
				second = (rand() % frqs.size());
			} while (checkedNums[second] && first == second);

			bool tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
			interaction fr, ba,ra;
			checkCollision(frqs[first], frqs[second], fr);
			checkCollision(bayes[first], bayes[second], ba);
			checkCollision(rands[first], rands[second], ra);

			freqCount += fr.crash;
			bayesCount += ba.crash;
			randCount += ra.crash;

			frqs[first].updateProb(fr); frqs[second].updateProb(fr);
			bayes[first].updateProb(ba); bayes[second].updateProb(ba);
			rands[first].updateProb(ra); rands[second].updateProb(ra); //is this sequence correct


			interactionCount++;
		}

		if (i % 1000 == 0) {
			double f = double(freqCount) / interactionCount;
			double b = double(bayesCount) / interactionCount;
			double r = double(randCount) / interactionCount;
			cout << interactionCount << " f: " << f << " b: " << b << " r: " << r << endl;
		}
	} //percent of interaction that is crash

	cout << "=======\n=======\n" << endl; // should add average for each kind of agent

	printProbs(frqs, bayes);

}

int main() {
	double incs[] = { .55,.54,.53,.52,.51,.5,.5,.49,.48,.47,.46,.45 };
	double decays[] = { .95,.9,.85,.8,.75 };

	for (double i : incs) {
		for (double d : decays) {
			cout << "******" << endl << "******" << endl;
			runSim(20 ,i, d);
		}
	}

	//runSim(20, 0.5, 0.95);

	return 0;
}