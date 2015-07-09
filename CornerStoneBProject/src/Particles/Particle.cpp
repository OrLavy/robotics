/*
* Particle.cpp
*
*  Created on: Jun 23, 2015
*      Author: colman
*/

#include <Particles/Particle.h>

Particle::Particle(float x, float y, float yaw, float bel) {
	// TODO Auto-generated constructor stub
	cm_location.setX(x);
	cm_location.setY(y);
	cm_location.setYaw(yaw);
	this->belief = bel;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

ComplexLocation Particle::getLocation() {
	return cm_location;
}
void Particle::update(double xMoved, double yMoved, double yawMoved,LaserProxy *lp,MapObject& grid_map)
{
	float new_x = cm_location.getX() + xMoved;
	float new_y = cm_location.getY() + yMoved;


	float mapCmHalfWidth = ConfigurationsManager::getMapWidthCm() / 2;
	float mapCmHalfHeight = ConfigurationsManager::getMapHeightCm() / 2;
	// make sure rand_x, rand_y are in range on the grid.

	/*
	if (new_x >= mapCmHalfWidth)
	{
		new_x = mapCmHalfWidth;
	}
	else if (new_x < -mapCmHalfWidth)
	{
		new_x = -mapCmHalfWidth;
	}

	if (new_y >= mapCmHalfHeight)
	{
		new_y = mapCmHalfHeight;
	}
	else if (new_y < -mapCmHalfHeight)
	{
		new_y = -mapCmHalfHeight;
	}*/

	new_x = new_x >= mapCmHalfWidth ? mapCmHalfWidth : new_x < -mapCmHalfWidth? -mapCmHalfWidth : new_x;
	new_y = new_y >= mapCmHalfHeight ? mapCmHalfHeight : new_y < -mapCmHalfHeight ? -mapCmHalfHeight : new_y;

	//new_x = new_x >= grid_map.getWidth() ? grid_map.getWidth()-1 : new_x < 0? 0 : new_x;
	//new_y = new_y >= grid_map.getHeight() ? grid_map.getHeight()-1 : new_y < 0? 0 : new_y;

	cm_location.setX(new_x);
    cm_location.setY(new_y);

	cm_location.setYaw((float)fmod(cm_location.getYaw() + yawMoved, 2 * M_PI));

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
	srand (time(NULL));
	for(unsigned i = 0; i < CHILDREN_CREATE_AMOUNT; i++)
	{
		int rand_x = rand() % 2 - 1; // -15 to + 15
		int rand_y = rand() % 2 - 1;
		//float rand_yaw = fmod(rand(),2 * M_PI) - M_PI;
		//rand_yaw = fmod(cm_location.getYaw() + rand_yaw, 2 * M_PI);
		float rand_yaw = rand() % 2  + (this->getLocation().getYaw() * 180.0 / M_PI) - 1;
		rand_yaw = fmod(rand_yaw, 360.0);
	    rand_yaw *= M_PI / 180.0;


		children.push_back(Particle(rand_x + cm_location.getX(), rand_y + cm_location.getY(), rand_yaw, belief));
	}

	return children;
}

double Particle::calcMovement(double xMoved,double yMoved,double yawMoved)
{
/*
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
*/

	return MaxBelief;
}
double Particle::calcScan(LaserProxy* lp, MapObject& map)
{
	unsigned bad_calls = 0, good_calls = 0;

	float mapCmHalfWidth = ConfigurationsManager::getMapWidthCm() / 2;
	float mapCmHalfHeight = ConfigurationsManager::getMapHeightCm() / 2;

	for (unsigned i = 0; i < LASER_READINGS; i+= LASER_READ_STEP)
	{
		double current_angle = laserIndexToRad(i);
		double relevant_angle = current_angle + cm_location.getYaw();

		if (lp->GetRange(i) >= LASER_MIN_SCAN_RANGE / 100)
		{
			for (double k = 0; k <= lp->GetRange(i); k += (1/map.getCell2Cm()) )
			{
				double currX = cm_location.getX() + (k * 100 *  cos(relevant_angle));
				double currY = cm_location.getY() + (k * 100 *  sin(relevant_angle));

				currX = currX >= mapCmHalfWidth ? mapCmHalfWidth : currX < -mapCmHalfWidth? -mapCmHalfWidth : currX;
				currY = currY >= mapCmHalfHeight ? mapCmHalfHeight : currY < -mapCmHalfHeight ? -mapCmHalfHeight : currY;

			    if (map.getCellAtRealLocation(currX / 100.0f,currY / 100.0f) == Clear)
			    	good_calls ++;
			    else
			    	bad_calls ++;

			}
		}
		else
		{
			double currX = cm_location.getX() + cos(relevant_angle);
			double currY = cm_location.getY() + sin(relevant_angle);


			// make sure rand_x, rand_y are in range on the grid.
			currX = currX >= mapCmHalfWidth ? mapCmHalfWidth : currX < -mapCmHalfWidth? -mapCmHalfWidth : currX;
			currY = currY >= mapCmHalfHeight ? mapCmHalfHeight : currY < -mapCmHalfHeight ? -mapCmHalfHeight : currY;

			if (map.getCellAtRealLocation(currX / 100.0f,currY / 100.0f) == Occupied)
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
