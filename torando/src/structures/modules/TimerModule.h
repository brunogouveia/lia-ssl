#ifndef TIMERMODULE_H_
#define TIMERMODULE_H_

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
//  OVERVIEW: TimerModule.h
//  ========
//  Class definition for timer module.

#include <Module.h>

#include <QObject>
#include <QtCore>
#include <QTimer>

//////////////////////////////////////////////////////////
//
// TimerModule: abstract timer module class
// ==========
class TimerModule: public Module {
	Q_OBJECT
	protected:
		/*
		 *
		 *   TimerModule é uma classe derivada de Module, onde possui um QTimer.
		 *   Qualquer módulo que derivar de TimerModule, tem uma característica:
		 * a repetição do método doInBackGround() será controlada por um timer,
		 * onde você escolhe o intervalo.
		 */

		TimerModule();
		virtual ~TimerModule();

		QTimer t;
		QTimer * getTimer() {
			return &t;
		}

		/*   O método start() e stop() são métodos importantes e ja implentados que
		 * controlam a execução do módulo.
		 *   O cilo de um módulo é o seguinte: quando ele for iniciado, é executado
		 * uma vez o método start(), depois o método doInBackGround() fica sendo executado
		 * repetidamente até o módulo parar (método stop() ser invocado), depois o método
		 * onPosExecute() é chamado uma unica vez.
		 *
		 *   IMPORTANTE: Aconselhamos a não reimplementar estes métodos. */
		virtual void start();
		virtual void stop();

		/*   Este método muda o intervalo em que o timer será disparado, ou seja, muda o tempo
		 * de espera entre cada execução do método doInBackGround(). */
		void setInterval(int milSeconds);


		virtual void onConnectToTimer(QTimer * timer);
		virtual void onDisconnectToTimer(QTimer * timer);

		virtual void onPreExecute();
		virtual void doInBackground()=0;
		virtual void onPosExecute();

	protected slots:
		void exec();

	protected:
		bool firstRun;
		bool running;
};

#endif /* TIMERMODULE_H_ */
