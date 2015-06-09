/*
 * MapObject.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: colman
 */

#include "MapObject.h"

//************
//	Ctor and initializers
//************
MapObject::MapObject() {
	this->_cell2Cm = 1;
	this->_height = 0;
	this->_width = 0;
	this->defineDimensions(0,0);
}

MapObject::MapObject(vector<vector<GridCell> > cellMatrix, unsigned width, unsigned height, float cell2cm){
	this->_cellMatrix = cellMatrix;
	this->_width = width;
	this->_height = height;
	this->_cell2Cm = cell2cm;
}

MapObject::~MapObject(){
	this->_cellMatrix.clear();
}

void MapObject::defineDimensions(unsigned width, unsigned height){
	// Keep the new dimensions
	this->_width = width;
	this->_height = height;

	// Set number of rows
	this->_cellMatrix.resize(height);

	// In each row , set number of
	for (unsigned y = 0; y < height; y++){
		this->_cellMatrix[y].resize(width);
	}
}

void MapObject::clearMatrix(){
	unsigned width, height;
	height = this->getHeight();
	width  = this->getWidth();

	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width ; x++){
			this->_cellMatrix[y][x] = Clear;
		}
	}
}

