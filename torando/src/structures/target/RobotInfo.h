/*
 * RobotInfo.h
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#ifndef ROBOTINFO_H_
#define ROBOTINFO_H_

#include <Target.h>
#include <Info.h>
#include "messages_robocup_ssl_detection.pb.h"

class RobotInfo: public Info {
	public:
		RobotInfo();
		virtual ~RobotInfo();

		float x() const {
			return _x;
		}

		float y() const {
			return _y;
		}

		float orientation() const {
			return _orientation;
		}

		float confidence() const {
			return _confidence;
		}
		float pixelx() const {
			return _pixelx;
		}

		float pixely() const {
			return _pixely;
		}

		bool onField() const {
			return _onField;
		}

		int id() const {
			return _id;
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

		float closestDistance(bool considerBall = true);

	private:
		int _id;
		float _orientation;
		float _confidence;
		float _pixelx;
		float _pixely;
		bool _onField;

		float _velX;
		float _velY;
		float _accX;
		float _accY;

		friend class Vision;
		friend class RobotList;
};

#endif /* ROBOTINFO_H_ */
