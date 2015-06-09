/*
 * Location.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef LOCATION_H_
#define LOCATION_H_

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
};

#endif /* LOCATION_H_ */
