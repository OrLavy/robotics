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

#include "Robot.h"
#include "Behaviours/Manager.h"
#include "Behaviours/Plans/PlanDrive.h"

using namespace std;

int main() {
	/*
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
	ConfigurationsManager::setDestination(usedDestination); */

	string confFilePath ="/home/colman/git/robotics/CornerStoneBProject/parameters.txt" ;//"/mnt/hgfs/SharedFolder/simulation/orConf.txt";
	ConfigurationsManager::initializeFromFile(confFilePath);
	ConfigurationsManager::printParameters();

	string hospitalMap = "/usr/robotics/PcBotWorld/hospital_section.png";
	string hospitalMapFixed = "/usr/robotics/PcBotWorld/hospital_section.png";//"/home/colman/Programming/Robotics/CornerStoneBProject/FixedHospital.png";
	string labMap = "/home/colman/git/robotics/CornerStoneBProject/roboticLabMap.png";//"/mnt/hgfs/SharedFolder/simulation/roboticLabMap.png";

	//string smallMazeMap = "/mnt/hgfs/SharedFolder/Maps/smallMap.png";
	//string circularMazeMap = "/mnt/hgfs/SharedFolder/Maps/roundMaze.png";
	string usedMap = labMap;
	cout << "Or Lavy part begin" << endl;
	Map mapa;
	mapa.readMapFromPng(usedMap);
	mapa.saveRawMapAsPng("RawGrid.png");
	mapa.saveBlownMapAsPng("BlownMap.png");
	mapa.saveNavigationMapAsPng("NavMap.png");

	PathFinder pathFinder(mapa.getBlownMap());
	ComplexLocation initialComplexLocation = ConfigurationsManager::getRobotInitialLocation();
	pathFinder.findPath(initialComplexLocation.getLocation(),
						ConfigurationsManager::getDestination());

	pathFinder.saveMapWithRoughPath("roughPath.png");

	WayPointsManager wpManager(pathFinder.getChosenPath(),mapa.getBlownMap());
	cout << "waypoint count: " << wpManager.getNumberOfWayPoints() << endl;
	wpManager.savePointsOnMap("waypoints.png");

	cout << "Or Lavy part  end" << endl;

	cout << "Anton part begin" << endl;

    float cell2cm = ConfigurationsManager::getPixel2Centimeter();
	initialComplexLocation.setX(Utils::locationFromActualPosition(initialComplexLocation.getX(), cell2cm));
	initialComplexLocation.setY(Utils::locationFromActualPosition(initialComplexLocation.getY(), cell2cm));

	float x = initialComplexLocation.getX();
	float y = initialComplexLocation.getY();
	//initialComplexLocation.setX((x - 550) / 85.0f);
	//initialComplexLocation.setY(-(y - 400) / 85.0f);

	initialComplexLocation.setX(1.975f);
	initialComplexLocation.setY(-2.6375f);
	initialComplexLocation.setYaw(20.0f * 3.14159f / 180.0f);

	Robot* robot = new Robot("localhost",6665, initialComplexLocation);
    cout << "initial Robot location " << robot->getCurrentLocation().getX() << ", " << robot->getCurrentLocation().getY() << endl;
	PlanDrive plnOA(robot, &wpManager);
	Manager manager(robot, &plnOA);
	manager.run();
	cout << "Anton part ends" << endl;


	return 0;
}
