/*
 * PathFinder.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include <limits>
#include "Commons/MapObject.h"
#include "Commons/Utils.h"
#include "Commons/GridPosition.h"
#include "AStar/AStarSearcher.h"
#include "AStar/MapGraphObject.h"
#include "AStar/MatrixHolder.h"

using namespace std;

#define MAX_U numeric_limits<unsigned int>::max()
#define MAX_I numeric_limits<int>::max()

class PathFinder {
private:
	MapObject _map;
	MapObject _mapWithRoughPath;

	vector<GridPosition> _roughlocationsVector;

	AStarSearcher _searcher;

	MatrixHolder<GridPosition> _parentsMap = MatrixHolder<GridPosition>(GridPosition(MAX_U,MAX_U));
	MatrixHolder<int> _costsMap = MatrixHolder<int>(MAX_I);
public:
	//************
	//	Ctor and initialization
	//************
	PathFinder(MapObject map);

	//************
	//	Accessors
	//************
	vector<GridPosition> getChosenPath(){
		return _roughlocationsVector;
	}


	//************
	//	Navigation methods
	//************
	/**
	 * Orders the class to find the path from source to destination and
	 * keep it.
	 */
	void findPath(Location source, Location destination);

	//************
	//	Public utilities - Save and print
	//************
	/**
	 * Saves the map with the path to a png with the given file name
	 */
	void saveMapWithRoughPath(string fileName){
		Utils::writeMapToPng(fileName, _mapWithRoughPath);
	}

	/**
	 * Prints the map with the path
	 */
	void printMapWithPath(){
		Utils::printMap(_mapWithRoughPath);
	}
private :

	//***********
	//	Path finding helpers
	//***********
	vector<GridPosition> pathFromParentMap(GridPosition from, GridPosition to){
		vector<GridPosition> path;

		// Starts from the end and go to the begining
		GridPosition current = to;

		path.insert(path.begin(),current);
		cout << LOG_DEBUG << " Pushed X=" << current.getX() << ", Y=" << current.getY() << endl;
		while(current != from){
			current = _parentsMap[current];

			path.insert(path.begin(),current);
			cout << LOG_DEBUG << " Pushed X=" << current.getX() << ", Y=" << current.getY() << endl;
		}

		return path;
	}
};

#endif /* PATHFINDER_H_ */
