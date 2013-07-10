/*
 * Path.h
 *
 *  Created on: 27/04/2013
 *      Author: yuriclaure
 */

#ifndef PATH_H_
#define PATH_H_

#include <Target.h>
#include <TargetFixed.h>
#include <Vision.h>

class Path {
	public:
		Path(Target & from) :
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

	protected:

		Target & from;
		Target to;
};

#endif /* PATH_H_ */
