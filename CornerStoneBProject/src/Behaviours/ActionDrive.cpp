/*
 * ActionDrive.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#include "ActionDrive.h"
#include <math.h>

Action_Drive::Action_Drive(Robot* robot) : Behaviour(robot){
	// TODO Auto-generated constructor stub

}

bool Action_Drive::startCond()
{
	bool val;
    if (_robot->isBlocked(&val))
    {
    	return false;
    }

    return true;
}
bool Action_Drive::stopCond()
{
   bool val;

   // Check if road is blocked or if we reached the current target location(the waypoint).
   if (_robot->isBlocked(&val) || _robot->isNearLocation(_robot->getTargetLocation()))
   {
	   return true;
   }

   return false;
}
void Action_Drive::action()
{

	// calculate direction
    Location direction_unit_vector = (_robot->getTargetLocation() - _robot->getCurrentLocation()).Normalize();
    float rad_angle = atan2(direction_unit_vector.getY(), direction_unit_vector.getX());// gives the radian angle from x.

    // set positive speed in target direction
    _robot->setSpeed(1.0f,rad_angle - _robot->getYaw()); // TODO : Check! maybe we need to turn before we move anywhere!.
}
