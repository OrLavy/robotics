/*
 * Map.h
 *
 *  Created on: May 27, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include "PngUtils/PngUtil.h"
#include "Commons/MapObject.h"
#include "Globals.h"
#include "Commons/Utils.h"
using namespace std;

class Map {
private:

	//*************************
	//		members
	//*************************
	MapObject rawMap;	// Raw map - pixel identical to the PNG file
	MapObject blownMap;	// Raw map after blowing obstacles
	MapObject navigationMap; // Raw map after fixing resolution

public:
	Map();
	~Map();
	/**
	 * Reads the map from the given PNG file and dose the following :
	 * 1. Keeps the original map as a cell grid in a 1:1 ratio.
	 * 2. Creates a Blown map , used for the A* path finding algorithm.
	 * 3. Creates a Scaled map , used for the localization manager.
	 */
	void readMapFromPng(std::string path);

	//**********************
	//	Map objects accessors
	//**********************
	MapObject getNavMap(){
		return navigationMap;
	}

	MapObject getBlownMap(){
		return blownMap;
	}

	//**********************
	//	Map/Grid printing/saving
	//**********************
	/**
	 * Takes the currently used raw grid and keep it as a PNG file with the given name.
	 */
	void saveRawMapAsPng(std::string fileName){
		Utils::writeMapToPng(fileName,this->rawMap);
	}

	/**
	 * Takes the currently used blown map and keep it as a PNG file with the given name.
	 */
	void saveBlownMapAsPng(std::string fileName){
		Utils::writeMapToPng(fileName, this->blownMap);
	}

	/**
	 * Takes the currently used navigation map and keep it as a PNG file with the given name.
	 */
	void saveNavigationMapAsPng(std::string fileName){
		Utils::writeMapToPng(fileName,this->navigationMap);
	}

	/**
	 * Prints the raw map.
	 */
	void printRawMap(){
		Utils::printMap(rawMap);
	}

	/**
	 *	Prints the blown map
	 */
	void printBlownMap(){
		Utils::printMap(blownMap);
	}

	/**
	 * Prints the navigation Map;
	 */
	void printNavigationMap(){
		Utils::printMap(navigationMap);
	}

private :
	//******************************
	//		Private logic methods
	//******************************
	/**
	* Takes the current map and blow its walls for added safety
	* by half the size of the robot.
	*/
	void makeBlownMap();

	void makeResulotionizedMapFromRawGrid();

	/**
	 * Returns the amount of pixel that needs to be blown from the
	 * raw pixel map in order to create the blown map.
	 */
	unsigned calculateAmountOfPixelesToBlow(){
		unsigned robotSize = ConfigurationsManager::getRobotSize();
		unsigned pixel2Cm = ConfigurationsManager::getPixel2Centimeter();

		// Amount is half the size of the robot in pixels
		return ceil((robotSize / 2) / (float)pixel2Cm);
	}

	/**
	 * Takes the given cell and fill an "Occupied" square around it
	 */
	void blowAreaInMap(MapObject& mapObject, unsigned x, unsigned y, unsigned blowSize){
		for (unsigned yModifier = y - blowSize; yModifier < y + blowSize;yModifier++){
			for (unsigned xModifier = x - blowSize; xModifier < x + blowSize; xModifier++){
				if(mapObject.isPositionValid(xModifier,yModifier)){
					mapObject.setCellAtPosition(xModifier,yModifier,Occupied);
				}
			}
		}
	}

	/**
	 * Gets an source map object and a location in the reductad map.
	 * Scans the area of the matching cells in the source map and return true only if they
	 * are all clear
	 */
	GridCell reductArea(MapObject& source, unsigned x, unsigned y, unsigned reductionSize){
		unsigned yBegin = y * reductionSize;
		unsigned xBegin = x * reductionSize;

		bool areaClear = true;

		for (unsigned yModifier = yBegin; yModifier < yBegin + reductionSize;yModifier++){
			for (unsigned xModifier = xBegin; xModifier < xBegin + reductionSize; xModifier++){
				// Check that er are not passing the ssource borders
				if(source.isPositionValid(xModifier,yModifier)){
					if (source.getCellAtPosition(xModifier,yModifier) == Occupied){
						areaClear = false;
						// Ugly , but quicker than double break
						goto ScanQuickFailur;
					}
				}
			}
		}

		ScanQuickFailur:

		if (areaClear){
			return Clear;
		} else {
			return Occupied;
		}
	}
};

#endif /* MAP_H_ */
