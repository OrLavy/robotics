/*
 * Configuration.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#include "ConfigurationsManager.h"
//*****************
//	Initialization for static members (because of C++ syntax)
//*****************
string ConfigurationsManager::_mapPath ="";
ComplexLocation ConfigurationsManager::_robotInitialLocation;
Location ConfigurationsManager::_destination;
unsigned ConfigurationsManager::_gridCell2Centimeter = 0;
unsigned ConfigurationsManager::_pixel2Centimeter = 0;
unsigned ConfigurationsManager::_robotSize = 0;



//*****************
//	Public methods
//*****************
void ConfigurationsManager::initializeFromFile(string filePath) {

	ifstream inputFile(filePath.c_str());
	string line;
	string fieldName;
	// Map path
	getline(inputFile,line);
	istringstream ssmapLocation(line);
	string mapPath;
	ssmapLocation >> fieldName >> mapPath;
	parseMapLocation(line);

	// Initial Location
	getline(inputFile,line);
	istringstream ssInitialLocation(line);
	string initialX,initialY,initialYaw;
	ssInitialLocation >> fieldName >> initialX >> initialY >> initialYaw;
	parseInitialLocation(initialX,initialY,initialYaw);

	// Target's Location
	getline(inputFile,line);
	istringstream ssTargetLocation(line);
	string targetX,targetY;
	ssTargetLocation >> fieldName >> targetX >> targetY ;
	parseTargetLocation(targetX,targetY);


	// Robot's size
	getline(inputFile,line);
	istringstream ssRobotSize(line);
	string robotX,robotY;
	ssRobotSize >> fieldName >> robotX >> robotY ;
	parseRobotSize(robotX,robotY);


	// cell resolution
	getline(inputFile,line);
	istringstream ssCellRes(line);
	string strCellRes;
	ssCellRes >> fieldName >> strCellRes;
	parseMapResolution(strCellRes);

	// navigation resolution
	getline(inputFile,line);
	istringstream ssNavRes(line);
	string strNavRes;
	ssNavRes >> fieldName >> strNavRes;
	parseNavigationResolution(strNavRes);
}
