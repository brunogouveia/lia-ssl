/*
 * RobotControl.cpp
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#include "Robot.h"
#include "Communication.h"
#include <stdio.h>
#include <math.h>

#define pi 3.14159265359

const int angles[4] = { 60, 135, 225, 300 };

double wheelsAnglesRad[4] = { (double) angles[0] / 180 * pi, (double) angles[1] / 180 * pi, (double) angles[2] / 180 * pi, (double) angles[3] / 180 * pi };

void Robot::lookAt(Target & lookat) {
	this->lookat = lookat;
	looking = true;
}

void Robot::follow(Target & target) {
	path.changeTarget(target);
	following = true;
}

void Robot::doInBackground() {

	lookingPower = 10.0;

	printf("Following: %f\n", followingPower);
	float wheelsPower[4];

	followingPower = getPower(path.distanceToTarget());
	Target nextPoint;
	//if (path.distanceToTarget() > 1000.0f)
	nextPoint = path.getNextPoint();
	//else
	//nextPoint = path.to;

	for (int i = 0; i < 4; i++) {
		wheelsPower[i] = 0.0;
	}

	if (following) {
		float targetTheta = atan2(nextPoint.y() - info.y(), nextPoint.x() - info.x()) - info.orientation();

		for (int i = 0; i < 4; i++)
			wheelsPower[i] += sin(wheelsAnglesRad[i] - targetTheta) * followingPower;

	}

	if (looking) {
		float lookTheta = atan2(lookat.y() - info.y(), lookat.x() - info.x()) - info.orientation();

		for (int i = 0; i < 4; i++)
			wheelsPower[i] += lookTheta * lookingPower;
	}

	Communication::setWheelsVelocity(_id, wheelsPower[0], wheelsPower[1], wheelsPower[2], wheelsPower[3]);
}

float Robot::getPower(int distanceTarget) {
	printf("Distance %d %f\n", distanceTarget, -70 * (distanceTarget / 1024.0f));
	// return - (int(log((distanceTarget + 150) >> 7)) << 5);
	if (distanceTarget >= 1024.0f) {
		followingPower = (followingPower > -70) ? followingPower - 0.5f : followingPower;
	} else {
		followingPower = -70 * float((distanceTarget-45) / 1024.0f);
		followingPower = int(followingPower);
	}
	return followingPower;
}
