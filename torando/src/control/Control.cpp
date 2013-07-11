/*
 * Control.cpp
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#include "Control.h"
#include "Robot.h"
#include <unistd.h>

Control::Control() : testRobot(Vision::robots[0]) {
	//Referee referee = Referee::getInstance();
	//connect(&referee, SIGNAL(newCommand()), this, SLOT(callStrategy()));
}

Control::~Control() {
	//Referee referee = Referee::getInstance();
	//disconnect(&referee, SIGNAL(newCommand()), this, SLOT(callStrategy()));
}

void Control::onPreExecute() {
	//testRobot.start();
}

void Control::doInBackground() {
	//printf("Control::doInBackGround - started\n");


	testRobot.lookAt();
	testRobot.follow(Vision::ball);

	usleep(1000);

	//printf("Control::doInBackGround - finished\n");

}

void Control::onPosExecute() {
}

void Control::callStrategy() {

}

