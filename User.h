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

#define ERR_THRES 0.0000001
#define TRY_ZERO 1e-10
#define CMD_I "ITERATE"
#define CMD_SPRS "SPRING"
#define CMD_TABLE "TABLES"

#define MAX_X 23
#define MIN_X 0
#define MAX_Y 23
#define MIN_Y 0

/**
*
* @brief The User object: Simulation environment
*
* This object represents the simulation environment within which
* the Newtonian properties of the simulation (namely the ring's
* x and y coordinates) are calculated. 
* It contains: 
* 1) the methods with which system forces and their partial 
*	derivatives	are calculated 
* 2) the main iteration method for predicting the next set
*	of ring coordinates and
* 3) a simple file iostream to store and collect data
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
	* @param string
	* @return bool
	*/
	bool outfile(string CMD, ofstream& currfile);

	//////////////////////////////////////////////////
	//calculation operations						//
	//////////////////////////////////////////////////

	/**	@fn loadspringconstants
	* @brief calculates relevant spring constants for entire simulation
	* @param void
	* @return void
	*/
	void updatespring(void);
	/**	@fn sumfx
	* @brief returns current x equilibrium (in abs value)
	* @param void
	* @return float
	*/
	double calcfx(void);
	/**	@fn sumfy
	* @brief returns current y equilibrium (in abs value)
	* @param void
	* @return float
	*/
	double calcfy(void);
	/**	@fn dXdx
	* @brief returns partial fx with respect to x
	* @param void
	* @return float
	*/
	double calcdXdx(void);
	/**	@fn dXdx
	* @brief returns partial fy with respect to y
	* @param void
	* @return float
	*/
	double calcdYdy(void);
	/**	@fn dXdy
	* @brief returns partial fx with respect to y
	* @param void
	* @return float
	*/
	double calcdXdy(void);
	/**	@fn dYdx
	* @brief returns partial fy with respect to x
	* @param void
	* @return float
	*/
	double calcdYdx(void);

	//////////////////////////////////////////////////
	//Newton's method iteration						//
	//////////////////////////////////////////////////

	/**	@fn iterate
	* @brief iterates simulation using newton's method and updates simulation environment
	* @param void
	* @return bool
	*/
	bool iterate(void);

private:
	vector<CSpring> springs;	///< vector of simulated strings
	CSpring tempspring;			///< tempspring for vector pushback

	double rx = -1, ry = -1;	///< ring x and y coordinate
	double itercount = 0;		///< number of iterations
	double sumx, sumy;			///< sum of forces in x and y
};

