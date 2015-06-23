/*
 * Robot.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port, ComplexLocation initial_location) {
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	decision_made = false;
	decided_direction_is_left = false;

	_pp->SetMotorEnable(true);
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		Read();

	_pp->SetOdometry(initial_location.getX(),initial_location.getY(), initial_location.getYaw());
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}

bool Robot::isBlocked(bool* is_blocked_from_right) {

	// Check if blocked from the right.
	if (!right_flank_clear())
	{
		// if still blocked but turning side was decided - keep it.
		if (!decision_made)
		{
			decided_direction_is_left = true;

			//_pp.SetSpeed(0.0, -0.3);
			decision_made = true;
		}
	}
	// Check if blocked from the left or front.
	else if (!left_flank_clear() || (*_lp)[forward] < 0.3f)
	{
		if (!decision_made)
		{
			decided_direction_is_left = false;
			//_pp.SetSpeed(0.0, 0.3);
			decision_made = true;
		}
	}
	// if not blocked from both sides - reset desition.
	else
	{
		//pp.SetSpeed(1.0,0);
		decision_made = false;
	}

	*is_blocked_from_right = decided_direction_is_left;
	return decision_made;
}

bool Robot::right_flank_clear()
{
	for(int i = forward + 50; i < 566; i+= 5)
	{
		// If the obstacle is near the front, stay further away.
		if ((*_lp)[i] < 0.85 - i * 0.001)
	    {
			//report_obstacle(i,(*_lp)[i], _pp);
	    	return false;
	    }
	}
	return true;
}

bool Robot::left_flank_clear()
{
	for(int i = 100; i < forward - 50; i+= 5)
	{
		// If the obstacle is near the front, stay further away.
	    if ((*_lp)[i] < 0.25 + i * 0.001)
	    {
	    	//report_obstacle(i,(*_lp)[i], _pp);
	    	return false;
	    }
	}
	return true;
}

bool Robot::isNearLocation(Location loc)
{
    float distance = getCurrentLocation().Distance(loc);

	if (distance < 0.3f) // TODO : check what does "near" mean in numbers...
	{
		return true;
	}

	return false;
}

void Robot::setTargetLocation(Location target)
{
	this->target_location = target;
}

Location Robot::getTargetLocation()
{
	return this->target_location;
}

Location Robot::getCurrentLocation()
{
	Location curr_loc((float)_pp->GetXPos(),(float)_pp->GetYPos());
	return curr_loc;
}
float Robot::getYaw()
{
	return _pp->GetYaw();
}
