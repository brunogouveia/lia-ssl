#ifndef RRT_H_
#define RRT_H_

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
//  OVERVIEW: Rrt.h
//  ========
//  Class definition for rrt.

#include <KdTree.h>
#include <Array.h>
#include <TargetInclude.h>
#include <Path.h>

#include <iostream>

//////////////////////////////////////////////////////////
//
// Rrt: rrt class
// ==========
class Rrt: public Path {
	public:
		Rrt(RobotInfo & from, Target  to);
		virtual ~Rrt();

		TargetFixed getNextPoint();

		int size() const {
			return numNodes;
		}

		void setLookAt(Target target) {
			this->lookAt = target;
		}
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

		int numNodes;
		Target lookAt;
		TargetFixed cache[200];
		int sizeCache;
		int indexCache;

		RrtNode * root;
		KdTree points;

};

#endif /* Rrt_H_ */
