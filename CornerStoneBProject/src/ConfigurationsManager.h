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
	static void initializeFromFile(string filePath);

	//******************
	//	Accessors
	//******************
	static const string& getMapPath(){
		return _mapPath;
	}

	static void setMapPath(string& mapPath) {
		_mapPath = mapPath;
	}

	static const ComplexLocation getRobotInitialLocation(){
		return _robotInitialLocation;
	}

	static void setRobotInitialLocation(ComplexLocation& robotInitialLocation) {
		_robotInitialLocation = robotInitialLocation;
	}

	static const Location getDestination() {
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

private:
	//*****************
	//	Parameters reading
	//*****************
	/**
	 * Parse the map file location
	 */
	static void parseMapLocation(string mapLocation){
		setMapPath(mapLocation);
	}

	/**
	 * Parse the robots initial location
	 */
	static void parseInitialLocation(string strX, string strY, string strYaw){
		unsigned x = atoi(strX.c_str());
		unsigned y = atoi(strY.c_str());
		unsigned yaw = atoi(strYaw.c_str());
		ComplexLocation cLoc = ComplexLocation(x,y,yaw);
		setRobotInitialLocation(cLoc);
	}

	/**
	 * Parse the target's location
	 */
	static void parseTargetLocation(string strX, string strY){
		unsigned x = atoi(strX.c_str());
		unsigned y = atoi(strY.c_str());

		Location loc = Location(x,y);
		setDestination(loc);
	}

	/**
	 * Parse the size of the robot
	 */
	static void parseRobotSize(string strXSize, string strYSize){
		unsigned x = atoi(strXSize.c_str());
		unsigned y = atoi(strYSize.c_str());

		setRobotSize(max(x,y));
	}

	/**
	 * Parse the map's resolution
	 */
	static void parseMapResolution(string strCell2Cm){
		float cell2Cm = atof(strCell2Cm.c_str());
		setPixel2Centimeter(cell2Cm);
	}

	/**
	 * Parse the map's resolution
	 */
	static void parseNavigationResolution(string strNavRes){
		float navRes = atof(strNavRes.c_str());
		setGridCell2Centimeter(navRes);
	}
};


#endif /* CONFIGURATION_H_ */
