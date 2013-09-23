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

#ifndef THREADMODULE_H_
#include "ThreadModule.h"
#endif

//////////////////////////////////////////////////////////
//
// ThreadModule implementation
// ==========
ThreadModule::ThreadModule() :
		firstRun(true), running(false)
//[]----------------------------------------------------[]
//|  Constructor                                         |
//[]----------------------------------------------------[]
{
	printf("ThreadModule::ThreadModule()\n");
}

ThreadModule::~ThreadModule()
//[]----------------------------------------------------[]
//|  Destructor                                          |
//[]----------------------------------------------------[]
{
	printf("ThreadModule::~ThreadModule()\n");
	disconnect(getThread(), SIGNAL(started()), this, SLOT(exec()));
}

void ThreadModule::start()
//[]----------------------------------------------------[]
//|  Start                                               |
//[]----------------------------------------------------[]
{
	printf("ThreadModule::start()\n");
	if (firstRun) {
		moveToThread(getThread());
		connect(getThread(), SIGNAL(started()), this, SLOT(exec()));
		onConnectToThread(getThread());
	}

	running = true;
	getThread()->start();
}

void ThreadModule::stop()
//[]----------------------------------------------------[]
//|  Stop                                                |
//[]----------------------------------------------------[]
{
	printf("ThreadModule::stop()\n");
	running = false;
	getThread()->quit();
}

void ThreadModule::exec()
//[]----------------------------------------------------[]
//|  Exec                                                |
//[]----------------------------------------------------[]
{
	printf("ThreadModule::exec()\n");
	onPreExecute();
	while (running) {
		doInBackground();
		QThread::yieldCurrentThread();
	}
	onPosExecute();
}

void ThreadModule::onConnectToThread(QThread * thread) {
	/* Implemente isto nas classes que herdam de ThreadModule */
}

void ThreadModule::onDisconnectToThread(QThread * thread) {
	/* Implemente isto nas classes que herdam de ThreadModule */
}

void ThreadModule::onPreExecute() {
	/* Implemente isto nas classes que herdam de ThreadModule */
}

void ThreadModule::onPosExecute() {
	/* Implemente isto nas classes que herdam de ThreadModule */
}

