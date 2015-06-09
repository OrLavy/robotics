/*
 * ComplexLocation.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#include "ComplexLocation.h"

void ComplexLocation::construct(float yaw){
	this->_yaw = yaw;
}

ComplexLocation::ComplexLocation():Location() {
	this->construct(0);
}
ComplexLocation::ComplexLocation(float yaw):Location(){
	this->construct(yaw);
}
ComplexLocation::ComplexLocation(float x, float y):Location(x,y){
	this->construct(0);
}
ComplexLocation::ComplexLocation(float x, float y, float yaw):Location(x,y){
	this->construct(yaw);
}

