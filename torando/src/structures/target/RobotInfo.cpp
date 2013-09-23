//[]------------------------------------------------------------------------[]
//|                                                                          |
//|                        Small Size League software                        |
//|                             Version 1.0                                  |
//|                     Laboratório de Inteligencia Artificial				 |
//| 				 Universidade Federal de Mato Grosso do Sul              |
//|					 Author: Bruno H. Gouveia, Yuri Claure					 |
//|																			 |
//[]------------------------------------------------------------------------[]
//
//  OVERVIEW: Referee.cpp
//  ========
//  Source file for referee.

#ifndef ROBOTINFO_H_
#include "RobotInfo.h"
#endif
#ifndef DEFINITIONS_H_
#include "Definitions.h"
#endif
#ifndef VISION_H_
#include "Vision.h"
#endif

//////////////////////////////////////////////////////////
//
// RobotInfo implementation
// ==========
RobotInfo::RobotInfo()
//[]----------------------------------------------------[]
//|  Constructor                                         |
//[]----------------------------------------------------[]
{
	// TODO Auto-generated constructor stub

}

RobotInfo::~RobotInfo()
//[]----------------------------------------------------[]
//|  Destructor                                          |
//[]----------------------------------------------------[]
{
	// TODO Auto-generated destructor stub
}

float RobotInfo::closestDistance( bool considerBall)
//[]----------------------------------------------------[]
//|  Closest Distance                                    |
//[]----------------------------------------------------[]
{
	float distance = 10000.0f;

	if (considerBall) {
		distance = Vision::ball.distanceTo(*this);
	}

	int numRobots = Vision::robots.size();
	for (int i = 0; i < numRobots; i++) {
		float dist = Vision::robots[i].distanceTo(*this);

		if (_id != Vision::robots[i].id() && dist < distance)
			distance = dist;
	}

	numRobots = Vision::opponents.size();
	for (int i = 0; i < numRobots; i++) {
		float dist = Vision::opponents[i].distanceTo(*this);

		if (dist > 0.8 * ROBOT_RADIUS && dist < distance)
			distance = dist;
	}
	return distance;
}
