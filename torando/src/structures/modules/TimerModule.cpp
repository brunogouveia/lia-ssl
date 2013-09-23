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
//  OVERVIEW: TimerModule.cpp
//  ========
//  Source file for abstract timer module.

#ifndef TIMERMODULE_H_
#include "TimerModule.h"
#endif

#include <stdio.h>

//////////////////////////////////////////////////////////
//
// TimerModule implementation
// ==========
TimerModule::TimerModule() :
		firstRun(true), running(false)
//[]----------------------------------------------------[]
//|  Constructor                                         |
//[]----------------------------------------------------[]
{
	printf("TimerModule::TimerModule\n");
}

TimerModule::~TimerModule()
//[]----------------------------------------------------[]
//|  Destructor                                          |
//[]----------------------------------------------------[]
{
	printf("TimerModule::~TimerModule\n");
	disconnect(getTimer(), SIGNAL(timeout()), this, SLOT(exec()));
}

void TimerModule::start()
//[]----------------------------------------------------[]
//|  Start                                               |
//[]----------------------------------------------------[]
{
	printf("TimerModule::start\n");
	if (firstRun) {
		connect(getTimer(), SIGNAL(timeout()), this, SLOT(exec()));
		getTimer()->setInterval(1);
		firstRun = false;
	}

	onPreExecute();
	running = true;
	getTimer()->start();
}

void TimerModule::stop()
//[]----------------------------------------------------[]
//|  Stop                                                |
//[]----------------------------------------------------[]
{
	printf("TimerModule::stop\n");
	getTimer()->stop();
	onPosExecute();
}

void TimerModule::setInterval(int milSeconds)
//[]----------------------------------------------------[]
//|  Set Interval                                        |
//[]----------------------------------------------------[]
{
	getTimer()->setInterval(milSeconds);
}

void TimerModule::exec()
//[]----------------------------------------------------[]
//|  Exec    	                                         |
//[]----------------------------------------------------[]
{
	//printf("TimerModule::exec\n");
	doInBackground();
	QThread::yieldCurrentThread();
}

void TimerModule::onConnectToTimer(QTimer * timer)
//[]----------------------------------------------------[]
//|  On Connect to Timer                                 |
//[]----------------------------------------------------[]
{
	printf("TimerModule::onConnectToTimer\n");
}
void TimerModule::onDisconnectToTimer(QTimer * timer)
//[]----------------------------------------------------[]
//|  On Disconnect to Timer	                             |
//[]----------------------------------------------------[]
{
	printf("TimerModule::onDisconnectToTimer\n");
}

void TimerModule::onPreExecute()
//[]----------------------------------------------------[]
//|  On Pre Execute                                      |
//[]----------------------------------------------------[]
{
	printf("TimerModule::onPreExecute\n");
}

void TimerModule::onPosExecute()
//[]----------------------------------------------------[]
//|  On Pos Execute                                      |
//[]----------------------------------------------------[]
{
	printf("TimerModule::onPosExecute\n");
}
