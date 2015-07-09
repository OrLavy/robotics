/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(Position2dProxy &pp, LaserProxy *lp, MapObject& map) {
	// TODO Auto-generated constructor stub
	pos_proxy = &pp;
	laser_proxy = lp;
	grid_map = map;
	particles = vector<Particle>();


	Location meters_robot_loc(pos_proxy->GetXPos(),pos_proxy->GetYPos());
	//cout << "ctor robot location meters (" << meters_robot_loc.getX() << "," << meters_robot_loc.getY() << ")" << endl;
	//GridPosition robot_cell_pos = Utils::GridPositionFromMapMeterLocation(meters_robot_loc, ConfigurationsManager::getGridCell2Centimeter(), &grid_map);
	//cout << "ctor robot location pixels (" << robot_cell_pos.getX() << "," << robot_cell_pos.getY() << ")" << endl;
	last_location.setX(meters_robot_loc.getX() * 100);
	last_location.setY(meters_robot_loc.getY() * 100);
	last_location.setYaw(pos_proxy->GetYaw());
	InitializeRandomParticles();
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}

void LocalizationManager::UpdateParticles()
{
	Location meters_robot_loc(pos_proxy->GetXPos(),pos_proxy->GetYPos());
	//GridPosition robot_cell_pos = Utils::GridPositionFromMapMeterLocation(meters_robot_loc, ConfigurationsManager::getGridCell2Centimeter(),& grid_map);
	double xMoved = meters_robot_loc.getX() * 100 - last_location.getX();
	double yMoved = meters_robot_loc.getY() * 100 - last_location.getY();
	double yawMoved = pos_proxy->GetYaw() - last_location.getYaw();

	last_location.setX(meters_robot_loc.getX() * 100);
	last_location.setY(meters_robot_loc.getY() * 100);
	last_location.setYaw(pos_proxy->GetYaw());
	//cout << "oudometry location (" << meters_robot_loc.getX() << "," << meters_robot_loc.getY() << "," << last_location.getYaw() * 180.0 / M_PI << ")" << endl;

	vector<Particle> toBeAddedParticles = vector<Particle>();

	vector<Particle>::iterator it = particles.begin();
	while (it != particles.end()){
		// Update the particle
		it->update(xMoved, yMoved, yawMoved,laser_proxy,grid_map);

		// If not probable - delete
		if (it->getBelief() < NORMAL_BELIEF && particles.size() > MaxParticleAmount / 5){
			it = particles.erase(it);
		} else {
			// Is there room for more particles ?
			if (toBeAddedParticles.size() + particles.size() < MaxParticleAmount && it->getBelief() > HIGH_BELIEF){
				vector<Particle> childParticles = it->generateChildren();
				toBeAddedParticles.insert(toBeAddedParticles.end(),childParticles.begin(),childParticles.end());
			}
			it++;
        }}

	/*
	toBeAddedParticles.sort([] (Particle& a, Particle& b) {
		return a.getBelief() < b.getBelief();
	});
	*/
	sort(toBeAddedParticles.begin(), toBeAddedParticles.end(), sortByBelief);

	vector<Particle>::iterator another_it = toBeAddedParticles.begin();
	unsigned available_space = MaxParticleAmount - particles.size();

	for (unsigned i = 0; i < available_space && i < toBeAddedParticles.size(); i++)
	{
		particles.push_back(*another_it);
		another_it ++;
	}


	sort(particles.begin(), particles.end(), sortByBelief);
	/*
	particles.sort([] ( Particle& a,  Particle& b) {
			return (a.getBelief() < b.getBelief());
		});
		*/
}

bool LocalizationManager::sortByBelief(Particle p1, Particle p2){
	return p1.getBelief() > p2.getBelief();
}


void LocalizationManager::InitializeRandomParticles()
{
	srand (time(NULL));
    unsigned particle_count = 0;

    cout << "About to generate particles around (" << last_location.getX() << "," << last_location.getY() << ")" << endl;

	while(particle_count < MaxParticleAmount)
	{
		//unsigned rand_x = rand() % grid_map.getWidth();

		//unsigned rand_y = rand() % grid_map.getHeight();

		int rand_x = rand() % 2 + (last_location.getX() - 1); // 0.25 meter radius
        int rand_y = rand() % 2 + (last_location.getY() - 1); // 0.15 meter radius

        int mapCmHalfWidth = ConfigurationsManager::getMapWidthCm() / 2;
        int mapCmHalfHeight = ConfigurationsManager::getMapHeightCm() / 2;
        // make sure rand_x, rand_y are in range on the grid.
        rand_x = rand_x >= mapCmHalfWidth ? mapCmHalfWidth : rand_x < -mapCmHalfWidth? -mapCmHalfWidth : rand_x;
        rand_y = rand_y >= mapCmHalfHeight ? mapCmHalfHeight : rand_y < -mapCmHalfHeight ? -mapCmHalfHeight : rand_y;

		//float rand_yaw = rand() % 360 + 1;
        float rand_yaw = rand() % 2 + (last_location.getYaw() * 180.0 / M_PI) - 1;
        rand_yaw = fmod(rand_yaw, 360.0);
		rand_yaw *= M_PI / 180.0;

		if (grid_map.getCellAtRealLocation(rand_x / 100.0f, rand_y / 100.0f) != Occupied)
		{
			Particle p =  Particle(rand_x, rand_y, rand_yaw, MaxBelief);
		    particles.push_back(p);
		    particle_count++;
		}

	}
}

ComplexLocation LocalizationManager::getEstimatedLocation()
{
	if (particles.empty())
	{
		current_location.setX(99999);
		current_location.setY(99999);
		Logger::log(ERROR, "Particles are empty");
		throw "";
	}

	Particle estimated = particles.front(); // works because it's sorted.

	return estimated.getLocation();
}
