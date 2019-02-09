#pragma once
#include "agent.h"

class frequentist : public agent {

public:

	frequentist();
	void updateProb(interaction) override;

private:
	int rightCount;
	int interactionCount;
};