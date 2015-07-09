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
#include "GridPosition.h"
#include <math.h>

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

	//************
	//	Path assignment
	//************
	static void insertPathToMap(MapObject& map, vector<GridPosition> path){
		for (GridPosition pos : path){
			map.setCellAtPosition(pos, Path);
		}
	}
	static float locationFromActualPosition(unsigned position, float _cell2Cm){
		float aproximateLocation = (position * _cell2Cm) + (((float)_cell2Cm) / 2);
		return aproximateLocation;
	}

	static Location MapMeterLocationFromPixelLocation(Location position, float _pixel2Cm, float map_width_px, float map_height_px){
		float map_half_width_px = map_width_px / 2;
		float map_half_height_px = map_height_px / 2;

		float meters_from_center_x = (position.getX() - map_half_width_px) * _pixel2Cm / 100;
		float meters_from_center_y = -(position.getY() - map_half_height_px) * _pixel2Cm / 100;

		Location loc_from_center(meters_from_center_x,meters_from_center_y);
		return loc_from_center;
	}

	// same as above.
	static Location MapMeterLocationFromGridPosition(GridPosition position, float _cell2Cm, float map_width, float map_height){
			float map_half_width_px =map_width / 2;
			float map_half_height_px = map_height / 2;

			float meters_from_center_x = (position.getX() - map_half_width_px) * _cell2Cm / 100;
			float meters_from_center_y = -(position.getY() - map_half_height_px) * _cell2Cm / 100;

			Location loc_from_center(meters_from_center_x,meters_from_center_y);
			return loc_from_center;
		}


};

#endif /* UTILS_H_ */
