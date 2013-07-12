/*
 * Rnn.cpp
 *
 *  Created on: Jul 8, 2013
 *      Author: bruno
 */

#include "Rrt.h"

#include <sys/time.h>
#include <iostream>

//[]----------------------------------[]
// |	Constructor                   |
//[]----------------------------------[]
Rrt::Rrt(RobotInfo & from, Target & to) :
		Path(from) {
	changeTarget(to);

	root = new RrtNode(from, 0);
	points.insert(from, root);
}

//[]----------------------------------[]
// |	Destructor                    |
//[]----------------------------------[]
Rrt::~Rrt() {
}

TargetFixed
//[]----------------------------------[]
// |	getNextPoint                  |
//[]----------------------------------[]
Rrt::getNextPoint() {
	static TargetFixed next(from.x(), from.y());

	/*if (from.distanceTo(next) > 30) {
	 return next;
	 }*/

	timeval stop, start;
	gettimeofday(&start, NULL);

	//static int i = 1;
	while (points.nearestDist(to) > 200) {
		grow(to);
		//cout << "grow" << i++ << endl;
		print();
	}
	RrtNode * parent = points.getNearestNode(to);
	RrtNode * goal = parent->parent;

	while (parent != 0 && parent->target.distanceTo(from) > 200) {
		goal = parent;
		parent = parent->parent;
		if (parent != 0)
			if (closestDistance(goal->target, true) < 700) {
				next = goal->target;
			}
	}
	if (goal != 0) {
		root = goal;
		//next = goal->target;
	} else {
		root = parent;
		//next = parent->target;
	}
	root->parent = 0;

	gettimeofday(&stop, NULL);
	printf("took %lu\n", stop.tv_usec - start.tv_usec);

	exit(1);
	return next;
}

void Rrt::grow(Target goal) {

	//Cria um ponto aleatório
	float maxX = 3000.0;
	float minX = -3000.0;

	float x = minX + (rand() % (int) (maxX - minX + 1));

	float maxY = 2000.0;
	float minY = -2000.0;

	float y = minY + (rand() % (int) (maxY - minY + 1));

	float ran = (float) rand() / (float) RAND_MAX;

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

			points.insert(delta, newNode);
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

void
//[]----------------------------------[]
// |	Print                         |
//[]----------------------------------[]
Rrt::print() {
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

void
//[]----------------------------------[]
// |	Print                         |
//[]----------------------------------[]
Rrt::print(FILE * f, RrtNode * root) {

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

