/*
 * ActionRotate.h
 *
 *  Created on: Jun 15, 2015
 *      Author: colman
 */

#ifndef ACTIONROTATE_H_
#define ACTIONROTATE_H_

#include "Behaviour.h"

class Action_Rotate: public Behaviour {
public:
	Action_Rotate(Robot* robot);
	virtual ~Action_Rotate(){};
	bool startCond();
	bool stopCond();
	void action();
};

#endif /* ACTIONROTATE_H_ */
