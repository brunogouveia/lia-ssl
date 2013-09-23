#ifndef TARGETFIXED_H_
#define TARGETFIXED_H_

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
//  OVERVIEW: TargetFixed.h
//  ========
//  Class definition for target fixed.

#include <Target.h>

//////////////////////////////////////////////////////////
//
// TargetFixed: target fixed class
// ==========
class TargetFixed: public Target {
	public:
		TargetFixed(float x, float y);
		TargetFixed() {}
		virtual ~TargetFixed();

		void set(float x, float y) {
			_x = x;
			_y = y;
		}
};

#endif /* TARGETFIXED_H_ */
