/*
 * Utils.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <ostream>

#include "MapObject.h"
#include "../PngUtils/PngUtil.h"

using namespace std;

class Utils {
public:


	//******************************
	//		Public static helper methods - Print& Save
	//******************************

	/**
	 * Prints the given map to the console
	 */
	static void printMap(MapObject& mapObject){
		for (unsigned y = 0; y < mapObject.getHeight(); y++){
			for (unsigned x = 0; x <mapObject.getWidth(); x++){
				cout << static_cast<char>(mapObject.getCellAtPosition(x,y));
			}
			cout << endl;
		}

		cout << endl;
	}

	/**
	 * Saves the given map as a png with the given name
	 */
	static void writeMapToPng(std::string path, MapObject& mapObject){

		PngUtil::mapObjectToPng(path.c_str(),mapObject);
	}
};

#endif /* UTILS_H_ */
