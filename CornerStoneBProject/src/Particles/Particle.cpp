/*
* Particle.cpp
*
*  Created on: Jun 23, 2015
*      Author: colman
*/

#include <Particles/Particle.h>

Particle::Particle(float x, float y, float yaw, float bel) {
	// TODO Auto-generated constructor stub
	pixel_pos.setX(x);
	pixel_pos.setY(y);
	pixel_pos.setYaw(yaw);
	this->belief = bel;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

ComplexPosition Particle::getPos() {
	return pixel_pos;
}
void Particle::update(double xMoved, double yMoved, double yawMoved,LaserProxy *lp,MapObject& grid_map)
{
	pixel_pos.setX(pixel_pos.getX() + xMoved);
	pixel_pos.setY(pixel_pos.getY() + yMoved);
	pixel_pos.setYaw((float)fmod(pixel_pos.getYaw() + yawMoved, 2 * M_PI));

	belief *= calcMovement(xMoved,yMoved,yawMoved) * calcScan(lp, grid_map) * BELIEF_FACTOR;
	belief = belief < NO_BELIEF ? NO_BELIEF : (belief > MaxBelief? MaxBelief : belief);
}

float Particle::getBelief()
{
	return this->belief;
}

vector<Particle> Particle::generateChildren()
{
	vector<Particle> children;

	for(unsigned i = 0; i < CHILDREN_CREATE_AMOUNT; i++)
	{
		unsigned rand_x = rand() % 20 - 10; // -10 to + 10
		unsigned rand_y = rand() % 20 - 10;
		float rand_yaw = fmod(rand(),2 * M_PI) - M_PI;
		rand_yaw = fmod(pixel_pos.getYaw() + rand_yaw, 2 * M_PI);

		children.push_back(Particle(rand_x + pixel_pos.getX(), rand_y + pixel_pos.getY(), rand_yaw, belief));
	}

	return children;
}

double Particle::calcMovement(double xMoved,double yMoved,double yawMoved)
{
	double distance = sqrt(pow(xMoved,2) + pow(yMoved,2));

	bool safe_move = distance < MAX_SAFE_MOVEMENT_DISTANCE;
	bool safe_rot = isInRange(yawMoved,-1,1);
	if (safe_move && safe_rot)
	{
		return MaxBelief;
	}
	else if(safe_move || safe_rot){
		if (safe_rot)
			return HIGH_BELIEF;
		else
		    return NORMAL_BELIEF;
	}
	else
	{
		return LOW_BELIEF;
	}
}
double Particle::calcScan(LaserProxy* lp, MapObject& map)
{
	unsigned bad_calls = 0, good_calls = 0;

	for (unsigned i = 0; i < LASER_READINGS; i+= LASER_READ_STEP)
	{
		double current_angle = laserIndexToRad(i);
		double relevant_angle = current_angle + pixel_pos.getYaw();

		if (lp->GetRange(i) >= LASER_MIN_SCAN_RANGE)
		{
			for (double k = 0; k <= LASER_MIN_SCAN_RANGE; k += (1/map.getCell2Cm()) )
			{
				double currX = pixel_pos.getX() + (k * cos(relevant_angle));
				double currY = pixel_pos.getY() + (k * sin(relevant_angle));

			    if (map.getCellAtPosition(currX,currY) == Clear)
			    	good_calls ++;
			    else
			    	bad_calls ++;

			}
		}
		else
		{
			double currX = pixel_pos.getX() + cos(relevant_angle);
			double currY = pixel_pos.getY() + sin(relevant_angle);

			if (map.getCellAtPosition(currX,currY) == Occupied)
				good_calls ++;
			else
				bad_calls ++;
		}
	}

	return ((double) good_calls) / (good_calls + bad_calls);
}

bool Particle::isInRange(double value, double min_val, double max_val) {
	return (value < min_val ? false : (value > max_val? false : true));
}

double Particle::laserIndexToRad(int index)
{
	double angle_for_sample = LASER_FIELD / LASER_READINGS;
	double deg_angle = index * angle_for_sample - LASER_FIELD / 2;

	return (deg_angle * M_PI / 180);
}
