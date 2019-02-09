#pragma once

#include "stdafx.h"
#include "agent.h"

const double agent::getProbRight() {
	return probRight;
};

const bool agent::getDirection()
{
	double probLeft = ((double)rand() / (RAND_MAX));
	lastDirection = (probLeft <= probRight);
	return lastDirection;
} //1=right; 0=left

