/*
 * Rrt.h
 *
 *  Created on: Jul 8, 2013
 *      Author: bruno
 */

#ifndef RRT_H_
#define RRT_H_

#include <KdTree.h>
#include <Array.h>
#include <TargetInclude.h>
#include <Path.h>

#include <iostream>

class Rrt: public Path {
	public:
		Rrt(RobotInfo & from, Target & to);
		virtual ~Rrt();

		TargetFixed getNextPoint();

		void grow(Target goal);

		void print();

		void print(FILE * f, RrtNode * root);

	private:

		RrtNode * root;
		KdTree points;

};

#endif /* Rrt_H_ */
