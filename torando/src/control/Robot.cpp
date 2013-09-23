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
//  OVERVIEW: Robot.cpp
//  ========
//  Source file for robot.
#ifndef ROBOTCONTROL_H_
#include "Robot.h"
#endif
#ifndef COMMUNICATION_H_
#include <Communication.h>
#endif
#ifndef VECTOR_H_
#include <Vector.h>
#endif

#include <stdio.h>
#include <math.h>
#include <sys/time.h>

//////////////////////////////////////////////////////////
//
// Static variables
// ==========
TargetFixed Robot::passSource;
bool Robot::readyToPass = false;
TargetFixed Robot::passDestination;
bool Robot::readyToReceivePass = false;
bool Robot::passReceived = true;

//////////////////////////////////////////////////////////
//
// Constants
// ==========
#define pi 3.14159265359
const int angles[4] = { 60, 135, 225, 300 };
float wheelsAnglesRad[4] = { (double) angles[0] / 180 * pi, (double) angles[1] / 180 * pi, (double) angles[2] / 180 * pi, (double) angles[3] / 180 * pi };

//////////////////////////////////////////////////////////
//
// Robot implementation
// ==========
void Robot::lookAt(Target & lookat)
//[]----------------------------------------------------[]
//|  Look At                                             |
//[]----------------------------------------------------[]
		{
	this->lookat = lookat;
	looking = true;

	path.setLookAt(lookat);
	path.changeAngleApproach(atan2(lookat.y() - path.to.y(), lookat.x() - path.to.x()));
}

void Robot::stopLook()
//[]----------------------------------------------------[]
//|  Stop Look                                           |
//[]----------------------------------------------------[]
{
	looking = false;
}

void Robot::follow(Target & target)
//[]----------------------------------------------------[]
//|  Follow                                              |
//[]----------------------------------------------------[]
		{
	to = target;
	path.changeTarget(target);
	following = true;
}
void Robot::stopFollow()
//[]----------------------------------------------------[]
//|  Stop Follow                                         |
//[]----------------------------------------------------[]
{
	following = false;
}

void Robot::kickTo(Target & to, float power) {
	kicking = true;
	kickTarget = &to;
	kickPower = power;
}

void Robot::stopKicking() {
	kicking = false;
}

void Robot::block(int position)
//[]----------------------------------------------------[]
//|  Block                                               |
//[]----------------------------------------------------[]
		{
	blockPosition = position;
	blocking = true;
	kicking = true;
}
void Robot::stopBlock()
//[]----------------------------------------------------[]
//|  Stop Block                                          |
//[]----------------------------------------------------[]
{
	blocking = false;
	kicking = false;
}

void Robot::marki(RobotInfo * opponent)
//[]----------------------------------------------------[]
//|  Marki                                               |
//[]----------------------------------------------------[]
		{
	this->opponent = opponent;
	markingi = true;
}

void Robot::stopMarki()
//[]----------------------------------------------------[]
//|  Stop Marki                                          |
//[]----------------------------------------------------[]
{
	this->opponent = 0;
	kicking = false;
	markingi = false;
}

void Robot::mark(RobotInfo * opponent)
//[]----------------------------------------------------[]
//|  Mark                                                |
//[]----------------------------------------------------[]
		{
	this->opponent = opponent;
	marking = true;
}

void Robot::stopMark()
//[]----------------------------------------------------[]
//|  Stop Mark                                          |
//[]----------------------------------------------------[]
{
	this->opponent = 0;
	kicking = false;
	marking = false;
}

void Robot::passTo(Target target)
//[]----------------------------------------------------[]
//|  Pass To                                             |
//[]----------------------------------------------------[]
		{

	kicking = true;

	//TODO - fazer isso direito
	lookAt(target);
	if (!passing && passReceived) {
		passSource.set(Vision::ball.x(), Vision::ball.y());
		passing = true;
	}
}

void Robot::cancelPass()
//[]----------------------------------------------------[]
//|  Cancel Pass                                         |
//[]----------------------------------------------------[]
{
	passReceived = true;
	passing = false;
	kicking = false;
	stopFollow();
}

void Robot::receivePassFrom(Target robot, Target receivingPoint)
//[]----------------------------------------------------[]
//|  Receive Pass From                                   |
//[]----------------------------------------------------[]
		{
	//follow(receivingPoint);
	lookAt(robot);
	passDestination.set(receivingPoint.x(), receivingPoint.y());
	passReceived = false;
	receivingPass = true;
}

