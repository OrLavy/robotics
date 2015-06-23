/*
 * ComplexPosition.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include <Commons/ComplexPosition.h>



void ComplexPosition::construct(float yaw){
	this->_yaw = yaw;
}

ComplexPosition::ComplexPosition():GridPosition() {
	this->construct(0);
}
ComplexPosition::ComplexPosition(float yaw):GridPosition(){
	this->construct(yaw);
}
ComplexPosition::ComplexPosition(unsigned x, unsigned y):GridPosition(x,y){
	this->construct(0);
}
ComplexPosition::ComplexPosition(unsigned x, unsigned y, float yaw):GridPosition(x,y){
	this->construct(yaw);
}
