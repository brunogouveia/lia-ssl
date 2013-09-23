#ifndef PATH_H_
#define PATH_H_

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
//  OVERVIEW: Path.h
//  ========
//  Class definition for path.

#include <Target.h>
#include <TargetFixed.h>
#include <Vision.h>

//////////////////////////////////////////////////////////
//
// Path: path class
// ==========
class Path {
	public:
		Path(RobotInfo & from) :
				from(from), to(from) {
		}
		virtual ~Path() {
		}

		// Retorna o próximo ponto no caminho para o destino
		virtual TargetFixed getNextPoint() = 0;

		// Retorna a distancia para o destino
		float distanceToTarget() {
			return from.distanceTo(to);
		}

		// Está no destino
		bool inDestination() {
			return from.distanceTo(to) < 30.0;
		}

		bool changeTarget(Target to) {
			this->to = to;
			return true;
		}

		bool changeAngleApproach(float angle) {
			this->angleApproach = angle;
			return true;
		}

		float closestDistance(Target position, bool considerBall) {
			float distance = 10000.0f;

			if (considerBall) {
				distance = Vision::ball.distanceTo(position);
			}

			int numRobots = Vision::robots.size();
			for (int i = 0; i < numRobots; i++) {
				if (Vision::robots[i].id() != from.id()) {
					float dist = Vision::robots[i].distanceTo(position);

					if (dist > 0.8 * ROBOT_RADIUS && dist < distance)
						distance = dist;
				}
			}

			numRobots = Vision::opponents.size();
			for (int i = 0; i < numRobots; i++) {
				float dist = Vision::opponents[i].distanceTo(position);

				if (dist > 0.8 * ROBOT_RADIUS && dist < distance)
					distance = dist;
			}
			return distance;
		}

	public:

		RobotInfo & from;
		Target to;
		float angleApproach;
};

#endif /* PATH_H_ */
