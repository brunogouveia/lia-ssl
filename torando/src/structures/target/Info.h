/*
 * Info.h
 *
 *  Created on: Aug 15, 2013
 *      Author: bruno
 */

#ifndef INFO_H_
#define INFO_H_

#include <Target.h>
#include <Kalm.h>

class Info: public Target {
	public:
		Info() {
			kalman.setKalman(0, 0);
		}
		virtual ~Info() {}

	protected:
		Kalman kalman;

};

#endif /* INFO_H_ */
