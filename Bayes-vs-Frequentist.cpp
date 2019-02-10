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

void checkCollision(agent& a1, agent& a2, interaction& i) {
	bool tmp1, tmp2;
	tmp1 = a1.getDirection();
	tmp2 = a2.getDirection();
	i.direction = tmp1;
	i.crash = !(tmp1 == tmp2);
}//should make this method internal to interaction struct

void printProbs(vector<frequentist>& f, vector<psuedoBayes>& b) {
	for (int i = 0; i < f.size(); i++) {
		cout << f[i].getProbRight() << "  " << b[i].getProbRight() << endl;
	}
}

void printStatus(int freqCount, int bayesCount, int randCount, int interactionCount) {
	double f = double(freqCount) / interactionCount;
	double b = double(bayesCount) / interactionCount;
	double r = double(randCount) / interactionCount;
	cout << interactionCount << " f: " << f << " b: " << b << " r: " << r << endl;
}

void partialSim(vector<frequentist>& frqs, vector<psuedoBayes>& bayes, vector<randAgent>& rands, int sliceSize) {
	int fCnt, bCnt, rCnt;
	fCnt = bCnt = rCnt = 0;
	for (int i = 0; i < sliceSize; i++) {
		int first, second;
		interaction itF, itB, itR;
		first = rand() % frqs.size();
		second = rand() % frqs.size();
		checkCollision(frqs[first], frqs[second], itF);
		checkCollision(bayes[first], bayes[second], itB);
		checkCollision(rands[first], rands[second], itR);

		frqs[first].updateProb(itF); frqs[second].updateProb(itF);
		bayes[first].updateProb(itB); bayes[second].updateProb(itF);

		fCnt += itF.crash;
		bCnt += itB.crash;
		rCnt += itR.crash;
	}
	printStatus(fCnt, bCnt, rCnt, sliceSize);
}

void runSim(int numAgents, double inc, double decay, int limit) //want to add default arguments for bayes inc method, and decay val
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
					  //should I be reinitizializing
	cout << "prints percentage of crashes as decimal." << endl;
	int printInterval = limit / 5;

	for (int i = 0; i <= limit; i+=printInterval) {
		partialSim(frqs, bayes, rands, printInterval);
	}
}

int main() {
	double incs[] = { .55,.54,.53,.52,.51,.5,.5,.49,.48,.47,.46,.45 };
	double decays[] = { .95,.9,.85,.8,.75 };
	int simLimit = 500000;
	char pause;
	for (double i : incs) {
		for (double d : decays) {
			cout << "inc val= " << i << " decay val= " << d << endl;
			runSim(20 ,i, d, simLimit);
			cout << "******" << endl;
		}
		cout << "=====\n=====\n" << endl;
		//cin >> pause;
		system("PAUSE");
	}

	//runSim(20, 0.5, 0.95);

	return 0;
}