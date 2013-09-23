#ifndef ASTARPATH_H_
#define ASTARPATH_H_

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
//  OVERVIEW: AStarPath.h
//  ========
//  Class definition for a star path.

#include <Path.h>

//////////////////////////////////////////////////////////
//
// AStarPath: a star path class
// ==========
class AStarPath: public Path {
	public:
		AStarPath(RobotInfo & from):Path(from) {
		}
		virtual ~AStarPath() {
		}

		TargetFixed getNextPoint();
		void generateNearestPoints(TargetFixed * vector, Target position, double distance);

};

//////////////////////////////////////////////////////////
//
// PoolTarget: pool target class
// ==========
class PoolTarget {

	PoolTarget() {}
	void add(Target target);

	private:


};

#endif /* ASTARPATH_H_ */
