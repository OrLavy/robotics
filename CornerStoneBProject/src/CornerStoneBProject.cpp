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
	string confFilePath ="/home/colman/git/robotics/CornerStoneBProject/parameters.txt" ;//"/mnt/hgfs/SharedFolder/simulation/orConf.txt";
	ConfigurationsManager::initializeFromFile(confFilePath);
	ConfigurationsManager::printParameters();

	string labMap = "/home/colman/git/robotics/CornerStoneBProject/roboticLabMap.png";//"/mnt/hgfs/SharedFolder/simulation/roboticLabMap.png";

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

    //float cell2cm = ConfigurationsManager::getPixel2Centimeter();
    //float map_half_width_px = mapa.getBlownMap().getWidth() / 2;
    //float map_half_height_px = mapa.getBlownMap().getWidth() / 2;

    initialComplexLocation.setLocation(
    		Utils::MapMeterLocationFromPixelLocation(
    				initialComplexLocation.getLocation(),
    				ConfigurationsManager::getPixel2Centimeter(),
    				(float)mapa.getBlownMap().getWidth(),
    				(float)mapa.getBlownMap().getHeight()));

	//float x = initialComplexLocation.getX();
	//float y = initialComplexLocation.getY();
	//initialComplexLocation.setX((x - 550) / 85.0f);
	//initialComplexLocation.setY(-(y - 400) / 85.0f);
    //9.05 - half_map_x
    //7.625 - half_map_y
	//initialComplexLocation.setX(1.975f);
	//initialComplexLocation.setY(-2.6375f);
	initialComplexLocation.setYaw(20.0f * M_PI / 180.0f);
	Robot* robot = new Robot("localhost",6665, initialComplexLocation, mapa.getNavMap());
    cout << "initial Robot location " << initialComplexLocation.getX() << ", " << initialComplexLocation.getY() << endl;
	PlanDrive plnOA(robot, &wpManager);
	Manager manager(robot, &plnOA);
	manager.run();
	cout << "Anton part ends" << endl;


	return 0;
}
