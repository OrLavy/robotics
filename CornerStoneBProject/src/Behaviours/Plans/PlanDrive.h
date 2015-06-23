/*
 * PlanDrive.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef PLANDRIVE_H_
#define PLANDRIVE_H_

#include "Plan.h"
#include "../ActionRotate.h"
#include "../ActionDrive.h"
#include "../ActionObstacle.h"
#include "../ActionSelectWaypoint.h"
#include "WayPointsManager.h"

class PlanDrive: public Plan {
	Behaviour* _beh[4];

public:
	PlanDrive(Robot* robot);
	PlanDrive(Robot* robot, WayPointsManager* wpManager);
	Behaviour* getStartPoint();
	virtual ~PlanDrive();
};

#endif /* PLANDRIVE_H_ */
