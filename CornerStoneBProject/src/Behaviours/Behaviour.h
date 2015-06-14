/*
 * Behavior.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef BEHAVIOUR_H_
#define BEHAVIOUR_H_
#include <vector>
#include "../Robot.h"
using namespace std;

class Behaviour {
	vector<Behaviour*> _behVect;
protected:
	Robot* _robot;
public:
	Behaviour();
	Behaviour(Robot* robot);
	virtual ~Behaviour();
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;
	void addBeh(Behaviour* next)
	{
		_behVect.push_back(next);
	}
	Behaviour* selectNext()
	{
		//Run over vector and return first true
		//startCond of the first behavior
		for (int i=0; i < _behVect.size(); i++)
		{
			if (_behVect[i]->startCond())
			{
				return _behVect[i];
			}
		}

		// aka still not out of behaviour,
		// because there is nothing else to choose.
		return this;
	}

};

#endif /* BEHAVIOR_H_ */
