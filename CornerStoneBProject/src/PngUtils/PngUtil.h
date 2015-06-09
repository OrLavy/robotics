/*
 * pngUtil.h
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */

#ifndef PNGUTIL_H_
#define PNGUTIL_H_
#include <iostream>
#include <vector>

#include "../Globals.h"
#include "../ConfigurationsManager.h"
#include "../Commons/MapObject.h"

//***************
//	Pixel handling methods
//***************


class PngUtil{
public:
	//***************
	//	Main PNG and Grid methods
	//***************
	/**
	 *	Gets the map from the given filename and return it in a MapObject form.
	 */
	static MapObject mapObjectFromPng(const char* filename);

	/**
	 *	Gets a map object and saves it as a PNG file
	 */
	static void mapObjectToPng(const char* filename , MapObject& mapObject);

private:

	//***************
	//	Private helper methods - conversion
	//***************
	/**
	 * Gets a pixel vector (each pixel is four bytes) and convert the data
	 * to cell data and put it in the target.
	 */
	static void convertByteVectorToMapObject(std::vector<unsigned char> source,MapObject& target,unsigned width, unsigned height);

	/**
	 * Gets a Map object and convert the data
	 * to pixel byte vector(each pixel is four bytes) and put it in the target.
	 */
	static void convertMapObjectToByteVector(MapObject source,std::vector<unsigned char>& target);

	/**
	 * Gets a vector of pixels (Each represented by 4 bytes) and
	 * returns true if the pixel i
	 */
	static GridCell gridCellFromPixel(std::vector<unsigned char>& pixelsVector, unsigned pixelBegining);

	//***************
	//	Private helper methods - File handling
	//***************
	/**
	 * Encode from raw pixels to disk with a single function call
	 * 	The image argument has width * height RGBA pixels or width * height * 4 bytes
	 */
	static void encodeOneStep(const char* filename, std::vector<unsigned char> image, unsigned width, unsigned height);
};

#endif /* PNGUTIL_H_ */
