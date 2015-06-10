/*
 * PathFinder.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "PathFinder.h"

PathFinder::PathFinder(MapObject map) {
	this->_map = map;

	this->_costsMap.defineDimensions(map.getWidth(),map.getHeight());
	this->_parentsMap.defineDimensions(map.getWidth(),map.getHeight());
}

//************
//	Navigation methods
//************
void PathFinder::findPath(Location source, Location destination){
	// First , lets find the matching cells in the map
	//GridPosition sourceCell = _map.PositionFromLocation(source);
	//GridPosition destinationCell = _map.PositionFromLocation(detination);

	GridPosition sourceCell = GridPosition(source.getX(),source.getY());
	GridPosition destinationCell = GridPosition(destination.getX(),destination.getY());

	// a graph object
	MapGraphObject graphObject(_map);

	// DEBUG
	this->_mapWithRoughPath = MapObject(_map);
	_mapWithRoughPath.setCellAtPosition(sourceCell,Source);
	_mapWithRoughPath.setCellAtPosition(destinationCell,Target);
	Utils::writeMapToPng("locations.png", _mapWithRoughPath);
	// DEBUG END

	// Apply A*
	_searcher.aStarSearch(graphObject,sourceCell,destinationCell,_parentsMap, _costsMap);

	// Get path from parents map
	_roughlocationsVector= pathFromParentMap(sourceCell,destinationCell);

	// Copy the original map and assign the path
	this->_mapWithRoughPath = MapObject(_map);
	Utils::insertPathToMap(_mapWithRoughPath,_roughlocationsVector);
	_mapWithRoughPath.setCellAtPosition(sourceCell,Source);
	_mapWithRoughPath.setCellAtPosition(destinationCell,Target);
}
