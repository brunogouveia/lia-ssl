#ifndef ROBOTCONTROL_H_
#define ROBOTCONTROL_H_

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
//  OVERVIEW: Robot.h
//  ========
//  Class definition for robot.

#include <QtCore>
#include <QThread>

#include <Vision.h>
#include <TargetInclude.h>
#include <Rrt.h>

#include <ThreadModule.h>

#include <Definitions.h>

//////////////////////////////////////////////////////////
//
// Robot: robot class
// ==========
class Robot: public ThreadModule {
	Q_OBJECT
	public:
		/**
		 *   Em geral, o robo está parado ou seguindo algum alvo (TargetFixed, RobotInfo, BallInfo,...)
		 *   Ele sozinho possui uma rota para ir ate o caminho, e caso voce passe um alvo dinamico (que
		 * pode mudar de posição repentinamente), como por exemplo BallInfo, ele automaticamente ajusta
		 * o caminho para ir aquela posição. Ele também se adapta a casos em que algum objeto entre no
		 * meio do caminho.
		 *
		 */

		Robot(RobotInfo & info) :
				info(info), path(info, info), lookat(info) {

			markingi = false;
			opponent = 0;
			blocking = false;
			lookingPower = 0.0f;
			followingPower = 0.0f;
			looking = false;
			following = false;
			kicking = false;
			passing = false;
			receivingPass = false;
			goalkeeper = false;
			kickPower = 12.0f;

			angleApproach = 0.0f;
			this->_id = info.id();
			printf("%d\n", this->_id);

			start();
		}
		virtual ~Robot() {
			stop();
		}

		/**************************************************************/
		/*********************  Basic skills   ************************/
		/**************************************************************/
		/**
		 *  Define o target para qual o robo deve ir.
		 */
		void follow(Target & target);
		void stopFollow();

		/**
		 *   Define o target para qual o robo deve olhar.
		 */
		void lookAt(Target & lookat = Vision::opponentGoal);
		void stopLook();

		/**
		 *   Faz o robot chutar com a velocidade velocity m/s
		 */
		void kickTo(Target & to, float power = 12.0f);
		void stopKicking();

		/**************************************************************/
		/*********************   skills        ************************/
		/**************************************************************/
		/**
		 * 		Faz com que o robo bloqueio o caminho da bola em direção ao gol
		 * formando uma barreira a frente da bola.
		 * 		Position é a posição da barreira que o robo deve ocupar. 0 significa
		 * que o robo deve ficar no centro, ficando diretamente em frente a bola.
		 * 1 significa que ele deve ficar ao lado direito da posição que ficaria se fosse 0.
		 * -1 ao lado esquerdo, ect...
		 */
		void block(int position = 0);
		void stopBlock();

		void marki(RobotInfo * opponent);
		void stopMarki();

		void mark(RobotInfo * opponent);
		void stopMark();

		void passTo(Target target);
		void cancelPass();

		void receivePassFrom(Target robot, Target receivingPoint);
		void cancelReceivePass();

		void goalKeeper();
		void stopGoalKeeper();

		void defendGoal(int defendPos);
		void stopDefendGoal();

	private:
		virtual void doInBackground();

		float getPower(int);

		float angleDiff(float, float);

		/*Atributos gerais.*/
		RobotInfo & info; 	//Info sobre o robo
		Rrt path;			//Objeto responsável por calcular os caminhos.
		Target lookat;		//Ponto para onde o robo deve estar "olhando"
		Target to;			//Ponto para onde o robo deve ir
		float angleApproach;			//Qual angulo o robo deve abordar o ponto de destino (em rad).
		int _id;			//id do radio correspondente ao robo

		/*Informações para o kickTo */
		bool kicking;
		Target * kickTarget;
		float kickPower;

		/*Informações para block skill*/
		bool blocking;		//Se o robo está bloqueando
		int blockPosition;	//Posição relativa para bloqueio

		/*Informações para marki skill*/
		bool markingi;
		RobotInfo * opponent; //OpponentInfo do robo que deve ser marcado

		/*Informações para mark skill */
		bool marking;

		/* Informações para a skill de goleiro */
		bool goalkeeper;

		/* Informações para a skill defendGoal */
		bool defendgoal;
		int defendPosition;

		bool looking, following;
		bool passing, receivingPass;

		float lookingPower, followingPower;
		int findRobotId();

		/***************Static************/
		static TargetFixed passSource;
		static bool readyToPass;
		static TargetFixed passDestination;
		static bool readyToReceivePass;
		static bool passReceived;

};
// Robot

#endif /* ROBOTCONTROL_H_ */
