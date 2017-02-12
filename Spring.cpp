#include "stdafx.h"
#include "Spring.h"


CSpring::CSpring()
{
}


CSpring::~CSpring()
{
}

void CSpring::calcLs(float rx, float ry)
{
	Ls = sqrt(pow((x - rx), 2) + pow((y - ry), 2));
}

void CSpring::calctension()
{
	tension = Fcs + (k * ((Ls * INCH_TO_M) - L0));
}