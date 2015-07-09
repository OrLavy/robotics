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
#include "Commons/Utils.h"
#include "ConfigurationsManager.h"
#include <algorithm>

using namespace PlayerCc;

using namespace std;

class LocalizationManager {
private:
	Position2dProxy* pos_proxy;
	LaserProxy* laser_proxy;
	ComplexLocation last_location;
	ComplexLocation current_location;
	vector<Particle> particles;
	MapObject grid_map;

	void InitializeRandomParticles();
	static bool sortByBelief(Particle p1, Particle p2);
public:
	LocalizationManager(Position2dProxy &pp, LaserProxy* lp, MapObject& map);
	virtual ~LocalizationManager();
	ComplexLocation getEstimatedLocation();
	void UpdateParticles();
};

#endif /* LOCALIZATIONMANAGER_H_ */
