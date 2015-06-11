/*
 * WayPointsManager.h
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <vector>

#include "WayPointsManager/WayPoint.h"
#include "Commons/Location.h"
#include "Commons/GridPosition.h"
#include "Commons/MapObject.h"
#include "Commons/Utils.h"

using namespace std;

class WayPointsManager {
private :
	MapObject _originalMap;
	vector<GridPosition> _positions;
	vector<WayPoint> _wayPoints;

	unsigned _currentWayPoint;
public:

	//*****************
	//	Ctor
	//*****************
	WayPointsManager(vector<GridPosition> path, MapObject map);

	//*****************
	//	Accessors
	//*****************

	/**
	 * as long as we are not in the last way point , increase _currentWayPoint and return
	 * the new way point
	 */
	WayPoint advanceWayPoint(){
		this->_currentWayPoint++;

		return getCurrnetWayPoint();
	}

	/**
	 * Returns the current way point
	 */
	WayPoint getCurrnetWayPoint(){
		return _wayPoints[_currentWayPoint];
	}

	/**
	 * Gets a specific way point
	 */
	WayPoint getWayPointNumber(unsigned number){
		return _wayPoints[number];
	}

	/**
	 * Returns the amount of way points available in the given path
	 */
	unsigned getNumberOfWayPoints(){
		return _wayPoints.size();
	}

	vector<GridPosition> getChosenPositions(){
		return _positions;
	}


	//*****************
	//	Public methods
	//*****************
	void savePointsOnMap(string name){
		Utils::writeMapToPng(name,_originalMap);
	}

private:
	//*****************
	//	Private initialization methods
	//*****************

	/**
	 * Gets a path of GridPoisitions and chose a selected amount of
	 * Way points (takes one every 2 times robot size).
	 */
	void initializePositionsArray(vector<GridPosition> path){
		int robotsInPixel = ConfigurationsManager::getRobotSize() / _originalMap.getCell2Cm();

		int jumps = robotsInPixel * 2;

		// Naive algorithm , steps that are twice the robots size
		for(unsigned i=0; i< path.size(); i += jumps){
			this->_positions.push_back(path[i]);
		}

		if ((path.size() % jumps) != 0){
			this->_positions.push_back(path[path.size() -1]);
		}

		// Remove the first node
		_positions.erase(_positions.begin());

		Utils::insertPathToMap(_originalMap,_positions);
	}

	/**
	 * Transforms the chosen grid positions to way points
	 */
	void initializeWayPointsWrray(){
		for (unsigned i = 0; i < _positions.size() ; i++){
			Location loc = _originalMap.locationFromPosition(_positions[i]);
			this->_wayPoints.push_back(WayPoint(loc,i));
		}
	}
	//*****************
	//	private helper methods
	//*****************
};

#endif /* WAYPOINTSMANAGER_H_ */
