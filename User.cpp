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

}

void CUser::loadspringconstants(void)
{
	for (int i = 0; i < springs.size(); i++)
	{
		springs[i].calcLs(rx, ry);
		springs[i].calctension();
	}
}