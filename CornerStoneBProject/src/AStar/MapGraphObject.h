/*
 * MapGraphObject.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef MAPGRAPHOBJECT_H_
#define MAPGRAPHOBJECT_H_

#include "../Commons/MapObject.h"
#include "MatrixHolder.h"

#define WALL_COST 1000
#define NEAR_WALL_COST 3
#define CLEAR_COST 1

#define BLOW_SIZE 5
#define WALL_BLOW 10
#define NEAR_WALL_BLOW 5

class MapGraphObject {
private:
	MapObject _map;
	MatrixHolder<int> _costs = MatrixHolder<int>(WALL_COST);
public:
	MapGraphObject(MapObject& map);

	vector<GridPosition> neighbors(GridPosition center);

	unsigned cost(GridPosition from, GridPosition to);

private :
	void initializeCosts(){
		// First , set default values
		for (int y = 0; y < _map.getHeight(); y++){
			for (int x = 0; x < _map.getWidth(); x++){
				GridPosition pos = GridPosition(x,y);
				int cost;
				if (isWall(pos)){
					cost = WALL_COST;
				} else if (isNearWall(pos)){
					cost = NEAR_WALL_COST;
				} else {
					cost = CLEAR_COST;
				}
				_costs[pos] = cost;
			}
		}

		// Then , blow area near walls
		for (int y = 0; y < _map.getHeight(); y++){
			for (int x = 0; x < _map.getWidth(); x++){
				GridPosition pos = GridPosition(x,y);
				if (isWall(pos)){
					blowPriceArea(pos,WALL_BLOW);
				}
			}
		}
	}

	/**
	 * Checks if the give position is near a wall
	 */
	bool isNearWall(GridPosition pos){
		GridPosition up = pos.getRelativePosition(Up);
		GridPosition right = pos.getRelativePosition(Right);
		GridPosition down = pos.getRelativePosition(Down);
		GridPosition left = pos.getRelativePosition(Left);

		bool isNearWall = false;

		isNearWall = (
				((_map.isPositionValid(up)) && (isWall(up))) ||
				((_map.isPositionValid(right)) && (isWall(right))) ||
				((_map.isPositionValid(down)) && (isWall(down))) ||
				((_map.isPositionValid(left)) && (isWall(left)))
				);

		return isNearWall;
	}

	bool isWall(GridPosition pos){
		return _map.getCellAtPosition(pos) == Occupied;
	}

	void blowPriceArea(GridPosition pos, int blowSize){
		for (int radios = 1; radios < blowSize; radios ++){
			// The closer to the wall - the more expensive
			int increas = blowSize - radios;
			increasSquare(pos,radios,increas);
		}

		//increaseFair(pos,blowSize, blowSize);
	}

	void increaseFair(GridPosition pos, int radios, int inc){
		// Get edges
		int xLeft = pos.getX() - radios;
		int xRight = pos.getX() + radios;
		int yTopRow = pos.getY() + radios;
		int yBottomRow = pos.getY() -radios;

		for (int y = yBottomRow; y <= yTopRow; y++){
			for (int x = xLeft; x <= xRight; x++){
				GridPosition to = GridPosition(x,y);
				if (_costs.isPositionValid(to)){
					int dis = getDist(pos,to);
					int fairInc = inc - dis;
					if (fairInc > 0){
						_costs[to] = _costs[to] + fairInc;
					}
				}
			}
		}
	}

	int getDist(GridPosition from ,GridPosition to){
		return ((abs(from.getX() - to.getX())) +
				(abs(from.getY() - to.getY())));
	}

	void increasSquare(GridPosition pos, int radios, int inc){
		// Get edges
		int xLeft = pos.getX() - radios;
		int xRight = pos.getX() + radios;
		int yTopRow = pos.getY() + radios;
		int yBottomRow = pos.getY() -radios;

		// Top row
		for (int xCur = xLeft; xCur <= xRight; xCur++){
			GridPosition posCur(xCur,yTopRow);
			if (_costs.isPositionValid(posCur)){
				_costs[posCur] = _costs[posCur] + inc;
			}
		}

		// Bottom row
		for (int xCur = xLeft; xCur <= xRight; xCur++){
			GridPosition posCur(xCur,yBottomRow);
			if (_costs.isPositionValid(posCur)){
				_costs[posCur] = _costs[posCur] + inc;
			}
		}

		// Right col
		for (int yCur = yBottomRow + 1; yCur < yTopRow; yCur++){
			GridPosition posCur(xRight,yCur);
			if (_costs.isPositionValid(posCur)){
				_costs[posCur] = _costs[posCur] + inc;
			}
		}

		// Left col
		for (int yCur = yBottomRow + 1; yCur < yTopRow; yCur++){
			GridPosition posCur(xLeft,yCur);
			if (_costs.isPositionValid(posCur)){
				_costs[posCur] = _costs[posCur] + inc;
			}
		}
	}
};

#endif /* MAPGRAPHOBJECT_H_ */
