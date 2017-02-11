#pragma once

#include <string>


/**
*
* @brief Spring object
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
	CSpring();
	~CSpring();

	///////////////////////////////////////////////
	// functions that return properties of spring//
	///////////////////////////////////////////////

	/**
	@fn getk
	@brief return k
	@param void
	@return float
	*/
	float getk() { return k; };
	/**
	@fn getFcs
	@brief return compression force
	@param void
	@return float
	*/
	float getFcs() { return Fcs; };
	/**
	@fn getL0
	@brief return L0 (length initial)
	@param void
	@return float
	*/
	float getL0() { return L0; };
	/**
	@fn getLs
	@brief return Ls (length stretched)
	@param void
	@return float
	*/
	float getLs() { return Ls; };
	/**
	@fn getangle
	@brief return angle in degrees
	@param void
	@return float
	*/
	float getangle() { return angle; };
	/**
	@fn gettension
	@brief return tension in stretched string
	@param void
	@return float
	*/
	float gettension() { return tension; };
	/**
	@fn getx
	@brief return starting x
	@param void
	@return float
	*/
	float getx() { return x; };
	/**
	@fn gety
	@brief return starting y
	@param void
	@return float
	*/
	float gety() { return y; };

	///////////////////////////////////////////////
	// functions that sets properties of spring  //
	///////////////////////////////////////////////

	/**
	@fn setk
	@brief set k
	@param float
	@return void
	*/
	void setk( float nk ) { k = nk; };
	/**
	@fn setFcs
	@brief set compression force
	@param float
	@return void
	*/
	void setFcs(float nFcs) { Fcs = nFcs; };
	/**
	@fn setL0
	@brief set L0 (length initial)
	@param float
	@return void
	*/
	void setL0(float nL0) { L0 = nL0; };
	/**
	@fn setLs
	@brief set Ls (length stretched)
	@param float
	@return void
	*/
	void setLs(float nLs) { Ls = nLs; };
	/**
	@fn setangle
	@brief set angle in degrees
	@param float
	@return void
	*/
	void setangle(float nangle) { angle = nangle; };
	/**
	@fn settension
	@brief set tension in stretched string
	@param float
	@return void
	*/
	void settension(float ntension) { tension = ntension; };
	/**
	@fn setx
	@brief set starting x
	@param float
	@return void
	*/
	void setx(float nx) { x = nx; };
	/**
	@fn sety
	@brief set starting y
	@param float
	@return void
	*/
	void sety(float ny) { y = ny; };

private:
	float k, Fcs, L0, Ls, angle, tension, x, y;	
	std::string colour;	
};

