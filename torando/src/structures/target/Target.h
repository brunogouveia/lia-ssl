#ifndef TARGET_H_
#define TARGET_H_

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
//  OVERVIEW: Target.h
//  ========
//  Class definition for target.

#include<math.h>

//////////////////////////////////////////////////////////
//
// Target: abstract target class
// ==========
class Target {
	public:
		Target();
		virtual ~Target();

		inline float x() {
			return _x;
		}
		inline float y() {
			return _y;
		}


		double distanceTo(Target point) {
			double distX = _x - point.x();
			double distY = _y - point.y();

			return sqrt(distX * distX + distY * distY);
		}

	protected:

		float _x;
		float _y;

		friend class Vision;

};

#endif /* TARGET_H_ */
