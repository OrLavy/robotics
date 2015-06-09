/*
 * AStarSearcher.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "AStarSearcher.h"

AStarSearcher::AStarSearcher() {
}

void AStarSearcher::aStarSearch(MapGraphObject mapGraph,
		GridPosition start, GridPosition target,
		MatrixHolder<GridPosition>& parentsMap,
		MatrixHolder<int>& costMap){
	MyPq frontier;

	cout << "From is : " ;
	start.printString();
	cout << endl;

	cout << "Target is : " ;
	target.printString();
	cout << endl;


	// initialize the start node
	frontier.put(start, 0);
	parentsMap.setValueAtPosition(start,start);
	costMap.setValueAtPosition(start,0);

	// Perform the search
	while (!frontier.empty()){
		GridPosition current = frontier.get();
		//cout << LOG_DEBUG << "Cur is node X=" << current.getX() << " and Y=" << current.getY() << endl;

		if (current == target){
			cout << LOG_INFO << "Reached target" << endl;
			break;
		}
		vector<GridPosition> neighbors = mapGraph.neighbors(current);
		for (GridPosition next : neighbors){

			int newCost = costMap[current] + mapGraph.cost(current,next);

			// Is the next node was not reached yet ? or dose the new cost is lower than
			// the cast it had so far ?
			if ((costMap.isPositionDefault(next)) || (newCost < costMap[next])){

				cout << LOG_DEBUG << "Astar on node X=" << next.getX() << " and Y=" << next.getY() << " Because : ";
				if (costMap.isPositionDefault(next)){
					cout << "Node was not visited, given cost is " << newCost << endl;
				} else {
					cout << newCost <<  " is cheaper than " << costMap[next] << endl;
				}

				costMap[next] = newCost;

				// Get the new priority of the node
				int priority = newCost + heuristic(next, target);

				frontier.put(next, priority);
				parentsMap[next] = current;
				// cout << "X=" << next.getX() << ",Y=" << next.getY() << " parent is X=" <<cameFrom[next].getX() << ",Y=" << cameFrom[next].getY() <<endl;
			}
		}
	}
	cout << LOG_DEBUG << "Finished A* getting path "  << endl;
	if (parentsMap.isPositionDefault(target)){
		cout << "Target was never reached" << endl;
	}
}

