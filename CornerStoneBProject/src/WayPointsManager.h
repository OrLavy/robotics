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
public:

	//*****************
	//	Ctor
	//*****************
	WayPointsManager(vector<GridPosition> path, MapObject map);

	//*****************
	//	Accessors
	//*****************
	WayPoint getWayPointNumber(unsigned number){
		return _wayPoints[number];
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
	void initializeWayPointsArray(vector<GridPosition> path){
		int robotsInPixel = ConfigurationsManager::getRobotSize() / _originalMap.getCell2Cm();
		int size = path.size() / robotsInPixel;
		cout << "Size is " << size << endl;
		int jumps = robotsInPixel * 2;//size;//30;
		// Naive algorithm , take every 10'th point
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

	//*****************
	//	private helper methods
	//*****************
};

#endif /* WAYPOINTSMANAGER_H_ */