void Robot::cancelReceivePass()
//[]----------------------------------------------------[]
//|  Cancel Receive Pass                                 |
//[]----------------------------------------------------[]
{
	passReceived = true;
	receivingPass = false;
	stopFollow();
}

void Robot::goalKeeper() {
	goalkeeper = true;
}

void Robot::stopGoalKeeper() {
	goalkeeper = false;
}

void Robot::defendGoal(int defendPos) {
	defendPosition = defendPos;
	defendgoal = true;
}

void Robot::stopDefendGoal() {
	defendgoal = false;
}

void Robot::doInBackground()
//[]----------------------------------------------------[]
//|  Do In Back Ground                                   |
//[]----------------------------------------------------[]
{

	lookingPower = 15.0;

	float wheelsPower[4];

	for (int i = 0; i < 4; i++) {
		wheelsPower[i] = 0.0;
	}

	if (blocking) {
		Vector2D ballToGoal(Vision::goal.x() - Vision::ball.x(), Vision::goal.y() - Vision::ball.y());

		ballToGoal.normalize(300.0f);

		ballToGoal = ballToGoal.rotateRight(0.7f * blockPosition);

		TargetFixed blockPoint(Vision::ball.x() + ballToGoal.x(), Vision::ball.y() + ballToGoal.y());

		follow(blockPoint);
		lookAt(Vision::ball);
	}

	if (markingi) {

		if (opponent->distanceTo(Vision::ball) > 450.0) {
			stopKicking();
			Vector2D opponentToGoal(Vision::goal.x() - opponent->x(), Vision::goal.y() - opponent->y());

			opponentToGoal.normalize(300.0f);

			TargetFixed blockPoint(opponent->x() + opponentToGoal.x(), opponent->y() + opponentToGoal.y());

			follow(blockPoint);
			lookAt(Vision::ball);

		} else {

			Vector2D kickToPoint(Vision::ball.x() - info.x(), Vision::ball.y() - info.y());

			kickToPoint.normalize(150.0f);

			TargetFixed kickPoint(Vision::ball.x() + kickToPoint.x(), Vision::ball.y() + kickToPoint.y());

			kickTo(kickPoint);

		}
	}

	if (marking) {
		if (opponent->distanceTo(Vision::ball) > 450.0) {
			stopKicking();
			Vector2D opponentToGoal(Vision::ball.x() - opponent->x(), Vision::ball.y() - opponent->y());

			opponentToGoal.normalize(300.0f);

			TargetFixed blockPoint(opponent->x() + opponentToGoal.x(), opponent->y() + opponentToGoal.y());

			follow(blockPoint);
			lookAt(Vision::ball);

		} else {

			Vector2D kickToPoint(Vision::ball.x() - info.x(), Vision::ball.y() - info.y());

			kickToPoint.normalize(150.0f);

			TargetFixed kickPoint(Vision::ball.x() + kickToPoint.x(), Vision::ball.y() + kickToPoint.y());

			kickTo(kickPoint);

		}
	}

//Passar ou tocar
	if (passing) {
		float deltaX = passDestination.x() - Vision::ball.x();
		float deltaY = passDestination.y() - Vision::ball.y();

		Vector2D vector(deltaX, deltaY);
		vector.normalize(90.0f);

		//path.changeTarget(TargetFixed(Vision::ball.x() + vector.x(), Vision::ball.y() + vector.y()));
		TargetFixed target(Vision::ball.x() - vector.x(), Vision::ball.y() - vector.y());
		follow(target);
	}

	if (receivingPass) {
		Vector2D rightVector(passDestination.x() - passSource.x(), passDestination.y() - passSource.y());
		Vector2D ballVector(Vision::ball.x() - passSource.x(), Vision::ball.y() - passSource.y());

		float diffAngle = Vector2D::angle(rightVector, ballVector);

		float deslocNorm = rightVector.norm() * tan(diffAngle);

		if (passSource.distanceTo(Vision::ball) > 100.0f) {

			Vector2D correctionVector = rightVector.rotateRight();
			correctionVector.normalize(deslocNorm);

			TargetFixed target(passDestination.x() + correctionVector.x(), passDestination.y() + correctionVector.y());
			follow(target);

		} else {
			follow(passDestination);
		}

	}

	if (goalkeeper) {
		Vector2D goalKeeperPosition(Vision::ball.x() - Vision::goal.x(), Vision::ball.y() - Vision::goal.y());

		if (goalKeeperPosition.findAngle() > Vision::rightCornerAngle) {
			goalKeeperPosition.set(Vision::rightCornerVector);
		} else if (goalKeeperPosition.findAngle() < Vision::leftCornerAngle) {
			goalKeeperPosition.set(Vision::leftCornerVector);
		}

		goalKeeperPosition.normalize(450.0f);

		TargetFixed blockPoint(Vision::goal.x() + goalKeeperPosition.x(), Vision::goal.y() + goalKeeperPosition.y());

		follow(blockPoint);
		lookAt(Vision::ball);

	}

	if (defendgoal) {
		Vector2D defendPoint(Vision::ball.x() - Vision::goal.x(), Vision::ball.y() - Vision::goal.y());

		if (defendPoint.findAngle() > Vision::rightCornerAngle) {
			defendPoint.set(Vision::rightCornerVector);
		} else if (defendPoint.findAngle() < Vision::leftCornerAngle) {
			defendPoint.set(Vision::leftCornerVector);
		}

		defendPoint.normalize(700.0f);

		defendPoint = defendPoint.rotateRight(0.2f * defendPosition);

		TargetFixed blockPoint(Vision::goal.x() + defendPoint.x(), Vision::goal.y() + defendPoint.y());

		follow(blockPoint);
		lookAt(Vision::ball);

	}

	if (following) {
		followingPower = getPower(path.distanceToTarget());
		Target nextPoint = path.getNextPoint();
		float targetTheta = atan2(nextPoint.y() - info.y(), nextPoint.x() - info.x()) - info.orientation();

		for (int i = 0; i < 4; i++)
			wheelsPower[i] += sin(wheelsAnglesRad[i] - targetTheta) * followingPower;

	}

	if (looking) {
		float lookTheta = atan2(lookat.y() - info.y(), lookat.x() - info.x());

		float aDiff;
		aDiff = angleDiff(lookTheta, info.orientation());

		for (int i = 0; i < 4; i++)
			wheelsPower[i] += aDiff * lookingPower;
	}

	Communication::setWheelsVelocity(_id, wheelsPower[0], wheelsPower[1], wheelsPower[2], wheelsPower[3]);

	if (kicking) {

		if (kickTarget != 0) {
			Vector2D vector(Vision::ball.x() - kickTarget->x(), Vision::ball.y() - kickTarget->y());

			vector.normalize(90.0f);

			TargetFixed positionBehind(Vision::ball.x() + vector.x(), Vision::ball.y() + vector.y());

			TargetFixed target(positionBehind.x(), positionBehind.y());

			follow(target);
			lookAt(*kickTarget);

		}

		if (followingPower == 0.0f && info.distanceTo(Vision::ball) < 210.0f) {
			if (receivingPass) {
				readyToReceivePass = true;
				passReceived = true;
			}

			if (passing) {
				float power = sqrt(float(info.distanceTo(lookat))) / 15.0f;

				//passSource.set(Vision::ball.x(), Vision::ball.y());
				//if (readyToReceivePass)
				Communication::kick(_id, power);
				cancelPass();
				//passing = false;
			} else {
				Communication::kick(_id, kickPower);
			}
		}
	}

}

