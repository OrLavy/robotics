/*
7 * ActionDrive.h
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#ifndef ACTIONDRIVE_H_
#define ACTIONDRIVE_H_

#include "Behaviour.h"

class Action_Drive: public Behaviour {
public:
	Action_Drive(Robot* robot);
	virtual ~Action_Drive(){}
	bool startCond();
	bool stopCond();
	void action();
};

#endif /* ACTIONDRIVE_H_ */
