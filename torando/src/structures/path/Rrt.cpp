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
//  OVERVIEW: Referee.cpp
//  ========
//  Source file for referee.

#ifndef RRT_H_
#include "Rrt.h"
#endif

#include <sys/time.h>
#include <iostream>

//////////////////////////////////////////////////////////
//
// Referee implementation
// ==========
Rrt::Rrt(RobotInfo & from, Target to) :
		Path(from)
//[]----------------------------------[]
// |	Constructor                   |
//[]----------------------------------[]
{
	changeTarget(to);
	numNodes = 0;
	sizeCache = 0;
	indexCache = 0;

	root = new RrtNode(from, 0);
	points.insert(from, root);
}

Rrt::~Rrt()
//[]----------------------------------[]
// |	Destructor                    |
//[]----------------------------------[]
{
}

TargetFixed Rrt::getNextPoint()
//[]----------------------------------[]
// |	getNextPoint                  |
//[]----------------------------------[]
{
	static TargetFixed next(from.x(), from.y());

	timeval stop, start;
	gettimeofday(&start, NULL);

	checkTree();

	//Grow the tree to goal.
	numNodes = 0;
	while (points.nearestDist(to) > 20 && numNodes < 2000) {
		grow(to);
		numNodes++;
		//print();
	}

	RrtNode * goal = 0;
	RrtNode * parent = points.getNearestNode(to);

	float distance = from.closestDistance(true);

	while (parent->parent != 0 && parent->target.distanceTo(from) > distance) {

		goal = parent;
		parent = parent->parent;
	}
	if (goal != 0) {
		//root = goal;
		next = goal->target;
	} else {
		//root = parent;
		next = parent->target;
	}
	//root->parent = 0;

	gettimeofday(&stop, NULL);
	//printf("took %lu\n", stop.tv_usec - start.tv_usec);
	return next;
}

void Rrt::grow(Target goal)
//[]----------------------------------[]
// |	Grow	                       |
//[]----------------------------------[]
		{

	//Cria um ponto aleatório
	float maxX = 3700.0;
	float minX = -3700.0;

	float x = minX + (rand() % (int) (maxX - minX + 1));

	float maxY = 2700.0;
	float minY = -2700.0;

	float y = minY + (rand() % (int) (maxY - minY + 1));

	float ran = (float) rand() / (float) RAND_MAX;

	//Existe uma possibilidade de o ponto aleatório ser o ponto de destino
	//Probabilidade de 5%
	if (ran < 0.1) {
		x = goal.x();
		y = goal.y();
	} else if (ran < 0.2) {
		float dX = lookAt.x() - goal.x();
		float dY = lookAt.y() - goal.y();

		float norm = sqrt(dX * dY + dY * dY);

		dX = (dX / norm) * (ROBOT_RADIUS * 0.7f);
		dY = (dY / norm) * (ROBOT_RADIUS * 0.7f);

		x = goal.x() - dX;
		y = goal.y() - dY;

	} else if (ran < 0.7 && sizeCache != 0) {
		if (sizeCache > 50)
			sizeCache = 50;
		int indexRand = rand() % sizeCache;
		x = cache[indexRand].x();
		y = cache[indexRand].y();
	}

	//Cria o Target para o ponto aleatório gerado.
	TargetFixed randomPoint(x, y);

	//Procura o nó da árvore que está mais proximo do ponto gerado
	RrtNode * nearestNode = points.getNearestNode(randomPoint);

	//Cria um vetor (pontogerado - pontomaisperto)
	Target nearestPoint = nearestNode->target;

	float deltaX = randomPoint.x() - nearestPoint.x();
	float deltaY = randomPoint.y() - nearestPoint.y();

	//normalizar os deltas vetor(delaX,deltaY)
	float norm = sqrt(deltaX * deltaX + deltaY * deltaY);
	float nearestObjectDistance = Vision::closestDistance(nearestPoint);
	/*if (norm != 0) {

	 if (nearestObject > 200.0f)
	 nearestObject = 200.0f;

	 if (randomTarget.distanceTo(nearestTarget) > nearestObject) {
	 deltaX = (deltaX / norm) * nearestObject;
	 deltaY = (deltaY / norm) * nearestObject;
	 }
	 }*/

	float normalizedDeltaX = (deltaX / norm) * 80.0f;
	float normalizedDeltaY = (deltaY / norm) * 80.0f;

	bool isFree;
	nearestObjectDistance = (nearestObjectDistance > 400.0f) ? 400.0f : nearestObjectDistance;
	while (nearestObjectDistance > 80.0f) {
		TargetFixed delta(nearestPoint.x() + normalizedDeltaX, nearestPoint.y() + normalizedDeltaY);

		isFree = Vision::isFreeWithBall(from, delta, ROBOT_RADIUS + 50.0, angleApproach);
		if (isFree) {
			RrtNode * newNode = new RrtNode(delta, nearestNode);
			nearestNode->addChild(newNode);

			points.insert(delta, newNode);
			nearestNode = newNode;
		} else {
			break;
		}

		nearestPoint = delta;
		nearestObjectDistance -= 80.0f;
	}

	if (norm < 80.0f) {
		TargetFixed delta(nearestPoint.x() + deltaX, nearestPoint.y() + deltaY);

		//Se o ponto é válido, ou seja, não está perto de nenhum obstáculo, então adiciona o novo ponto na árvore
		if (Vision::isFreeWithBall(from, delta, ROBOT_RADIUS + 50.0, angleApproach)) {
			RrtNode * newNode = new RrtNode(delta, nearestNode);
			nearestNode->addChild(newNode);

			points.insert(delta, newNode);
		}
	}

	if (points.nearestDist(to) <= 80) {
		RrtNode * parent = points.getNearestNode(to);

		//Adiciona o to na árvore
		RrtNode * toNode = new RrtNode(to, parent);
		parent->addChild(toNode);
		points.insert(to, toNode);

		RrtNode * goal = parent;

		float distance = from.closestDistance(true);
		while (parent != 0 && parent->target.distanceTo(from) > distance) {
			cache[indexCache] = goal->target;
			indexCache = (indexCache + 1) % 200;
			sizeCache++;

			goal = parent;
			parent = parent->parent;
		}
	}

}

