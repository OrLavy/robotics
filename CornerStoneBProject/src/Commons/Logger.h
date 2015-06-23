/*
* Logger.h
*
*  Created on: Jun 23, 2015
*      Author: colman
*/

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include "../Globals.h"

using namespace std;

class Logger {
public:
	Logger();

	virtual ~Logger();

	static void log(LogLevel level, string message){

		std::cout << levelString(level) << message << endl;
	}

	static string levelString(LogLevel level){
		switch (level) {
		case DEBUG:
		return "DEBUG : ";
		break;
		case INFO:
		return "INFO : ";
		break;
		case ERROR:
		return "ERROR : ";
		break;

		default:
		return "GEN_LOG : ";
		break;
		}
	}
};

#endif /* LOGGER_H_ */
