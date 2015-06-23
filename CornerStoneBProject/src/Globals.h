/*
 * Globals.h
 *
 *  Created on: Jun 1, 2015
 *      Author: colman
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

//**********************
//	DEFINE
//**********************
# define LOG_ERROR "ERROR : "
# define LOG_INFO  "INFO : "
# define LOG_FINE "FINE : "
# define LOG_DEBUG "DEBUG : "

//**********************
//	Structs
//**********************
struct Pixel {
	unsigned red;
	unsigned green;
	unsigned blue;
};

//**********************
//	Enums
//**********************
enum GridCell {Clear = ' ', Occupied = '*', Path='%', Target='T', Source='S'};

enum Directions { Up,Up_Right, Right,Down_Right ,Down, Down_Left, Left, Up_Left};

enum LogLevel {DEBUG, INFO , ERROR};

//**********************
//	Constants
//**********************



/**
 * Black is clear
 */
static const Pixel ClearPixel= {
		255,255,255
};

/**
 * White is occupied
 */
static const Pixel OccupiedPixel  = {
		0,0,0
};

/**
 * Path is green
 */
static const Pixel PathPixel = {
		0,255,0
};

/**
 * Source is blue
 */
static const Pixel SourcePixel = {
		0,0,255
};

/**
 * Target is green
 */
static const Pixel TargetPixel = {
		255,0,0
};

static const unsigned int MaxParticleAmount = 200;
static const float MaxBelief = 1.0;

static const float TOTAL_BELIEF = MaxBelief;
static const float HIGH_BELIEF = MaxBelief * 0.75;
static const float NORMAL_BELIEF = MaxBelief * 0.50;
static const float LOW_BELIEF = MaxBelief * 0.25;
static const float NO_BELIEF = MaxBelief * 0;

static const float BELIEF_FACTOR = 1.06;

static const float BELIEF_LOWER_LIMIT = NORMAL_BELIEF;

static const float MAX_SAFE_MOVEMENT_DISTANCE = 30;

static const unsigned LASER_READINGS = 666;
static const unsigned LASER_READ_STEP = 5;
static const double LASER_FIELD = 240.0;
static const double LASER_MIN_SCAN_RANGE = 75; //cm
static const unsigned CHILDREN_CREATE_AMOUNT = 10;

#endif /* GLOBALS_H_ */
