/*
 * WayPoint.h
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include "../Commons/Location.h"

class WayPoint {
private :
	Location _location;
	unsigned _number;
public:
	//*****************
	//	Ctor
	//*****************
	WayPoint(Location location, unsigned number){
		this->_location = location;
		this->_number = number;
	}

	//*****************
	//	Accessors
	//*****************

	const Location& getPixelLocation() const {
		return _location;
	}

	const Location& getRealLocation()  {
		float x = _location.getX();
		float y = _location.getY();
		Location real_loc((x - 550) / 82.0f, -(y - 400) / 82.0f);

		return real_loc;
	}

	unsigned getNumber() const {
		return _number;
	}
};

#endif /* WAYPOINT_H_ */
