/*
 * AStarPath.h
 *
 *  Created on: Jul 9, 2013
 *      Author: yuri
 */

#ifndef ASTARPATH_H_
#define ASTARPATH_H_

#include <Path.h>

class AStarPath: public Path {
	public:
		AStarPath(Target & from):Path(from) {
		}
		virtual ~AStarPath() {
		}

		TargetFixed getNextPoint();
		void generateNearestPoints(TargetFixed * vector, Target position, double distance);

};

class PoolTarget {

	PoolTarget() {}
	void add(Target target);

	private:


};

#endif /* ASTARPATH_H_ */
