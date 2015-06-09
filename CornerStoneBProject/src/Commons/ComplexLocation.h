/*
 * ComplexLocation.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef COMPLEXLOCATION_H_
#define COMPLEXLOCATION_H_

#include "Location.h"

/**
 * Represents an actual location in a 2D word with a yaw.
 */
class ComplexLocation: public Location {
private :
	float _yaw;

	/**
	 * Telescopic constructor replacement
	 */
	void construct(float yaw);

public:
	//***********************
	//		Ctor
	//***********************
	ComplexLocation();
	ComplexLocation(float yaw);
	ComplexLocation(float x, float y);
	ComplexLocation(float x, float y, float yaw);

	//***********************
	//		Parent class
	//***********************
	Location getLocation(){
		Location loc(getX(),getY());

		return loc;
	}

	//***********************
	//		Accessors
	//***********************

	float getYaw() const {
		return _yaw;
	}

	void setYaw(float yaw) {
		_yaw = yaw;
	}
};

#endif /* COMPLEXLOCATION_H_ */
