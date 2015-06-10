//============================================================================
// Name        : CornerStoneBProject.cpp
// Author      : OrAnton
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Map.h"
#include "PngUtils/PngUtil.h"
#include "PathFinder.h"
#include "WayPointsManager.h"
using namespace std;

int main() {
	// Configurations initializing
	ConfigurationsManager::setRobotSize(30);
	//ConfigurationsManager::setRobotSize(2); // Maze tests
	ConfigurationsManager::setPixel2Centimeter(2);
	ConfigurationsManager::setGridCell2Centimeter(10);
	ComplexLocation initialLocation(362,305,20); // Regular
	ComplexLocation initialLocationSmallMaze(4,5,20); // small Maze test
	ComplexLocation initialLocationCircularMaze(7,578,20); // circular Maze test
	ComplexLocation usedLocation = initialLocation;
	ConfigurationsManager::setRobotInitialLocation(usedLocation);
	Location destination(169,138); // Regular
	Location destinationSmallMaze(134,230); // small maze test
	Location destinationCircularMaze(553,572); // Circular maze test
	Location usedDestination = destination;
	//Location destination(372,311);
	ConfigurationsManager::setDestination(usedDestination);

	ConfigurationsManager::printParameters();

	string hospitalMap = "/usr/robotics/PcBotWorld/hospital_section.png";
	string hospitalMapFixed = "/home/colman/Programming/Robotics/CornerStoneBProject/FixedHospital.png";
	string labMap = "/mnt/hgfs/SharedFolder/simulation/roboticLabMap.png";

	string smallMazeMap = "/mnt/hgfs/SharedFolder/Maps/smallMap.png";
	string circularMazeMap = "/mnt/hgfs/SharedFolder/Maps/roundMaze.png";
	string usedMap = labMap;
	cout << "Or Lavy part begin" << endl;
	Map mapa;
	mapa.readMapFromPng(usedMap);
	mapa.saveRawMapAsPng("RawGrid.png");
	mapa.saveBlownMapAsPng("BlownMap.png");
	mapa.saveNavigationMapAsPng("NavMap.png");

	PathFinder pathFinder(mapa.getBlownMap());
	pathFinder.findPath(usedLocation.getLocation(),usedDestination);

	pathFinder.saveMapWithRoughPath("roughPath.png");

	WayPointsManager wpManager(pathFinder.getChosenPath(),mapa.getBlownMap());
	wpManager.savePointsOnMap("folder/waypoints.png");

	cout << "Or Lavy part  end" << endl;
	return 0;
}
