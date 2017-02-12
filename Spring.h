#pragma once

#include <string>

#define INCH_TO_M 0.0254
#define RING_RADIUS 0.01

using namespace std;

/**
*
* @brief Spring object: properties and operations
*
* This object represents a spring and its physical properties:
* its spring constant, compression force, initial length, 
* stretched length, angle horizontal in degrees, stretched
* tension, and initial cartesian coordinates.
*
* @author Jing Huang, Julie Lee, Adam Wells, Peiman Dadkah
*
*/
class CSpring
{
public:

	//////////////////////////////////////////////////
	//constructors and destructors					//
	//////////////////////////////////////////////////

	CSpring();
	~CSpring();

	//////////////////////////////////////////////////
	//functions that return properties of spring	//
	//////////////////////////////////////////////////

	/** @fn getk
	* @brief return k
	* @param void
	* @return float
	*/
	float getk() { return k; };
	/** @fn getFcs
	* @brief return compression force
	* @param void
	* @return float
	*/
	float getFcs() { return Fcs; };
	/**	@fn getL0
	* @brief return L0 (length initial)
	* @param void
	* @return float
	*/
	float getL0() { return L0; };
	/**	@fn getx
	* @brief return starting x
	* @param void
	* @return float
	*/
	float getx() { return x; };
	/**	@fn gety
	* @brief return starting y
	* @param void
	* @return float
	*/
	float gety() { return y; };
	/**	@fn getc
	* @brief return colour
	* @param void
	* @return string
	*/
	string getc() { return colour; };

	/**	@fn getLs
	* @brief return Ls (length stretched)
	* @param void
	* @return float
	*/
	float getLs() { return Ls; };
	/**	@fn getangle
	* @brief return angle in degrees
	* @param void
	* @return float
	*/
	float getangle() { return angle; };
	/**	@fn gettension
	* @brief return tension in stretched string
	* @param void
	* @return float
	*/
	float gettension() { return tension; };

	//////////////////////////////////////////////////
	//functions that sets properties of spring		//
	//////////////////////////////////////////////////

	/**	@fn setk
	* @brief set k
	* @param float
	* @return void
	*/
	void setk(float nk) { k = nk; };
	/**	@fn setFcs
	* @brief set compression force
	* @param float
	* @return void
	*/
	void setFcs(float nFcs) { Fcs = nFcs; };
	/**	@fn setL0
	* @brief set L0 (length initial)
	* @param float
	* @return void
	*/
	void setL0(float nL0) { L0 = nL0; };
	/**	@fn setx
	* @brief set starting x
	* @param float
	* @return void
	*/
	void setx(float nx) { x = nx; };
	/**	@fn sety
	* @brief set starting y
	* @param float
	* @return void
	*/
	void sety(float ny) { y = ny; };
	/**	@fn setc
	* @brief set colour
	* @param string
	* @return void
	*/
	void setc(string nc) { colour = nc; };

	/**	@fn calcLs
	* @brief calculates Ls (length stretched)
	* @param float rx (ring x), float ry (ring y)
	* @return void
	*/
	void calcLs(float rx, float ry);
	/**	@fn calcangle
	* @brief set angle in degrees
	* @param float
	* @return void
	*/
	void calcangle(float ry);
	/**	@fn calctension
	* @brief calculates tension in stretched string
	* @param void
	* @return void
	*/
	void calctension();

private:
	//!@{ 
	//! springProperties consist of: k = spring constant
	//! Fcs = compression force, L0 = initial length
	//! Ls = stretched length, angle = angle in degrees from horizontal
	//! tension = tension of spring, x, y = cartesian coordinates of spring
	//! and colour = string colour (or any string form of identification)
	float k, Fcs, L0, Ls, angle, tension, x, y;	
	std::string colour;
	//!@}
};

