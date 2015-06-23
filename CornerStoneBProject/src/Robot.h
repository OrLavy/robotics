/*
 * Robot.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>
#include "Commons/ComplexLocation.h"

#define forward 333

using namespace PlayerCc;
class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
	bool decision_made;
	bool decided_direction_is_left;
private:
	bool right_flank_clear();
	bool left_flank_clear();
	Location target_location;

public:
	Robot(char* ip, int port, ComplexLocation initial_loc);
	void Read() {
		_pc->Read();
	}
	void setSpeed(float xSpeed, float angularSpeed) {
		_pp->SetSpeed(xSpeed, angularSpeed);
	}
	void setTargetLocation(Location target);
	Location getTargetLocation();
	bool isBlocked(bool* is_blocked_from_right);
	bool isNearLocation(Location loc);
	Location getCurrentLocation();
	float getYaw();
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
