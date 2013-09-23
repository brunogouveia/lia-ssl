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
//  OVERVIEW: Communication.cpp
//  ========
//  Source file for communication.
#ifndef COMMUNICATION_H_
#include "Communication.h"
#endif

#include <stdio.h>

//////////////////////////////////////////////////////////
//
// Communication implementation
// ==========
Communication::Communication()
//[]----------------------------------------------------[]
//|  Constructor                                         |
//[]----------------------------------------------------[]
{
	printf("Communication::Communication\n");
}

Communication::~Communication()
//[]----------------------------------------------------[]
//|  Destructor                                          |
//[]----------------------------------------------------[]
{
	printf("Communication::~Communication\n");
}

void Communication::startModule()
//[]----------------------------------------------------[]
//|  Start Module                                        |
//[]----------------------------------------------------[]
{
	printf("Communication::startModule - started\n");
	getInstance().start();
	printf("Communication::startModule - finished\n");
}


void Communication::stopModule()
//[]----------------------------------------------------[]
//|  Stop Module                                         |
//[]----------------------------------------------------[]
{
	printf("Communication::stopModule - started\n");
	getInstance().stop();
	printf("Communication::stopModule - finished\n");
}

void Communication::changeInterval(int milSeconds)
//[]----------------------------------------------------[]
//|  Change Interval                                     |
//[]----------------------------------------------------[]
{
	printf("Communication::changeInterval - started\n");
	getInstance().setInterval(milSeconds);
	printf("Communication::changeInterval - finished\n");
}

void Communication::kick(int index, float XSpeed, float ZSpeed)
//[]----------------------------------------------------[]
//|  Kick                                                |
//[]----------------------------------------------------[]
{
	getInstance().packets[index].kickXSpeed = XSpeed;
	getInstance().packets[index].kickZSpeed = ZSpeed;

}

void Communication::drible(int index, bool drible)
//[]----------------------------------------------------[]
//|  Drible                                              |
//[]----------------------------------------------------[]
{
	printf("Communication::drible - started\n");
	getInstance().packets[index].spinner = drible;
	printf("Communication::drible - finished\n");
}

void Communication::setWheelsVelocity(int index, float frontLeft, float backLeft, float backRight, float frontRight)
//[]----------------------------------------------------[]
//|  Set Wheels Velocity                                 |
//[]----------------------------------------------------[]
{
	//printf("Communication::setWheelsVelocity - started\n");
	getInstance().packets[index].wheels[0] = frontLeft;
	getInstance().packets[index].wheels[1] = backLeft;
	getInstance().packets[index].wheels[2] = backRight;
	getInstance().packets[index].wheels[3] = frontRight;
	//printf("Communication::setWheelsVelocity - finished\n");
}

void Communication::onPreExecute()
//[]----------------------------------------------------[]
//|  On Pre Execute                                      |
//[]----------------------------------------------------[]
{
	printf("Communication::onPreExecute - started\n");
	udpsocket.close();
	bool flag = _addr.setHost("127.0.0.1", 20011);
	if (udpsocket.open(20011, false, false, false) && flag)
		printf("SendPacket conectou\n");
	printf("Communication::onPreExecute - finished\n");
}

void Communication::doInBackground()
//[]----------------------------------------------------[]
//|  Do In Back Ground                                   |
//[]----------------------------------------------------[]
{
	//printf("Communication::doInBackGround - started\n");

	grSim_Packet packet;

	bool yellow = false;
	packet.mutable_commands()->set_isteamyellow(yellow);
	packet.mutable_commands()->set_timestamp(0.0);
	for (int i = 0; i < 10; i++) {
		grSim_Robot_Command* command = packet.mutable_commands()->add_robot_commands();
		command->set_id(i);

		command->set_wheelsspeed(true);
		command->set_wheel1(packets[i].wheels[0]);
		command->set_wheel2(packets[i].wheels[1]);
		command->set_wheel3(packets[i].wheels[2]);
		command->set_wheel4(packets[i].wheels[3]);
		command->set_veltangent(0.0);
		command->set_velnormal(0.0);
		command->set_velangular(0.0);
		command->set_kickspeedx(packets[i].kickXSpeed);
		command->set_kickspeedz(packets[i].kickZSpeed);
		packets[i].kickXSpeed = 0.0f;
		packets[i].kickZSpeed = 0.0f;
		command->set_spinner(packets[i].spinner);
	}
	std::string s;
	packet.SerializeToString(&s);
	udpsocket.send((void*) s.c_str(), s.length(), _addr);
	//printf("Communication::doInBackGround - finished\n");
}

void Communication::onPosExecute()
//[]----------------------------------------------------[]
//|  On Pos Execute                                      |
//[]----------------------------------------------------[]
{
	printf("Communication::onPosExecute - started\n");
	udpsocket.close();
	printf("Communication::onPosExecute - finished\n");
}
