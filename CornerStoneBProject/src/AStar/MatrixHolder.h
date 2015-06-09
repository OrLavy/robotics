/*
 * MatrixHolder.h
 *
 *  Created on: Jun 7, 2015
 *      Author: colman
 */

#ifndef MATRIXHOLDER_H_
#define MATRIXHOLDER_H_

#include <vector>
#include "../Commons/GridPosition.h"

using namespace std;

template <class matrixType>
class MatrixHolder {
	vector<vector<matrixType> > _valuesMatrix;
	unsigned _width; // cells in y
	unsigned _height; // cells in x

	matrixType _defaultValue;
public:
	MatrixHolder(matrixType defaultValue){
		this->_defaultValue = defaultValue;
	}

	/**
	 * Redefines the size of the matrix
	 */
	void defineDimensions(unsigned width, unsigned height){
		// Keep the new dimensions
		this->_width = width;
		this->_height = height;

		// Set number of rows
		this->_valuesMatrix.resize(height);

		// In each row , set number of
		for (unsigned y = 0; y < height; y++){
			this->_valuesMatrix[y].resize(width);
		}

		clearMatrix();
	}
	/**
	 *	Fill the matrix with default cells
	 */
	void clearMatrix(){
		unsigned width, height;
		height = this->getHeight();
		width  = this->getWidth();

		for (unsigned y = 0; y < height; y++) {
			for (unsigned x = 0; x < width ; x++){
				this->_valuesMatrix[y][x] = _defaultValue;
			}
		}
	}

	//************
	//	Position validators
	//************
	bool isPositionValid(unsigned x, unsigned y){
		return ((x >= 0) && (x < _width)) &&
				((y >= 0) && (y < _height));
	}

	bool isPositionValid(GridPosition pos){
		return (isPositionValid(pos.getX(), pos.getY()));
	}

	bool isPositionDefault(GridPosition pos){
		matrixType value = getValueAtPosition(pos);
		return value == _defaultValue;
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

	/**
	 * Gets the cell at the given position from the matrix.
	 *
	 * Note : if an invalid position was given , no value is returned
	 */
	matrixType getValueAtPosition(unsigned x,  unsigned y){
		// Ensure borders
		if (ensureCellPositionValid(x,y)){
			return _valuesMatrix[y][x];
		} else {
			cout << LOG_ERROR << "Invalid position given to 'MatrixHolder.getCellAtPosition' , no value returned." << endl;
		}
	}

	/**
	 * Gets the cell at the given position from the matrix.
	 *
	 * Note : if an invalid position was given , no value is returned
	 */
	matrixType getValueAtPosition(GridPosition pos){
		return getValueAtPosition(pos.getX(), pos.getY());
	}

	void setValueAtPosition(unsigned x,  unsigned y, matrixType value){
		// Ensure borders
		if (ensureCellPositionValid(x,y)){
			_valuesMatrix[y][x] = value;
		} else {
			cout << LOG_ERROR << "Invalid position given to 'setCellAtPosition' , no value returned." << endl;
		}
	}

	void setValueAtPosition(GridPosition pos,matrixType value){
		setValueAtPosition(pos.getX(),pos.getY(),value);
	}

	//************
	//	Operators
	//************
	matrixType& operator[](GridPosition pos){
		return getCellReference(pos);
	}

private:
	//************
	//	Utility access methods
	//************
	matrixType& getCellReference(GridPosition pos){
		if (isPositionValid(pos)){
			return _valuesMatrix[pos.getY()][pos.getX()];
		} else {
			cout << LOG_ERROR << "Invalid position given to MatrixHolder.getCellReference : X="
					<< pos.getX() << ",Y=" << pos.getY() << endl;
			throw "Out of boundries exception";
		}
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
		cout << "ERROR : " << "Matrix holder was given out of boundaries values. "
				<< "The boundaries are X=" << x << " and Y=" << y
				<< " But given location was X=" << x << " and Y=" << y << endl;
		throw ("Out of map matrix bounds !");
	}
};



#endif /* MATRIXHOLDER_H_ */