void Rrt::checkTree()
//[]----------------------------------[]
// |	Check Tree                     |
//[]----------------------------------[]
{
	/*RrtNode * goal = points.getNearestNode(to);
	 if (goal != 0) {
	 RrtNode * parent = goal->parent;

	 while (parent != 0) {
	 if (Vision::closestDistance(goal->target, false) < (ROBOT_RADIUS) && from.distanceTo(goal->target) > (ROBOT_RADIUS)) {
	 printf("Distance: %f  -  %f\n", Vision::closestDistance(goal->target, false), from.distanceTo(goal->target));
	 break;
	 } else {
	 printf("Distance: %f  -  %f\n", Vision::closestDistance(goal->target, false), from.distanceTo(goal->target));
	 }
	 goal = parent;
	 parent = parent->parent;
	 }
	 if (goal->target.distanceTo(from) > (3 * ROBOT_RADIUS) && parent == 0) {
	 printf("Remake - %f\n", goal->target.distanceTo(from));
	 clear();
	 } else {

	 root = goal;
	 points.clear();
	 addTreeOnKdTree(root);
	 }
	 }*/

	/*printf("Entrou check\n");
	 printf("%x\n", root);
	 RrtNode * nearest = points.getNearestNode(from);
	 if (nearest == 0)
	 return;
	 points.clear();
	 deleteTreeLeast(root, nearest);
	 printf("Terminou delete\n");
	 root = nearest;
	 root->parent = 0;
	 addTreeOnKdTree(root);

	 printf("Saiu check\n");*/
	clear();
}

void Rrt::deleteTreeLeast(RrtNode * root, RrtNode * least)
//[]----------------------------------[]
// |	Delete Tree Least              |
//[]----------------------------------[]
		{
	if (root == 0 || root == least)
		return;

	printf("Delete tree \n");
	int size = root->children.size();
	for (int i = 0; i < size; i++) {
		if (root->children[i]->target.distanceTo(least->target) > 10.0f)
			deleteTreeLeast(root->children[i], least);
		else
			printf("Nao deletou\n");
	}

	printf("Delete tree end \n");

	delete root;
}

void Rrt::addTreeOnKdTree(RrtNode * root)
//[]----------------------------------[]
// |	Add Tree On KD-Tree            |
//[]----------------------------------[]
		{
	if (root == 0)
		return;

	points.insert(root->target, root);
	int size = root->children.size();
	for (int i = 0; i < size; i++) {
		addTreeOnKdTree(root->children[i]);
	}
}

void Rrt::clear()
//[]----------------------------------[]
// |	Clear		                   |
//[]----------------------------------[]
{
	deleteTree(root);
	points.clear();

	root = new RrtNode(from, 0);
	points.insert(from, root);
}

void Rrt::deleteTree(RrtNode *& root)
//[]----------------------------------[]
// |	Delete Tree                    |
//[]----------------------------------[]
		{
	if (root == 0)
		return;

	int size = root->children.size();
	for (int i = 0; i < size; i++) {
		deleteTree(root->children[i]);
	}

	delete root;
	root = 0;
}

void Rrt::print()
//[]----------------------------------[]
// |	Print                         |
//[]----------------------------------[]
{
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

void Rrt::print(FILE * f, RrtNode * root)
//[]----------------------------------[]
// |	Print                         |
//[]----------------------------------[]
		{

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

