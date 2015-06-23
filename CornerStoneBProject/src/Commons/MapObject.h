/*
 * MapObject.h
 *
 *  Created on: Jun 4, 2015
 *      Author: colman
 */

#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

using namespace std;

#include <iostream>
#include <vector>
#include <cmath>

#include "../Globals.h"
#include "GridPosition.h"
#include "Location.h"

/**
 * Used to represent a single map as a matrix of GridCells.
 * Also adds utilities to convert actual locations to cells in the matrix
 */
class MapObject {
private :
	vector<vector<GridCell> > _cellMatrix;
	unsigned _width; // cells in y
	unsigned _height; // cells in x
	float _cell2Cm; // sq cm of every cell (Initialized to 1)
public:
	//************
	//	Ctor and initializers
	//************
	/**
	 * Creates a new map with initialized members.
	 */
	MapObject();
	MapObject(vector<vector<GridCell> >, unsigned width, unsigned height, float cell2cm);
	~MapObject();

	/**
	 * Redefines the size of the matrix
	 */
	void defineDimensions(unsigned width, unsigned height);

	/**
	 *	Fill the matrix with "clear" cells
	 */
	void clearMatrix();

	//************
	//	Access validation
	//************
	bool isPositionValid(unsigned x, unsigned y){
		return ((x > 0) && (x < _width)) &&
				((y > 0) && (y < _height));
	}

	bool isPositionValid(GridPosition pos){
		return (isPositionValid(pos.getX(), pos.getY()));
	}

	//************
	//	Accessors
	//************

	unsigned getHeight() const {
		return _height;
	}

	unsigned getWidth() const {
		return _width;
	}

	float getCell2Cm() const {
		return _cell2Cm;
	}

	void setCell2Cm(float cell2Cm) {
		_cell2Cm = cell2Cm;
	}

	/**
	 * Gets the cell at the given position from the matrix.
	 *
	 * Note : if an invalid position was given , no value is returned
	 */
	GridCell getCellAtPosition(unsigned x,  unsigned y){
		// Ensure borders
		if (ensureCellPositionValid(x,y)){
			return _cellMatrix[y][x];
		} else {
			cout << LOG_ERROR << "Invalid position given to 'getCellAtPosition' , no value returned." << endl;
		}
	}

	/**
	 * Gets the cell at the given position from the matrix.
	 *
	 * Note : if an invalid position was given , no value is returned
	 */
	GridCell getCellAtPosition(GridPosition pos){
		return getCellAtPosition(pos.getX(), pos.getY());
	}

	void setCellAtPosition(unsigned x,  unsigned y, GridCell value){
		// Ensure borders
		if (ensureCellPositionValid(x,y)){
			_cellMatrix[y][x] = value;
		} else {
			cout << LOG_ERROR << "Invalid position given to 'setCellAtPosition' , no value returned." << endl;
		}
	}

	void setCellAtPosition(GridPosition pos,GridCell value){
		setCellAtPosition(pos.getX(),pos.getY(),value);
	}

	/**
	 * Returns the cell that contains the given actual location
	 */
	GridCell getCellAtRealLocation(float x,  float y){
		GridPosition position = positionFromLocation(x,y);
		return getCellAtPosition(position.getX(),position.getY());
	}

	/**
	 * Gets the position from the given location coordinates
	 */
	GridPosition positionFromLocation(float x, float y){
		unsigned xPos = positionFromActualLocation(x);
		unsigned yPos = positionFromActualLocation(y);
		return GridPosition(xPos,yPos);
	}

	/**
	 * Gets the position from the given location object
	 */
	GridPosition positionFromLocation(Location location){
		return positionFromLocation(location.getX(),location.getY());
	}

	/**
	 * Retrun an aproximate location of the given grid position
	 */
	Location locationFromPosition(GridPosition position){
         Location loc(locationFromActualPosition(position.getX())
        		 , locationFromActualPosition(position.getY()));
         return loc;
	}

private :
	//************
	//	Utility calculation methods
	//************

	/**
	 * Gets an "actual location" representer (in cm from the zero point)
	 *
	 * Note : By this calculation , each whole number belongs the the cell that was before him
	 * 	For example : Res is 2 cm per cell , location is 10.0 so the matching cell will be the fifth cell;
	 */
	unsigned positionFromActualLocation(float location){
		unsigned cell;
		if (location == 0){
			//	Zero is zero
			cell = 0;
		} else {
			// Round up the division and subtract 1 (zero based array)
			cell = ceil(location / this->_cell2Cm) - 1;
		}

		return cell;
	}

	/**
	 * Returns an actual world location(float) that is about in the middle
	 * of the given grid location
	 */
	float locationFromActualPosition(unsigned position){
		float aproximateLocation = (position * _cell2Cm) + (((float)_cell2Cm) / 2);
		return aproximateLocation;
	}

	//************
	//	Utility validation methods
	//************
	/**
	 * Ensures the the position is valid for the given matrix
	 */
	bool ensureCellPositionValid(unsigned x,  unsigned y){
		if ((x >= this->getWidth()) || (y >= this->getHeight())){
			this->throwOutOfBoundsException(x,y);
			return false;
		} else {
			return true;
		}
	}

	/**
	 * Print error and throw exception
	 */
	void throwOutOfBoundsException(unsigned x,  unsigned y){
		cout << "ERROR : " << "Map object was given out of boundaries values. "
				<< "The boundaries are X=" << x << " and Y=" << y
				<< " But given location was X=" << _width << " and Y=" << _height << endl;
		throw ("Out of map matrix bounds !");
	}


};

#endif /* MAPOBJECT_H_ */
