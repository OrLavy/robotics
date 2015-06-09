/*
 * pngUtil.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */
#include "PngUtil.h"
#include "lodepng.h"
#include <iostream>


//******************
//	Main methods
//******************
MapObject PngUtil::mapObjectFromPng(const char* filename) {
	std::vector<unsigned char> rawImage; // Raw pixels & alpha's
	unsigned width,height;
	unsigned error = lodepng::decode(rawImage,width,height,filename);

	if (error) {
		std::cout << "decoder error " << error << ": "
						<< lodepng_error_text(error) << std::endl;
		throw "PNG decoding error ! " + error;
	}

	MapObject mapObject;
	mapObject.defineDimensions(width, height);

	// Convert the raw pixels to actual grid cells
	convertByteVectorToMapObject(rawImage,mapObject,width,height);

	// Return the loaded map as grid of cells
	return mapObject;
}

void PngUtil::mapObjectToPng(const char* filename, MapObject& mapObject) {
	// Get the measurements
	unsigned width = mapObject.getWidth();
	unsigned height = mapObject.getHeight();

	// Allocate a vector for the bytes array
	std::vector<unsigned char> rawPixels;
	rawPixels.resize(width * height * 4);

	// Convert the map object to raw pixels
	convertMapObjectToByteVector(mapObject,rawPixels);

	// Make a png from the raw pixels
	encodeOneStep(filename, rawPixels,width, height);
}

//******************
//	Helper methods
//******************
void PngUtil::convertByteVectorToMapObject(std::vector<unsigned char> source,MapObject& target,unsigned width, unsigned height) {
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			// Find out where the byte representation of the pixel begins
			unsigned pixelNumber = y * width + x;
			unsigned pixelBegining = 4 * pixelNumber;

			// Assign the matching gridCell value
			target.setCellAtPosition(x,y,gridCellFromPixel(source,pixelBegining));
		}
	}
}

void PngUtil::convertMapObjectToByteVector(MapObject source,std::vector<unsigned char>& target) {
	unsigned height = source.getHeight();
	unsigned width = source.getWidth();
	for (unsigned y = 0; y < height; y++) {
			for (unsigned x = 0; x < width; x++) {
				unsigned pixelNumber = y * width + x;
				unsigned pixelBegining = 4 * pixelNumber;

				unsigned red = ClearPixel.red;
				unsigned green = ClearPixel.green;
				unsigned blue = ClearPixel.blue;
				unsigned alpha = 255;

				// Decide the color of the pixel
				switch(source.getCellAtPosition(x,y)){
				case Clear :
					break;
				case Occupied :
					red = OccupiedPixel.red;
					green = OccupiedPixel.green;
					blue = OccupiedPixel.blue;
					break;
				case Path:
					red = PathPixel.red;
					green = PathPixel.green;
					blue = PathPixel.blue;
					break;
				case Target:
					red = TargetPixel.red;
					green = TargetPixel.green;
					blue = TargetPixel.blue;
					break;
				case Source:
					red = SourcePixel.red;
					green = SourcePixel.green;
					blue = SourcePixel.blue;
					break;
			}

				// Fill the pixel color in the target
				target[pixelBegining + 0] = red;
				target[pixelBegining + 1] = green;
				target[pixelBegining + 2] = blue;
				target[pixelBegining + 3] = alpha;
			}
		}
}

GridCell PngUtil::gridCellFromPixel(std::vector<unsigned char>& pixelsVector,
		unsigned pixelBegining) {
	// If any of the bytes are not 0 - the fixel is colored.
	bool pixelColored = (pixelsVector[pixelBegining + 0]) ||
						(pixelsVector[pixelBegining + 1]) ||
						(pixelsVector[pixelBegining + 2]);

	// Colored pixel means a wall
	if (pixelColored) {
		return Clear;
	} else {
		return Occupied;
	}
}

void PngUtil::encodeOneStep(const char* filename, std::vector<unsigned char> image,
		unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}
