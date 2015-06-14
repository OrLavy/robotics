/*
 * ActionObstacle.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#include "ActionObstacle.h"

Action_Obstacle::Action_Obstacle(Robot* robot) : Behaviour(robot) {
	// TODO Auto-generated constructor stub
    obstacle_from_right = false;
}

bool Action_Obstacle::startCond()
{
    return true; // if the drive action returned false it comes here, therefore no need to check.
}
bool Action_Obstacle::stopCond()
{
    if (!_robot->isBlocked(&obstacle_from_right))
    {
    	return true;
    }

    return false;
}
void Action_Obstacle::action()
{
	if (obstacle_from_right)
	{
		// turn left
		_robot->setSpeed(0.0f, -0.3f);
	}
	else
	{
		// turn right
		_robot->setSpeed(0.0f, 0.3f);

	}
    // turn to the most 'free' side to avoid obstable.
    // later try driving to the latest waypoint as instructed.
}
