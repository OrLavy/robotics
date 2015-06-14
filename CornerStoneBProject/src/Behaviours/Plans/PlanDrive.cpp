/*
 * PlanDrive.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "PlanDrive.h"

PlanDrive::PlanDrive(Robot* robot) : Plan(robot) {
	//Creating Behaviors
	_beh[0] = new Action_SelectWaypoint(robot);
	_beh[1] = new Action_Drive(robot);
	_beh[2] = new Action_Obstacle(robot);
	//Connecting Behaviors
	_beh[0]->addBeh(_beh[1]); // first select a waypoint and than move to it.
	_beh[1]->addBeh(_beh[2]);
	_beh[1]->addBeh(_beh[0]); // driving can lead to a waypoint -> and then we select a new one.
	_start = _beh[0];
}

PlanDrive::PlanDrive(Robot* robot, WayPointsManager* wpManager) : PlanDrive(robot) {
    ((Action_SelectWaypoint*)_beh[0])->setWaypointManager(wpManager);
}

PlanDrive::~PlanDrive() {
	// TODO Auto-generated destructor stub
	for(int i=0;i<3;i++)
		delete _beh[i];
}
Behaviour* PlanDrive::getStartPoint() {
	return this->_start;
}
