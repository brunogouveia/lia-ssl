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

	float followingPower = -70.0;
	float lookingPower = 10.0;

	float wheelsPower[4];

	if (!path.inDestination()) {
		Target nextPoint = path.getNextPoint();
		//TargetFixed nextPoint(path.to.x(),path.to.y());

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
	} else {
		Communication::setWheelsVelocity(_id, 0.0, 0.0, 0.0, 0.0);
	}
}
