/*
 * MapGraphObject.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "MapGraphObject.h"

MapGraphObject::MapGraphObject(MapObject& map) {
	this->_map = map;
	this->_costs.defineDimensions(_map.getWidth(),_map.getHeight());

	initializeCosts();
}

vector<GridPosition> MapGraphObject::neighbors(GridPosition center){
	vector<GridPosition> neighbors;

	for (int direction = Up; direction <= Up_Left; direction ++){
		GridPosition neighbor = center.getRelativePosition((Directions)direction);

		if ((_map.isPositionValid(neighbor)) && (_map.getCellAtPosition(neighbor) != Occupied)){
			neighbors.push_back(neighbor);
		}
	}

	return neighbors;
}

unsigned MapGraphObject::cost(GridPosition from, GridPosition to){
	return max(_costs[from],_costs[to]);
}
