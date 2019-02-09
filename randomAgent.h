#pragma once
#include "agent.h"

class randAgent : public agent {

public:
	randAgent();
	void updateProb(interaction) override;

};