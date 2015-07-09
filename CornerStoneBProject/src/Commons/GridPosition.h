/*
 * GridLocation.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef GRIDPOSITION_H_
#define GRIDPOSITION_H_

#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../Globals.h"

using namespace std;

/**
 * Represents a location in a matrix grid (unsigned integer x and y values)
 */
class GridPosition {
private :
	unsigned int _x;
	unsigned int _y;

	/**
	 * Telescopic constructor replacement
	 */
	void construct(unsigned int x,unsigned int y);

public:
	//***********************
	//	Ctor
	//***********************
	GridPosition();
	GridPosition(unsigned int x,unsigned int y);

	//***********************
	//	Relative factory
	//***********************
	GridPosition getRelativePosition(Directions direction){
		GridPosition relative;
		switch(direction ){
		case Up:
			relative = GridPosition(getX(),getY() + 1);
			break;
		case Up_Right:
			relative = GridPosition(getX() + 1,getY() + 1);
			break;
		case Right:
			relative = GridPosition(getX() + 1,getY());
			break;
		case Down_Right:
			relative = GridPosition(getX() + 1,getY() - 1);
			break;
		case Down:
			relative = GridPosition(getX(),getY() - 1);
			break;
		case Down_Left:
			relative = GridPosition(getX() -1 ,getY() - 1);
			break;
		case Up_Left:
			relative = GridPosition(getX() - 1,getY() + 1);
			break;
		}

		return relative;
	}

	//***********************
	//		Accessors
	//***********************

	unsigned int getX() const {
		return _x;
	}

	void setX(unsigned int x) {
		_x = x;
	}

	unsigned int getY() const {
		return _y;
	}

	void setY(unsigned int  y) {
		_y = y;
	}

	void printString(){
		cout << "X=" <<_x << ",Y=" << _y;
	}
};

struct my_hash {
std::size_t operator()( const GridPosition & c ) const
        {
			unsigned hash = 17;
			hash = (31 * hash) +  c.getX();
			hash = (31 * hash) + c.getY() ;

            return hash;
        }
};

inline bool operator==(const GridPosition& lhs,const GridPosition& rhs){
	return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
}
inline bool operator!=(const GridPosition& lhs,const GridPosition& rhs){
	return !(lhs==rhs);
}


#endif /* GRIDPOSITION_H_ */
