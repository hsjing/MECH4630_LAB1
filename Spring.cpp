#include "stdafx.h"
#include "Spring.h"


CSpring::CSpring()
{
}


CSpring::~CSpring()
{
}

void CSpring::calcLs(double rx, double ry)
{
	// check for Ls = 0, if so return arbitrary Ls for current iteration
	if (x != rx && y != ry)
		Ls = sqrt(pow((x - rx), 2) + pow((y - ry), 2));
	else
		Ls = DUMMY_LS;
}

void CSpring::calcangle(double ry)
{
	angle = (asin((y - ry) / (Ls + RING_RADIUS))) * (180 / PI);
}

void CSpring::calctension()
{
	tension = Fcs + (k * ((Ls * INCH_TO_M) - L0));
}

void CSpring::calclambda()
{
	lambda = Fcs - (k * L0);
}