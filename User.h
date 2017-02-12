#pragma once

#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Spring.h"

using namespace std;

#define inputfile "input.txt"
#define outputfile "output.txt"


/**
*
* @brief User object: simulation environment and operations
*
* TODO: FILL IN
*
* @author Jing Huang, Julie Lee, Adam Wells, Peiman Dadkah
*
*/
class CUser
{
public:
	CUser();
	~CUser();

	//////////////////////////////////////////////////
	//file i/o operations							//
	//////////////////////////////////////////////////
	
	/**	@fn loadfile
	* @brief reads (parsed) spring parameters from text file
	* @param void
	* @return bool
	*/
	bool loadfile(void);

	/**	@fn outfile
	* @brief outputs (parsed) simulation results into text file
	* @param void
	* @return bool
	*/
	bool outfile(void);

	//////////////////////////////////////////////////
	//calculation operations						//
	//////////////////////////////////////////////////

	/**	@fn loadspringconstants
	* @brief calculates relevant spring constants for entire simulation
	* @param void
	* @return void
	*/
	void updatespring(void);	

private:
	vector<CSpring> springs;	///< vector of simulated strings
	CSpring tempspring;			///< tempspring for vector pushback

	float rx, ry;				///< ring x and y coordinate
	float sumfx, sumfy;			///< sum of simualted forces in x and y
};

