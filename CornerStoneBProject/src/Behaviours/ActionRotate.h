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
private:
	Location direction_unit_vector;
	double rad_angle;
	bool direction_decided;
	bool passed_correct_angle;
	bool is_dir_right;
public:
	Action_Rotate(Robot* robot);
	virtual ~Action_Rotate(){};
	bool startCond();
	bool stopCond();
	void action();
};

#endif /* ACTIONROTATE_H_ */
