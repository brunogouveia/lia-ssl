#ifndef BALLINFO_H_
#define BALLINFO_H_

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
//  OVERVIEW: BallInfo.h
//  ========
//  Class definition for ball info.

#include <Target.h>
#include <Info.h>
#include "messages_robocup_ssl_detection.pb.h"

//////////////////////////////////////////////////////////
//
// BallInfo: ball info class
// ==========
class BallInfo: public Info {
	public:
		BallInfo():_velX(0),_velY(0),_accX(0),_accY(0){}
		virtual ~BallInfo(){}

		float x() {
			return _x;
		}

		float y() {
			return _y;
		}

		float z() {
			return _z;
		}

		float confidence() {
			return _confidence;
		}

		float pixelx() {
			return _pixelx;
		}

		float pixely() {
			return _pixely;
		}

		float velocityX() {
			return _velX;
		}

		float velocityY() {
			return _velY;
		}
		float accelerationX() {
			return _accX;
		}
		float accelerationY() {
			return _accY;
		}

		bool onField() {
			return _onField;
		}

		void updateBall(SSL_DetectionBall & ball) {
			static BallInfo balls[3];
			balls[0] = balls[1];
			balls[1] = balls[2];

			balls[2]._x = ball.x();
			balls[2]._y = ball.y();
			balls[2]._z = ball.z();
			_x = (balls[0]._x + balls[1]._x + balls[2]._x) / 3;
			_y = (balls[0]._y + balls[1]._y + balls[2]._y) / 3;
			_z = (balls[0]._z + balls[1]._z + balls[2]._z) / 3;

			_velX = _x - balls[2].x();
			_velY = _y - balls[2].y();
		}

	private:

		//float _x;
		//float _y;
		float _z;
		float _confidence;
		float _pixelx;
		float _pixely;
		bool _onField;

		float _velX;
		float _velY;
		float _accX;
		float _accY;

		friend class Vision;
};

#endif /* BALLINFO_H_ */
