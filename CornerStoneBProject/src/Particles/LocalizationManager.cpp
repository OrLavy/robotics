/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(Position2dProxy &pp, LaserProxy* lp, MapObject& map) {
	// TODO Auto-generated constructor stub
	pos_proxy = &pp;
	laser_proxy = lp;
	grid_map = map;
	particles = vector<Particle>();

	InitializeRandomParticles();
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}

void LocalizationManager::UpdateParticles()
{
	double xMoved = pos_proxy->GetXPos() - last_position.getX();
	double yMoved = pos_proxy->GetYPos() - last_position.getY();
	double yawMoved = pos_proxy->GetYaw() - last_position.getYaw();

	list<Particle> toBeAddedParticles;

	vector<Particle>::iterator it = particles.begin();
	while (it != particles.end()){
		// Update the particle
		it->update(xMoved, yMoved, yawMoved,laser_proxy,grid_map);

		// If not probable - delete
		if (it->getBelief() < BELIEF_LOWER_LIMIT){
			it = particles.erase(it);
		} else {
			// Is there room for more particles ?
			if (toBeAddedParticles.size() + particles.size() < MaxParticleAmount){
				vector<Particle> childParticles = it->generateChildren();
			}
			it++;
        }}

	toBeAddedParticles.sort([] (Particle& a, Particle& b) {
		return a.getBelief() < b.getBelief();
	});

	it = particles.begin();
	unsigned available_space = MaxParticleAmount - particles.size();

	for (unsigned i = 0; i < available_space && i < toBeAddedParticles.size(); i++)
	{
		particles.push_back(*it);
		it ++;
	}
}

void LocalizationManager::InitializeRandomParticles()
{
	srand (time(NULL));
    unsigned particle_count = 0;

	while(particle_count < MaxParticleAmount)
	{
		unsigned rand_x = rand() % grid_map.getWidth();

		unsigned rand_y = rand() % grid_map.getHeight();
		float rand_yaw = rand() % 360 + 1;
		rand_yaw *= M_PI / 180.0;
        GridPosition pos(rand_x, rand_y);

		if (grid_map.getCellAtPosition(pos) != Occupied)
		{
			Particle p =  Particle(rand_x, rand_y, rand_yaw, MaxBelief);
		    particles.push_back(p);
		    particle_count++;
		}

	}
}

ComplexPosition LocalizationManager::getEstimatedLocation()
{
	if (particles.empty())
	{
		current_position.setX(99999);
		current_position.setY(99999);
		Logger::log(ERROR, "Particles are empty");
		throw "";
	}

	Particle estimated = particles.front(); // works because it's sorted.

	return estimated.getPos();
}
