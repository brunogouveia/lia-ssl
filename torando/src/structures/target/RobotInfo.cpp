/*
 * RobotInfo.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#include "RobotInfo.h"

#include "Definitions.h"
#include "Vision.h"

RobotInfo::RobotInfo() {
	// TODO Auto-generated constructor stub

}

RobotInfo::~RobotInfo() {
	// TODO Auto-generated destructor stub
}

float RobotInfo::closestDistance( bool considerBall) {
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
