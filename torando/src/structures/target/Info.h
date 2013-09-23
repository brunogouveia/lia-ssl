#ifndef INFO_H_
#define INFO_H_

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
//  OVERVIEW: Info.h
//  ========
//  Class definition for info.

#include <Target.h>
#include <Kalm.h>

//////////////////////////////////////////////////////////
//
// Info: info class
// ==========
class Info: public Target {
	public:
		Info() {
			kalman.setKalman(0, 0);
		}
		virtual ~Info() {}

	protected:
		Kalman kalman;

};

#endif /* INFO_H_ */