float Robot::getPower(int distanceTarget)
//[]----------------------------------------------------[]
//|  Get Power                                           |
//[]----------------------------------------------------[]
		{

	static timeval lastTime;

	if (distanceTarget >= 1024.0f) {
		timeval now;
		gettimeofday(&now, NULL);

		int deltaTime = now.tv_usec - lastTime.tv_usec;
		float correction = (deltaTime * 0.0005f);

		if (correction < 30 && correction > 0) {
			followingPower = (followingPower > -70) ? followingPower - correction : followingPower;
		}
	} else if (distanceTarget >= 30.0f) {
		followingPower = -70 * float(sqrt(distanceTarget) / 37.0f);
		followingPower = int(followingPower);
	} else {
		followingPower = 0.0;
	}
	gettimeofday(&lastTime, NULL);
	return followingPower;
}

float Robot::angleDiff(float angle1, float angle2)
//[]----------------------------------------------------[]
//|  Angle Diff                                          |
//[]----------------------------------------------------[]
		{
	float angleDiff;

	if (angle1 > angle2) {
		angleDiff = angle1 - angle2;

		if (angleDiff > M_PI) {
			angleDiff = float(M_PI - angle1) + float(M_PI + angle2);
			return -angleDiff;
		}
		return angleDiff;
	} else {
		angleDiff = angle2 - angle1;
		if (angleDiff > M_PI) {
			angleDiff = float(M_PI - angle2) + float(M_PI + angle1);
			return angleDiff;
		}
		return -angleDiff;
	}

}
