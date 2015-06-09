/*
 * GridLocation.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#include "GridPosition.h"

void GridPosition::construct(unsigned int  x, unsigned int y){
	this->_x = x;
	this->_y = y;
}

GridPosition::GridPosition() {
	this->construct(0,0);
}

GridPosition::GridPosition(unsigned int x, unsigned int y){
	this->construct(x,y);
}

