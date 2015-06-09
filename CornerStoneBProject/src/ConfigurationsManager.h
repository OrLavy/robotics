/*
 * Configuration.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Commons/ComplexLocation.h"

class ComplexLocation;
class Location;

using namespace std;

class ConfigurationsManager {
private :
	static string _mapPath;
	static ComplexLocation _robotInitialLocation;
	static Location _destination;
	static unsigned _robotSize; // in Cm
	static unsigned _pixel2Centimeter;
	static unsigned _gridCell2Centimeter;
public:
	//******************
	//	Initialization
	//******************
	void initializeFromFile(string filePath);

	//******************
	//	Accessors
	//******************
	static const string& getMapPath(){
		return _mapPath;
	}

	static void setMapPath(string& mapPath) {
		_mapPath = mapPath;
	}

	static const ComplexLocation& getRobotInitialLocation(){
		return _robotInitialLocation;
	}

	static void setRobotInitialLocation(ComplexLocation& robotInitialLocation) {
		_robotInitialLocation = robotInitialLocation;
	}

	static const Location& getDestination() {
		return _destination;
	}

	static void setDestination(Location& destination) {
		_destination = destination;
	}

	static unsigned getRobotSize() {
		return _robotSize;
	}

	static void setRobotSize(unsigned robotSize) {
		_robotSize = robotSize;
	}

	static unsigned getPixel2Centimeter(){
		return _pixel2Centimeter;
	}

	static void setPixel2Centimeter(unsigned pixel2Centimeter) {
		_pixel2Centimeter = pixel2Centimeter;
	}

	static unsigned getGridCell2Centimeter() {
		return _gridCell2Centimeter;
	}

	static void setGridCell2Centimeter( unsigned gridCell2Centimeter) {
		_gridCell2Centimeter = gridCell2Centimeter;
	}

	//********************
	//	Print parameters
	//********************
	static void printParameters(){
		cout << " --- Program parameters are : ---" << std::endl;
		cout << " *** Map path : " << getMapPath() << endl;
		cout << " *** Robot initial location : " << getRobotInitialLocation().getX() << ", "
				<< getRobotInitialLocation().getY( )<< ", "
				<< getRobotInitialLocation().getYaw( )<< endl;
		cout << " *** Destination : " << getDestination().getX( ) << ", " << getDestination().getY() << endl;
		cout << " *** Robot size : " << getRobotSize() << endl;
		cout << " *** Pix2Cm ratio : " << getPixel2Centimeter() << endl;
		cout << " *** Localization res : " << getGridCell2Centimeter() << endl;
		cout << "----------------------------------" << endl;
	}
};


#endif /* CONFIGURATION_H_ */
