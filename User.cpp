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

bool CUser::outfile(string CMD, ofstream& currfile)
{
	if (currfile.is_open())
	{
		// handles table header
		if (CMD == CMD_TABLE)
		{
			currfile << left << setw(3) << "Itr"
				<< right
				<< " " << setw(13) << "Sum Fx (N)"
				<< " " << setw(13) << "Sum Fy (N)"
				<< left
				<< "     " << setw(10) << "RingX (In)"
				<< "     " << setw(10) << "RingY (In)"
				<< "\n";
		}

		// handles iteration output
		if (CMD == CMD_I)
		{
			currfile << left << setw(3) << itercount
				<< right
				<< " " << setw(13) << setprecision(4) << sumx
				<< " " << setw(13) << setprecision(4) << sumy
				<< left
				<< "     " << setw(10) << setprecision(9) << rx
				<< "     " << setw(10) << setprecision(9) << ry
				<< "\n";
		}

		// handles final spring property output
		else if (CMD == CMD_SPRS)
		{
			for (int i = 0; i < springs.size(); i++)
			{
				currfile << "\n"
					<< "Spring ID: " << springs[i].getc() << "\n"
					<< "Length: " << springs[i].getLs() << " inches\n"
					<< "Angle from X: " << springs[i].getangle() << " Degrees\n"
					<< "Tension: " << springs[i].gettension() << " N\n";
			}
		}

		// handles table header
	}

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
		// check for Ls = 0
		if ((springs[i].getx() != rx) && springs[i].gety() != ry)
		dXdy += (springs[i].getx() - rx) * (springs[i].gety() - ry) * springs[i].getlambda() *
			pow((pow(springs[i].getx() - rx, 2) + pow(springs[i].gety() - ry, 2)) , -1.5);
		else dXdy = 0;
	}
	return dXdy;
}

double CUser::calcdYdx(void)
{
	double dYdx = 0;
	for (int i = 0; i < springs.size(); i++)
	{
		// check for Ls = 0
		if ((springs[i].getx() != rx) && springs[i].gety() != ry)
		dYdx += (springs[i].getx() - rx) * (springs[i].gety() - ry) * springs[i].getlambda() *
			pow((pow(springs[i].getx() - rx, 2) + pow(springs[i].gety() - ry, 2)), -1.5);
		else dYdx = 0;
	}
	return dYdx;
}

bool CUser::iterate(void)
{
	// prompt user for guess input, check for bounds
	cout << "Please enter ring x and ring y guesses (x y): ";
	cin >> rx >> ry;
	while ((rx > MAX_X) || (rx < MIN_X) || (ry > MAX_Y) || (ry < MIN_Y))
	{
		cout << "x and y must be within bounds (0 - 23): ";
		cin >> rx >> ry;
	}

	// begin output file stream, clear existing content (trunc), allow output operations (out) by appending (app)
	ofstream outputFile(outputfile, (ios::out | ios::app | ios::trunc));
	outputFile.open(outputfile);

	// print table header
	outfile(CMD_TABLE, outputFile);

	// main iteration loop
	do
	{
		// update spring calculations
		updatespring();

		// get current equilibrium
		sumx = calcfx();
		sumy = calcfy();

		// Newton's method iteration
		rx = rx - (((sumx * calcdYdy()) - (sumy * calcdXdy())) /
			((calcdXdx() * calcdYdy()) - (calcdYdx() * calcdXdy())));

		ry = ry - (((sumy * calcdXdx()) - (sumx * calcdYdx())) /
			((calcdXdx() * calcdYdy()) - (calcdYdx() * calcdXdy())));

		itercount++;

		// record current iteration
		outfile(CMD_I, outputFile);

	} while ((fabs(sumx) >= ERR_THRES) && (fabs(sumy) >= ERR_THRES));

	// print final spring properties 
	outfile(CMD_SPRS, outputFile);
	outputFile.close();
	
	cout << "Check " << outputfile << " for results. Press any key to exit.";

	return true;
}
