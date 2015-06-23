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

    cout << "started Action_Drive" <<endl;
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
    // set positive speed in target direction
    _robot->setSpeed(1.0f,0.0f); // simply drive straight.
}
