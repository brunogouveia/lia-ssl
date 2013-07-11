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
		Rrt(Target & from, Target & to) :
				Path(from) {
			changeTarget(to);

			root = new RrtNode(from, 0);
			points.insert(from, root);
		}
		virtual ~Rrt() {

		}

		TargetFixed getNextPoint() {
			static TargetFixed next(from.x(), from.y());

			/*if (from.distanceTo(next) > 30) {
			 return next;
			 }*/

			while (points.nearestDist(to) > 200) {
				points.grow(from, to);
				cout << "grow" << endl;
				print();
			}
			RrtNode * parent = points.getNearestNode(to);
			RrtNode * goal = parent->parent;

			while (parent != 0 && parent->target.distanceTo(from) > 100) {
				goal = parent;
				parent = parent->parent;
			}
			if (goal != 0) {
				root = goal;
				next = goal->target;
			} else {
				root = parent;
				next = parent->target;
			}
			root->parent = 0;
			return next;
		}

		void print() {
			FILE * f = fopen("rrt.txt", "w+");
			print(f, root);

			int numRobots = Vision::robots.size();
			for (int i = 0; i < numRobots; i++) {
				fprintf(f, "%f, %f, %f, %f\n", Vision::robots[i].x(), Vision::robots[i].y(), Vision::robots[i].x() + 10, Vision::robots[i].y() + 10);
				fprintf(f, "%f, %f, %f, %f\n", Vision::robots[i].x(), Vision::robots[i].y(), Vision::robots[i].x() + 10, Vision::robots[i].y() - 10);
				fprintf(f, "%f, %f, %f, %f\n", Vision::robots[i].x(), Vision::robots[i].y(), Vision::robots[i].x() - 10, Vision::robots[i].y() + 10);
				fprintf(f, "%f, %f, %f, %f\n", Vision::robots[i].x(), Vision::robots[i].y(), Vision::robots[i].x() - 10, Vision::robots[i].y() - 10);
			}

			numRobots = Vision::opponents.size();
			for (int i = 0; i < numRobots; i++) {
				fprintf(f, "%f, %f, %f, %f\n", Vision::opponents[i].x(), Vision::opponents[i].y(), Vision::opponents[i].x() + 10, Vision::opponents[i].y() + 10);
				fprintf(f, "%f, %f, %f, %f\n", Vision::opponents[i].x(), Vision::opponents[i].y(), Vision::opponents[i].x() + 10, Vision::opponents[i].y() - 10);
				fprintf(f, "%f, %f, %f, %f\n", Vision::opponents[i].x(), Vision::opponents[i].y(), Vision::opponents[i].x() - 10, Vision::opponents[i].y() + 10);
				fprintf(f, "%f, %f, %f, %f\n", Vision::opponents[i].x(), Vision::opponents[i].y(), Vision::opponents[i].x() - 10, Vision::opponents[i].y() - 10);
			}

			fprintf(f, "%f, %f, %f, %f\n", Vision::ball.x(), Vision::ball.y(), Vision::ball.x() + 10, Vision::ball.y() + 10);
			fprintf(f, "%f, %f, %f, %f\n", Vision::ball.x(), Vision::ball.y(), Vision::ball.x() + 10, Vision::ball.y() - 10);
			fprintf(f, "%f, %f, %f, %f\n", Vision::ball.x(), Vision::ball.y(), Vision::ball.x() - 10, Vision::ball.y() + 10);
			fprintf(f, "%f, %f, %f, %f\n", Vision::ball.x(), Vision::ball.y(), Vision::ball.x() - 10, Vision::ball.y() - 10);

			fclose(f);
		}

		void print(FILE * f, RrtNode * root) {

			if (root == 0)
				return;

			int numChildren = root->children.size();
			for (int i = 0; i < numChildren; i++) {
				fprintf(f, "%f, %f, %f, %f\n", root->target.x(), root->target.y(), root->children[i]->target.x(), root->children[i]->target.y());
			}
			for (int i = 0; i < numChildren; i++) {
				print(f, root->children[i]);
			}
		}

	private:

		RrtNode * root;
		KdTree points;

};

#endif /* Rrt_H_ */
