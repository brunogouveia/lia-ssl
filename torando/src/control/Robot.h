/*
 * RobotControl.h
 *
 *  Created on: Apr 12, 2013
 *      Author: bruno
 */

#ifndef ROBOTCONTROL_H_
#define ROBOTCONTROL_H_

#include <QtCore>
#include <QThread>

#include <Vision.h>
#include <TargetInclude.h>
#include <Rrt.h>

#include <ThreadModule.h>

#include <Definitions.h>



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
				info(info), path(info, info), lookat(info), lookingPower(0.0f), followingPower(0.0f), looking(false), following(false) {

			/*TODO : encontrar o id correto*/
			//this->_id = findRobotId();
			this->_id = 0;

			start();
		}
		virtual ~Robot() {
			stop();
		}

		/**
		 *  Define o target para qual o robo deve ir.
		 */
		void follow(Target & target);

		void stopFollow() {
			following = false;
		}

		/**
		 *   Define o target para qual o robo deve olhar.
		 */
		void lookAt(Target & lookat = Vision::opponentGoal);

		void stopLook() {
			looking = false;
		}

		/**
		 *   Faz o robot chutar com a velocidade velocity m/s
		 */
		void kickTo(Target & to, float power);

		/**
		 *   Liga ou desliga o dribble.
		 */
		void dribble(bool on);

	private:
		virtual void doInBackground();

		float getPower(int);

		RobotInfo & info;
		Rrt path;
		Target lookat;

		int _id;
		float lookingPower, followingPower;

		bool looking, following;

		int findRobotId();

};

#endif /* ROBOTCONTROL_H_ */
