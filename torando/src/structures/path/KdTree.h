/*
 * KdTree.h
 *
 *  Created on: Jul 8, 2013
 *      Author: bruno
 */

#ifndef KDTREE_H_
#define KDTREE_H_

#include "kdtree.h"
#include "TargetFixed.h"
#include "Array.h"
#include "Vision.h"
#include <stdlib.h>
#include <iostream>

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

		void grow(Target from, Target goal) {

			//Cria um ponto aleatório
			float maxX = 3000.0;
			float minX = -3000.0;

			float x = minX + (rand() % (int) (maxX - minX + 1));

			float maxY = 2000.0;
			float minY = -2000.0;

			float y = minY + (rand() % (int) (maxY - minY + 1));

			float ran = (float) rand() / (float) RAND_MAX;

			for (int i = 0; i < 10; i++) {
				cout << x << ", " << y << ", " << ran << endl;
			}
			//Existe uma possibilidade de o ponto aleatório ser o ponto de destino
			//Probabilidade de 5%
			if (ran < 0.1) {
				x = goal.x();
				y = goal.y();
			}

			//Cria o Target para o ponto aleatório gerado.
			TargetFixed randomTarget(x, y);

			//Procura o nó da árvore que está mais proximo do ponto gerado
			RrtNode * nearestNode = getNearestNode(randomTarget);

			//Cria um vetor (pontogerado - pontomaisperto)
			Target nearestTarget = nearestNode->target;

			float deltaX = randomTarget.x() - nearestTarget.x();
			float deltaY = randomTarget.y() - nearestTarget.y();

			//normalizar os deltas vetor(delaX,deltaY)
			float norm = sqrt(deltaX * deltaX + deltaY * deltaY);
			float nearestObject = Vision::closestDistance(nearestTarget);
			/*if (norm != 0) {

			 if (nearestObject > 200.0f)
			 nearestObject = 200.0f;

			 if (randomTarget.distanceTo(nearestTarget) > nearestObject) {
			 deltaX = (deltaX / norm) * nearestObject;
			 deltaY = (deltaY / norm) * nearestObject;
			 }
			 }*/

			float normalizedDeltaX = (deltaX / norm) * 200.0f;
			float normalizedDeltaY = (deltaY / norm) * 200.0f;

			bool isFree;
			nearestObject = (nearestObject > 400.0f) ? 400.0f : nearestObject;
			while (nearestObject > 200.0f) {
				TargetFixed delta(nearestTarget.x() + normalizedDeltaX, nearestTarget.y() + normalizedDeltaY);

				isFree = Vision::isFree(from, delta);
				if (isFree) {
					RrtNode * newNode = new RrtNode(delta, nearestNode);
					nearestNode->addChild(newNode);

					insert(delta, newNode);
					nearestNode = newNode;
				} else {
					break;
				}

				nearestTarget = delta;
				nearestObject -= 200.0f;
			}

			if (norm < 200.0f) {
				TargetFixed delta(nearestTarget.x() + deltaX, nearestTarget.y() + deltaY);

				//Se o ponto é válido, ou seja, não está perto de nenhum obstáculo, então adiciona o novo ponto na árvore
				if (Vision::isFree(from, delta)) {
					RrtNode * newNode = new RrtNode(delta, nearestNode);
					nearestNode->addChild(newNode);

					insert(delta, newNode);
				}
			}

		}

	private:
		kdtree * kd;
};

#endif /* KDTREE_H_ */
