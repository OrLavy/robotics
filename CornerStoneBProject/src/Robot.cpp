/*
 * Robot.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port, ComplexLocation initial_location, MapObject grid_map) {
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	decision_made = false;
	decided_direction_is_left = false;

	cout <<"set odometry " << initial_location.getX() << "," << initial_location.getY() << endl;
	_pp->SetOdometry(initial_location.getX(),initial_location.getY(), initial_location.getYaw());

	_pp->SetMotorEnable(true);

	//For fixing Player's reading BUG
	while (_pp->GetXPos() == 0 && _pp->GetYPos() == 0)
	{
	    cout << "still trying to read position!!!" << endl;
	    Read();
	}

	loc_manager = new LocalizationManager(*_pp, _lp, grid_map);
	_grid_map = &grid_map;
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
	else if (!left_flank_clear() || (*_lp)[forward] < 0.4f)
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

	if (decision_made)
	{
		cout << "BLOCKED BLOCKED BLOCKED" << endl;
	}

	return decision_made;
}

bool Robot::right_flank_clear()
{
	double min_distance = 1000;
	for(int i = forward; i < 566; i+= 5)
	{
		min_distance = MIN(min_distance, (*_lp)[i]);
		// If the obstacle is near the front, stay further away.
		if ((*_lp)[i] < 0.6)
	    {
			//report_obstacle(i,(*_lp)[i], _pp);
	    	return false;
	    }
	}

	cout << "min obstacle distance right : " << min_distance << endl;
	return true;
}

bool Robot::left_flank_clear()
{
	double min_distance = 1000;
	for(int i = 100; i < forward; i+= 5)
	{
		min_distance = MIN(min_distance, (*_lp)[i]);
		// If the obstacle is near the front, stay further away.
	    if ((*_lp)[i] < 0.6)
	    {
	    	//report_obstacle(i,(*_lp)[i], _pp);
	    	return false;
	    }
	}

	cout << "min obstacle distance left : " << min_distance << endl;
	return true;
}

bool Robot::isNearLocation(Location loc)
{
    float distance = getCurrentLocation().Distance(loc);

	if (distance < 1.0f) // TODO : check what does "near" mean in numbers...
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
	//Location curr_loc((float)_pp->GetXPos(),(float)_pp->GetYPos());
    //ComplexPosition rob_pos = loc_manager->getEstimatedLocation();

    //Logger::log(INFO, "current location is " + )

    return (loc_manager->getEstimatedLocation().getLocation() / 100);//Utils::MapMeterLocationFromGridPosition(rob_pos.getPosition(), ConfigurationsManager::getGridCell2Centimeter(), _grid_map->getWidth(), _grid_map->getHeight());
	//return _grid_map->locationFromPosition(rob_pos.getPosition());
}
float Robot::getYaw()
{
	//return _pp->GetYaw();
	return loc_manager->getEstimatedLocation().getYaw();
}

void Robot::Update()
{
	loc_manager->UpdateParticles();
	Location meters_robot_loc = getCurrentLocation();
	//cout << "current robot location meters (" << meters_robot_loc.getX() << "," << meters_robot_loc.getY() << "," << getYaw() * 180.0 / M_PI << ")" << endl;
}
