/*
 * ActionSelectWaypoint.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#include <Behaviours/ActionSelectWaypoint.h>

Action_SelectWaypoint::Action_SelectWaypoint(Robot* robot) : Behaviour(robot){
	// TODO Auto-generated constructor stub
	isWaypointSet = false;
}

bool Action_SelectWaypoint::startCond()
{
	// check if the robot is near our current waypoint.
    if (_robot->isNearLocation(wpManager->getCurrnetWayPoint().getLocation()))
    {
    	isWaypointSet = false; // do it before we select a waypoint. so action will be called.
    	return true;
    }

    // the robot is not close to the current waypoint. cant switch waypoints.
    return false;
}
bool Action_SelectWaypoint::stopCond()
{
	// if the waypoint was not set, stay in the behaviour.
	// basicly im just making sure the action func ran atleast once.
   return isWaypointSet;
}
void Action_SelectWaypoint::action()
{
	// if you reached your current waypoint, set a new one!
	if (_robot->isNearLocation(wpManager->getCurrnetWayPoint().getLocation()))
	{
		wpManager->advanceWayPoint();
	}

	// Give the robot his current target. (might be the same way point if he didn't reach it or a new one).
	_robot->setTargetLocation(wpManager->getCurrnetWayPoint().getLocation());

	isWaypointSet = true;
}

void Action_SelectWaypoint::setWaypointManager(WayPointsManager* wp)
{
	this->wpManager = wp;
}

