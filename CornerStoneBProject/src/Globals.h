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

#endif /* GLOBALS_H_ */
