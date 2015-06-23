/*
 * LocalizationManager.h
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include <libplayerc++/playerc++.h>
#include "Commons/ComplexPosition.h"
#include "Commons/MapObject.h"
#include "Particle.h"
#include <vector>
#include <list>
#include "Globals.h"
#include <random>
#include <cmath>
#include "Commons/Logger.h"

using namespace PlayerCc;

using namespace std;

class LocalizationManager {
private:
	Position2dProxy* pos_proxy;
	LaserProxy* laser_proxy;
	ComplexPosition last_position;
	ComplexPosition current_position;
	vector<Particle> particles;
	MapObject grid_map;

	void InitializeRandomParticles();
public:
	LocalizationManager(Position2dProxy &pp, LaserProxy* lp, MapObject& map);
	virtual ~LocalizationManager();
	ComplexPosition getEstimatedLocation();
	void UpdateParticles();
};

#endif /* LOCALIZATIONMANAGER_H_ */
