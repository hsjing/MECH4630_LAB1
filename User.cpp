#include "stdafx.h"
#include "User.h"


CUser::CUser()
{
}


CUser::~CUser()
{
}

bool CUser::loadfile()
{
	ifstream inputFile(inputfile);
	string nline;
	string id;
	float x, y, fc, l0, k;

	int count = 0;

	if (inputFile.is_open())
	{
		while (getline(inputFile, nline))
		{
			if (istringstream(nline) >> id >> x >> y >> fc >> l0 >> k && id != "#")
			{
				// create tempspring using values from new line
				tempspring.setc(id);
				tempspring.setx(x);
				tempspring.sety(y);
				tempspring.setFcs(fc);
				tempspring.setL0(l0);
				tempspring.setk(k);

				// push tempstring onto vector stack
				springs.push_back(tempspring);
			}
		}
		return true;
	}
	return false;
}

bool CUser::outfile()
{
	return true;
}

void CUser::updatespring(void)
{
	// load spring constants (Ls must be loaded before angle and tension)
	for (int i = 0; i < springs.size(); i++)
	{
		springs[i].calcLs(rx, ry);
		springs[i].calcangle(ry);
		springs[i].calctension();
		springs[i].calclambda();
	}
}

double CUser::calcfx(void)
{
	double sumfx = 0;
	for (int i = 0; i < springs.size(); i++)
	{
		sumfx += (springs[i].gettension() * (springs[i].getx() - rx) / springs[i].getLs());
	}
	return sumfx;
}

double CUser::calcfy(void)
{
	double sumfy = 0;
	for (int i = 0; i < springs.size(); i++)
	{
		sumfy += (springs[i].gettension() * (springs[i].gety() - ry) / springs[i].getLs());
	}
	return sumfy;
}

double CUser::calcdXdx(void)
{
	double dXdx = 0;
	for (int i = 0; i < springs.size(); i++)
	{
		dXdx += ((springs[i].getlambda() * 
			pow(((springs[i].getx() - rx) / springs[i].getLs()), 2)) - springs[i].gettension()) / 
			springs[i].getLs();
	}
	return dXdx;
}

double CUser::calcdYdy(void)
{
	double dYdy = 0;
	for (int i = 0; i < springs.size(); i++)
	{
		dYdy += ((springs[i].getlambda() * 
			pow(((springs[i].gety() - ry) / springs[i].getLs()), 2)) - springs[i].gettension()) / 
			springs[i].getLs();
	}
	return dYdy;
}

double CUser::calcdXdy(void)
{
	double dXdy = 0;
	for (int i = 0; i < springs.size(); i++)
	{
		dXdy += (springs[i].getx() - rx) * (springs[i].gety() - ry) * springs[i].getlambda() *
			pow((pow(springs[i].getx() - rx, 2) + pow(springs[i].gety() - ry, 2)) , -1.5);
	}
	return dXdy;
}

double CUser::calcdYdx(void)
{
	double dYdx = 0;
	for (int i = 0; i < springs.size(); i++)
	{
		dYdx += (springs[i].getx() - rx) * (springs[i].gety() - ry) * springs[i].getlambda() *
			pow((pow(springs[i].getx() - rx, 2) + pow(springs[i].gety() - ry, 2)), -1.5);
	}
	return dYdx;
}

bool CUser::iterate(void)
{
	double sumx, sumy;

	do
	{
		updatespring();
		sumx = calcfx();
		sumy = calcfy();

		rx = rx - (((sumx * calcdYdy()) - (sumy * calcdXdy())) /
			((calcdXdx() * calcdYdy()) - (calcdYdx() * calcdXdy())));

		ry = ry - (((sumy * calcdXdx()) - (sumx * calcdYdx())) /
			((calcdXdx() * calcdYdy()) - (calcdYdx() * calcdXdy())));
		
		cout << rx << " " << ry << "\n";
		outfile();

	} while ((fabs(sumx) >= ERR_THRES) && (fabs(sumy) >= ERR_THRES));

	return true;
}
