/*
 * Location.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef LOCATION_H_
#define LOCATION_H_

#include <math.h>

/**
 * Represents an actual location in 2d space (x and y are in cm's from a decided zero point)
 */
class Location {
private :
	float _x;
	float _y;

	/**
	 * Telescopic constructor replacement
	 */
	void construct(float x,float y);

public:
	//***********************
	//	Ctor
	//***********************
	Location();
	Location(float x,float y);

	//***********************
	//		Accessors
	//***********************

	float getX() const {
		return _x;
	}

	void setX(float x) {
		_x = x;
	}

	float getY() const {
		return _y;
	}

	void setY(float y) {
		_y = y;
	}

	//*******************
	//     ExtraFuncs
	//*******************
	inline float Magnitude(const Location& v)
	{
	    return (sqrtf(v.getX() * v.getX() + v.getY() * v.getY()));
	}

	inline float Distance(const Location& v)
	{
		return (sqrtf((v.getX() - getX()) * (v.getX() - getX())
				+ (v.getY() - getY()) * (v.getY() - getY())));
	}

	Location operator -(const Location& v) const
	{
	    return (Location(_x - v._x, _y - v._y));
	}

	Location operator /(float t) const
	{
		   return (Location(_x / t, _y / t));
	}

	Location& operator /=(float t)
	{
	    float f = 1.0F / t;
	    _x *= f;
	    _y *= f;
	    return (*this);
	}

	Location& Normalize(void)
	{
	    return (*this /= sqrtf(_x * _x + _y * _y));
	}
};

#endif /* LOCATION_H_ */
