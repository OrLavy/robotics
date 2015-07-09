/*
 * Particle.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */
#include "Commons/ComplexLocation.h"
#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <math.h>
#include <Commons/MapObject.h>
#include <libplayerc++/playerc++.h>
#include <vector>
#include <ConfigurationsManager.h>

using namespace PlayerCc;

class Particle {
private:
	ComplexLocation cm_location;
	float belief;

	double laserIndexToRad(int index);
	bool isInRange(double value, double min_val, double max_val);
public:

	Particle(float x, float y, float yaw, float bel);
	virtual ~Particle();
	ComplexLocation getLocation();
	void update(double xMoved, double yMoved, double yawMoved,LaserProxy* lp,MapObject& grid_map);
	float getBelief();
	vector<Particle> generateChildren();
	double calcMovement(double xMoved,double yMoved,double yawMoved);
	double calcScan(LaserProxy* lp, MapObject& map);

};

#endif /* PARTICLE_H_ */
