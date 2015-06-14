/*
 * ActionObstacle.h
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#ifndef ACTIONOBSTACLE_H_
#define ACTIONOBSTACLE_H_

#include "Behaviour.h"

class Action_Obstacle: public Behaviour {
private:
	bool obstacle_from_right;
public:
	Action_Obstacle(Robot* robot);
	virtual ~Action_Obstacle(){}
	bool startCond();
	bool stopCond();
	void action();
};

#endif /* ACTIONOBSTACLE_H_ */