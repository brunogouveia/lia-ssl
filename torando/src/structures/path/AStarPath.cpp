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
//  OVERVIEW: AStarPath.cpp
//  ========
//  Source file for a star path.

#ifndef ASTARPATH_H_
#include "AStarPath.h"
#endif

//////////////////////////////////////////////////////////
//
// AStarPath implementation
// ==========
TargetFixed AStarPath::getNextPoint()
//[]----------------------------------------------------[]
//|  Get Next Point                                      |
//[]----------------------------------------------------[]
{
	TargetFixed nearestPoints[8];

	generateNearestPoints(nearestPoints, from, 400.0);

	int nearestPossiblePoint = 0;

	for (int i = 1; i < 8; i++) {
		if (Vision::isFree(from, nearestPoints[i], 300.0) && nearestPoints[i].distanceTo(to) < nearestPoints[nearestPossiblePoint].distanceTo(to)) {
			nearestPossiblePoint = i;
		}
	}

	printf("i: %d\n", nearestPossiblePoint);

	return nearestPoints[nearestPossiblePoint];

}

void AStarPath::generateNearestPoints(TargetFixed * out, Target position, double distance)
//[]----------------------------------------------------[]
//|  Generate Nearest Points                             |
//[]----------------------------------------------------[]
{

	if (distance > 500.0)
		distance = 500.0;
	if (distance < 100.0)
		distance = 100.0;

	out[0].set(position.x() + distance, position.y());
	out[1].set(position.x() + distance, position.y() + distance);
	out[2].set(position.x(), position.y() + distance);
	out[3].set(position.x() - distance, position.y() + distance);
	out[4].set(position.x() - distance, position.y());
	out[5].set(position.x() - distance, position.y() - distance);
	out[6].set(position.x(), position.y() - distance);
	out[7].set(position.x() + distance, position.y() - distance);

	return;
}

