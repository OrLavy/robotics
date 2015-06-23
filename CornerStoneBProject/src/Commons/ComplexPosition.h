/*
 * ComplexPosition.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#ifndef COMPLEXPOSITION_H_
#define COMPLEXPOSITION_H_

#include "GridPosition.h"

class ComplexPosition: public GridPosition{

private :
	float _yaw;

	/**
	 * Telescopic constructor replacement
	 */
	void construct(float yaw);

public:
	ComplexPosition();
	ComplexPosition(float yaw);
	ComplexPosition(unsigned x,unsigned y);
	ComplexPosition(unsigned x,unsigned y, float yaw);

	//***********************
	//		Parent class
	//***********************
	GridPosition getPosition(){
		GridPosition pos(getX(),getY());

		return pos;
	}

	void setPosition(GridPosition pos){
		setX(pos.getX());
		setY(pos.getY());
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

#endif /* COMPLEXPOSITION_H_ */
