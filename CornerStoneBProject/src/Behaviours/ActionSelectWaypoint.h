/*
 * ActionSelectWaypoint.h
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#ifndef ACTIONSELECTWAYPOINT_H_
#define ACTIONSELECTWAYPOINT_H_

#include "Behaviour.h"
#include "WayPointsManager.h"

class Action_SelectWaypoint: public Behaviour {
private:
	bool isWaypointSet;
	WayPointsManager* wpManager;
public:
	Action_SelectWaypoint(Robot* robot);
	virtual ~Action_SelectWaypoint(){};
	bool startCond();
	bool stopCond();
	void action();

	void setWaypointManager(WayPointsManager* wp);
};

#endif /* ACTIONSELECTWAYPOINT_H_ */
