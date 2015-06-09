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
}
