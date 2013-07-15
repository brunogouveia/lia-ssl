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

	protected:
		void grow(Target goal);

		void checkTree();
		void addTreeOnKdTree(RrtNode * root);

		void clear();
		void deleteTree(RrtNode *&  root);
		void deleteTreeLeast(RrtNode * root, RrtNode * least);

		void print();

		void print(FILE * f, RrtNode * root);

	private:

		TargetFixed cache[200];
		int sizeCache;
		int indexCache;

		RrtNode * root;
		KdTree points;

};

#endif /* Rrt_H_ */
