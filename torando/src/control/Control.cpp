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
//  OVERVIEW: Control.cpp
//  ========
//  Source file for control.
#ifndef CONTROL_H_
#include "Control.h"
#endif
#ifndef ROBOTCONTROL_H_
#include <Robot.h>
#endif
#include <unistd.h>

//////////////////////////////////////////////////////////
//
// Robot implementation
// ==========
Control::Control() :
		testRobot(Vision::robots[0]), testRobot2(Vision::robots[1]), testRobot3(Vision::robots[2])/*, testRobot4(Vision::robots[3]), testRobot5(Vision::robots[4])*/
//[]----------------------------------------------------[]
//|  Constructor                                         |
//[]----------------------------------------------------[]
{

}

Control::~Control()
//[]----------------------------------------------------[]
//|  Destructor                                          |
//[]----------------------------------------------------[]
{
}

void Control::onPreExecute()
//[]----------------------------------------------------[]
//|  On Pre Execute                                      |
//[]----------------------------------------------------[]
{
}

void Control::doInBackground()
//[]----------------------------------------------------[]
//|  Do In Back Ground                                   |
//[]----------------------------------------------------[]
{
	//printf("Control::doInBackGround - started\n");

	//testRobot.passTo(Vision::robots[1]);
	//testRobot2.receivePassFrom(Vision::robots[0], TargetFixed(0,0));
	testRobot.goalKeeper();
	testRobot2.defendGoal(-1);
	testRobot3.defendGoal(1);
	//testRobot4.block(-2);
	//testRobot5.block(2);


	/*testRobot2.lookAt();
	 testRobot2.follow(target);

	 testRobot3.lookAt();
	 testRobot3.follow(target);

	 testRobot4.lookAt();
	 testRobot4.follow(target);*/

	/*testRobot.passTo(Vision::robots[1]);
	testRobot2.receivePassFrom(Vision::robots[0], TargetFixed(0, 0));*/

	sleep(4000000);

	//printf("Control::doInBackGround - finished\n");

}

void Control::onPosExecute()
//[]----------------------------------------------------[]
//|  On Pos Execute                                      |
//[]----------------------------------------------------[]
{
}

void Control::callStrategy()
//[]----------------------------------------------------[]
//|  Call Strategy                                       |
//[]----------------------------------------------------[]
{
}

