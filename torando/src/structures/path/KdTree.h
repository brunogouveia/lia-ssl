#ifndef KDTREE_H_
#define KDTREE_H_

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
//  OVERVIEW: KdTree.h
//  ========
//  Class definition for kd-tree.

#include "kdtree.h"
#include "TargetFixed.h"
#include "Array.h"
#include "Vision.h"
#include <stdlib.h>
#include <iostream>

//////////////////////////////////////////////////////////
//
// RrtNode: rrt-node class
// ==========
class RrtNode {

	private:
		friend class Rrt;
		friend class KdTree;

		RrtNode(Target target, RrtNode * parent = 0) :
				target(target.x(), target.y()), parent(parent) {
		}
		~RrtNode() {
		}

		void addChild(RrtNode * child) {
			children.add(child);
		}

		void removeChild(RrtNode * child) {
			children.remove(child);
		}

		TargetFixed target;
		RrtNode * parent;
		Array<RrtNode *> children;
};


//////////////////////////////////////////////////////////
//
// KDRree: kd-tree class
// ==========
class KdTree {
	public:
		KdTree() :
				kd(kd_create(2)) {
			srand(time(0));
		}
		virtual ~KdTree() {
			kd_free(kd);
		}

		void insert(Target target, RrtNode * node) {
			kd_insert3f(kd, target.x(), target.y(), 0, node);
		}


		float nearestDist(Target target) {
			Target nearest = getNearestPoint(target);

			float deltaX = nearest.x() - target.x();
			float deltaY = nearest.y() - target.y();
			return sqrt(deltaX * deltaX + deltaY * deltaY);
		}

		Target getNearestPoint(Target & target) {
			RrtNode * node = getNearestNode(target);

			if (node != 0) {
				return node->target;
			}
			return target;
		}

		RrtNode * getNearestNode(Target & target) {
			kdres * kdr = kd_nearest3f(kd, target.x(), target.y(), 0);

			if (kd_res_size(kdr) > 0) {
				RrtNode * node = (RrtNode *) kd_res_item_data(kdr);
				kd_res_free(kdr);

				return node;
			}
			return 0;
		}

		void clear() {
			kd_clear(kd);
		}



	private:
		kdtree * kd;
};

#endif /* KDTREE_H_ */
