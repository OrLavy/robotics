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

	const Location& getLocation() const {
		return _location;
	}

	unsigned getNumber() const {
		return _number;
	}
};

#endif /* WAYPOINT_H_ */
